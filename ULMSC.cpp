//this program is about working of LMS(learning management system)
//this program can add new courses,delete courses,edit course,view all course and view courses by semester,save and load courses from file
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
//global variables
int counter = 0;
int counter1 = 0;
int counter2 = 0;
int global;
int counter3[100] = {0}; //counter for courses registered against a student
//viewing students and the courses in which they are registered
void viewallstudents(string stdRegNoList[], string stdNamesList[], string stdCourseList[][100])
{
    for (int i = 0; i < counter2; i++)
    {
        cout << left << setw(30) << stdRegNoList[i] << setw(30) << stdNamesList[i];
        for (int j = 0; j < counter3[i]; j++)
        {
            cout << stdCourseList[i][j];
            if (j + 1 < counter3[i])
                cout << ",";
        }
        cout << endl
             << endl;
    }
}
//unregistering a student
void unRegisterCourse(string stdRegNoList[], string courseList[], string stdCourseList[][100], string regNo, string courseCode)
{
    int a;
    cout << "Enter the course code you want to unregister :";
    cin >> courseCode;

    for (int j = 0; j < counter3[global]; j++)
    {
        if (courseCode == stdCourseList[global][j])
        {
            a = j;

            break;
        }
    }
    for (int i = a; i < counter3[global]; i++)
    {
        stdCourseList[global][i] = stdCourseList[global][i + 1];
    }
    counter3[global]--;
    cout << "course has successfully unregistered for the student " << endl
         << endl;
}
//registering students in courses
void registerCourse(string stdRegNoList[], string stdCourseList[][100], string codelist[], string regNo, string code)
{
    int flag1 = 0;
    for (int i = 0; i < counter3[global]; i++)
    {
        if (code == stdCourseList[global][i])
            flag1 = 1;
    }
    if (flag1 == 0)
    {
        int flag = 0;
        for (int i = 0; i < counter; i++)
        {
            if (codelist[i] == code)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            stdCourseList[global][counter3[global]] = code;
            cout << "Student has been registered in the course you entered" << endl
                 << endl;
            counter3[global]++;
        }
        else
        {
            cout << "THIS COURSE DOES NOT EXIST" << endl
                 << endl;
        }
    }
    else
    {
        cout << "THE STUDENT IS ALREADY REGITERED IN THIS COURSE" << endl
             << endl;
    }
}
//checking validity of student registration number
bool isValidRegNo(string regno)
{
    bool found = false;
    if (regno.size() == 11)
    {
        if (regno[0] == '2')
        {
            if (regno[1] == '0')
            {
                if (regno[2] == '1')
                {
                    if (regno[3] >= '0' && regno[3] <= '9')
                    {
                        if (regno[4] == '-')
                        {
                            if (regno[5] == 'C')
                            {
                                if (regno[6] >= 'A' && regno[6] <= 'Z')
                                {
                                    if (regno[7] == '-')
                                    {
                                        if (regno[8] >= '0' && regno[8] <= '9')
                                        {
                                            if (regno[9] >= '0' && regno[9] <= '9')
                                            {
                                                if (regno[10] >= '0' && regno[10] <= '9')
                                                {
                                                    if (regno[8] == '0' && regno[9] == '0' && regno[10] == '0')
                                                        found = false;
                                                    else
                                                        found = true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return found;
}
//checking validity of student name
bool isValidStudentName(string studentname)
{
    int a = studentname.size();
    if (a > 50)
    {
        return 0;
    }
    else
    {

        bool flag = 0;
        int length = studentname.size();
        for (int i = 0; i < length; i++)
        {
            if ((studentname[i] >= 'A' && studentname[i] <= 'Z') || (studentname[i] >= 'a' && studentname[i] <= 'z') || studentname[i] == ' ')

                flag = 1;

            else
                return 0;
        }
        return 1;
    }
}
//deleting student from lms
void deleteStudent(string studentnamelist[], string studentregnolist[], string studentname, string regno)
{
    for (int i = global; i < counter2; i++)
    {
        studentnamelist[i] = studentnamelist[i + 1];
        studentregnolist[i] = studentregnolist[i + 1];
    }
    counter3[global] = 0;
    counter2--;
}
//function for updating student
void updateStudent(string studentnamelist[], string studentregnolist[], string studentname, string regno)
{
    studentnamelist[global] = studentname;
    studentregnolist[global] = regno;
}
//adding students in LMS
void addStudent(string studentnamelist[], string studentregnolist[], string studentname, string regno)
{
    int flag = 0;
    for (int i = 0; i < counter2; i++)
    {

        if (regno == studentregnolist[i])
            flag = 1;
    }
    if (flag == 0)
    {
        studentnamelist[counter2] = studentname;
        studentregnolist[counter2] = regno;
        counter2++;
        cout << "Student has been added successfully " << endl
             << endl;
    }
    else
    {
        cout << "ANOTHER STUDENT IS REGISTERED WITH THE SAME REGISTRATION NUMBER " << endl
             << endl;
    }
}

//loading user information
bool loadUsers(string userslist[], string passwordslist[])
{
    string line;
    ifstream user;
    user.open("Users.txt");
    if (user.is_open())
    {
        for (int i = 0; !user.eof(); i++)
        {
            getline(user, line, ',');
            userslist[i] = line;
            getline(user, line);
            passwordslist[i] = line;

            counter1++;
        }
    }
    else
    {
        cout << "Sorry, we are unable to run the program, as user data does not exist." << endl
             << endl;
    }
}
//saving courses in a file
bool saveCourses(string codelist[], string namelist[], int semesterlist[], int creditlist[])
{
    ofstream file;
    file.open("Courses.txt");
    if (file.is_open())
    {
        for (int i = 0; i < counter; i++)
        {
            file << codelist[i] << "," << namelist[i] << "," << creditlist[i] << "," << semesterlist[i] << endl;
        }
        cout << endl
             << "Courses has been saved successfully " << endl
             << endl;
        return 1;
    }
    else
    {
        cout << "ERROR OPENING FILE Courses.txt" << endl
             << endl;
        return 0;
    }
    file.close();
}
//function to check validity of CourseCode
bool isValidCourseCode(string coursecode)
{
    if (coursecode[0] >= 'A' && coursecode[0] <= 'Z')
    {

        if (coursecode[1] >= 'A' && coursecode[1] <= 'Z')
            if (isdigit(coursecode[2]))
                if (isdigit(coursecode[3]))
                    if (isdigit(coursecode[4]))
                        return 1;
    }
    else
        return 0;
}
//function to check validity of CourseName
bool isValidCourseName(string coursename)
{
    int a = coursename.size();
    if (a > 50)
    {
        return 0;
    }
    else
    {

        bool flag = 0;
        int length = coursename.size();
        for (int i = 0; i < length; i++)
        {
            if ((coursename[i] >= 'A' && coursename[i] <= 'Z') || (coursename[i] >= 'a' && coursename[i] <= 'z') || coursename[i] == ' ')
                flag = 1;
            else
                return 0;
        }
        return 1;
    }
}
//function to check validity CreditHours
bool isValidCreditHours(int credit)
{
    if (credit > 0 && credit < 4)

        return 1;

    else

        return 0;
}
//function to check validity Semester
bool isValidSemester(int s)
{
    if (s > 0 && s < 9)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//loading courses from file
bool loadCourses(string codelist[], string namelist[], int semesterlist[], int creditlist[])
{
    string line;
    int a;
    ifstream file1;
    file1.open("Courses.txt");
    if (file1.is_open())
    {
        for (int i = 0; !file1.eof(); i++)
        {
            getline(file1, line, ',');
            if (isValidCourseCode(line))
            {
                codelist[i] = line;
                getline(file1, line, ',');
                if (isValidCourseName(line))
                {
                    namelist[i] = line;
                    file1 >> a;
                    if (isValidCreditHours(a))
                    {
                        creditlist[i] = a;
                        file1.ignore(1, ',');
                        file1 >> a;
                        if (isValidSemester(a))
                        {
                            semesterlist[i] = a;

                            counter++;
                            file1.ignore(1, '\0');
                        }
                        else
                        {
                            cout << i + 1 << " SEMESTER INVALID " << endl
                                 << endl;
                            break;
                        }
                    }
                    else
                    {
                        cout << i + 1 << " CREDIT HOUR INVALID " << endl
                             << endl;
                        break;
                    }
                }
                else
                {
                    cout << i + 1 << " COURSE NAME IS INVALID " << endl
                         << endl;
                    break;
                }
            }
            else
            {
                cout << i + 1 << " COURSE CODE IS INVALID " << endl
                     << endl;
                break;
            }
        }
        cout << "COURSES LOADED SUCCESSFULLY " << endl
             << endl;
    }
    else
    {
        cout << "ERROR OPENING FILE OR FILE DOES NOT EXIST" << endl
             << endl;
    }
    file1.close();
}
//function to add a new course in LMS
void AddCourse(string codelist[], int creditlist[], int semesterlist[], string namelist[], string code, int credit, int semester, string name)
{
    int flag = 0;
    for (int i = 0; i < counter; i++)
    {
        if (code == codelist[i])
            flag = 1;
    }
    if (flag == 0)
    {
        if (isValidCourseCode(code))
            if (isValidCreditHours(credit))
                if (isValidSemester(semester))
                    if (isValidCourseName(name))
                    {
                        codelist[counter] = code;
                        creditlist[counter] = credit;
                        semesterlist[counter] = semester;
                        namelist[counter] = name;
                        counter++;
                        cout << "Course has been added successfully" << endl
                             << endl;
                    }
                    else
                        cout << "INVALID COURSENAME" << endl
                             << endl;
                else
                    cout << "INVAID SEMESTER " << endl
                         << endl;
            else
                cout << "INVALID CREDIT HOUR" << endl
                     << endl;
        else
            cout << "INVALID COURSE CODE" << endl
                 << endl;
    }
    else
    {
        cout << "THIS COURSE IS ALREADY PRESENT IN THE LIST" << endl
             << endl;
    }
}
//function to edit a course from the list
void EditCourse(string codelist[], int creditlist[], int semesterlist[], string namelist[], string code, int credit, int semester, string name)
{

    if (isValidCourseCode(code))
        if (isValidCreditHours(credit))
            if (isValidSemester(semester))
                if (isValidCourseName(name))
                {
                    codelist[global] = code;
                    creditlist[global] = credit;
                    semesterlist[global] = semester;
                    namelist[global] = name;
                }
                else
                    cout << "INVALID COURSENAME" << endl
                         << endl;
            else
                cout << "INVAID SEMESTER " << endl
                     << endl;
        else
            cout << "INVALID CREDIT HOUR" << endl
                 << endl;
    else
        cout << "INVALID COURSE CODE" << endl
             << endl;

    cout << "Course has been edited successfully" << endl
         << endl;
}
//function to delete a course
void DeleteCourse(string codelist[], int creditlist[], int semesterlist[], string namelist[], string code)
{
    int o;
    bool flag = false;
    for (int i = 0; i < counter; i++)
    {
        if (code == codelist[i])
        {
            flag = true;
            o = i;
        }
    }
    for (int a = o; a < counter; a++)
    {
        codelist[a] = codelist[a + 1];
        creditlist[a] = creditlist[a + 1];
        semesterlist[a] = semesterlist[a + 1];
        namelist[a] = namelist[a + 1];
    }
    if (flag == true)
        cout << "Course has been deleted successfully" << endl
             << endl;
    else
        cout << "THIS COURSECODE DO NOT MATCH ANY DATA" << endl
             << endl;
    counter--;
}
//function to output all the courses that created
void ViewCourses(string codelist[], int creditlist[], int semesterlist[], string namelist[])
{
    for (int i = 0; i < counter; i++)
        cout << setw(14) << left << codelist[i] << setw(30) << left << namelist[i] << setw(15) << left << creditlist[i] << setw(10) << left << semesterlist[i] << endl;

    cout << endl
         << endl;
}
//function to output courses of a specific semester
void ViewSemesterCourses(string codelist[], int creditlist[], int semesterlist[], string namelist[], int semester)

{
    for (int i = 0; i < counter; i++)
        if (semester == semesterlist[i])
            cout << setw(13) << left << codelist[i] << setw(31) << left << namelist[i] << setw(15) << left << creditlist[i] << endl;
}
//search a course in an array
int searchcode(string code, string codelist[])
{
    bool flag = 0;
    for (int i = 0; i < counter; i++)
    {
        if (code == codelist[i])
        {
            return i;
            bool flag = 1;
        }
    }
    if (flag != 1)
        return -1;
}
//search username and password in array
bool searchlogin(string usernameslist[], string passwordslist[], string username, string password)
{
    for (int i = 0; i <= counter; i++)
    {
        if (usernameslist[i] == username)
            if (passwordslist[i] == password)
                return 1;
    }
    return 0;
}
int main()
{
    //declaration of array in which data is stored
    string codelist[100];
    string namelist[100];
    int creditlist[100];
    int semesterlist[100];
    string userslist[100];
    string passwordslist[100];
    string stdNamesList[100];
    string stdRegNoList[100];
    string stdCourseList[100][100];
    //some extra variable used in program
    int function;
    int a;
    int opp = 1;
    bool flag;
    //declaration of variables through which data is stored in arrays
    string code;
    string name;
    int credit;
    int semester;
    string username;
    string password;
    string studentName = "0";
    string regNo;
    loadCourses(codelist, namelist, semesterlist, creditlist); //loading courses from file
    loadUsers(userslist, passwordslist);                       //username and password loading from a file
    cout << setw(75) << "**WELCOME TO UNVERESTY MANGEMENT SYSTEM**" << endl
         << endl;
    cout << endl
         << endl;
    while (opp == 1)
    {
        cout << "Dear User, current software is intended for authorized users only." << endl
             << "Login to the system to get access." << endl;
        //login information
        cout << "Username :  ";
        cin >> username;
        cout << endl
             << "Password :  ";
        cin >> password;
        cout << endl;
        if (searchlogin(userslist, passwordslist, username, password))
        {
            opp = 0;
            cout << "You have successfully logged into the system" << endl
                 << endl;
            //MAIN PART OF PROGRAM
            function = 0;
            while (function != 12 && function != 13) //loop used for repetition of program
            {
                //interface
                cout << setw(72) << "Choose an option from the following" << endl
                     << endl
                     << setw(55) << "1    Add Course" << endl
                     << setw(58) << "2    Update Course" << endl
                     << setw(58) << "3    Delete Course" << endl
                     << setw(61) << "4    View All Courses" << endl
                     << setw(71) << "5    View Courses Of A Semester" << endl
                     << setw(60) << "6    Add New Student" << endl
                     << setw(59) << "7    Update Student" << endl
                     << setw(59) << "8    Delete Student" << endl
                     << setw(62) << "9    View All Students" << endl
                     << setw(76) << "10   Register the course for student" << endl
                     << setw(78) << "11   Unregister the course for student" << endl
                     << setw(65) << "12   Logout of the system" << endl
                     << setw(57) << "13   Exit program" << endl
                     << endl
                     << endl;
                if (cin.fail())
                {

                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                cout << "Enter the number of operation you want to perform >> ";
                cin >> function;
                cout << endl
                     << endl;
                switch (function)
                {

                case 1: //add course case
                {
                    cout << "Enter the detail of the course >> ";
                    cin >> code >> credit >> semester;
                    cin.ignore(1, ' ');
                    getline(cin, name);
                    cout << endl
                         << endl;
                    AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                    cout << endl
                         << endl;
                }
                break;
                case 2: //edit course case
                {
                    cout << "Enter the code of course you want to EDIT >> ";
                    cin >> code;
                    a = searchcode(code, codelist);
                    if (a == -1)
                    {
                        cout << "THIS COURSECODE DO NOT MATCH ANY DATA" << endl
                             << endl;
                    }
                    else
                    {
                        global = a;
                        cout << "Enter the new detail of the course >> ";
                        cin >> code >> credit >> semester;
                        getline(cin, name);
                        cout << endl
                             << endl;
                        EditCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                        cout << endl
                             << endl;
                    }
                }
                break;
                case 3: //delete course case
                {
                    cout << "Enter the code of the course you want to delete >> ";
                    cin >> code;
                    cout << endl
                         << endl;
                    DeleteCourse(codelist, creditlist, semesterlist, namelist, code);
                    for (int i = 0; i < counter2; i++)
                    {
                        for (int j = 0; j < counter3[i]; j++)
                        {
                            if (code == stdCourseList[i][j])
                            {
                                for (int x = j; x < counter3[i]; x++)
                                    stdCourseList[i][j] = stdCourseList[i][j + 1];
                                counter3[i]--;
                            }
                        }
                    }
                }
                break;
                case 4: //view all courses case
                {
                    cout << setw(10) << left << "Course Code   " << setw(30) << left << "Name   " << setw(10) << left << "Credit Hours   " << setw(10) << left << "Semester   " << endl;
                    cout << endl
                         << endl;
                    ViewCourses(codelist, creditlist, semesterlist, namelist);
                }
                break;
                case 5: //view courses by semester
                {
                    cout << "Enter the name of semester >> ";
                    cin >> semester;
                    cout << endl
                         << endl;
                    cout << setw(10) << left << "Course Code   " << setw(30) << "Name   " << setw(10) << left << "Credit Hours   " << endl;
                    cout << endl
                         << endl;
                    ViewSemesterCourses(codelist, creditlist, semesterlist, namelist, semester);
                }
                break;
                case 6: //adding a new student
                {
                    cout << "Enter details of students: ";
                    cin >> regNo;
                    cin.ignore(1, ' ');
                    getline(cin, studentName);
                    if (studentName == "\0")
                    {
                        cout << "please enter the name" << endl;
                        break;
                    }
                    if (isValidRegNo(regNo))
                    {
                        if (isValidStudentName(studentName))
                        {
                            addStudent(stdNamesList, stdRegNoList, studentName, regNo);
                        }
                        else
                            cout << "INVALID STUDENT NAME" << endl
                                 << endl;
                    }
                    else
                        cout << "INVALID REGISTRATION NUMBER" << endl
                             << endl;
                }
                break;
                case 7: //editing detail of a student
                {
                    flag = 0;
                    cout << "Enter registration Number of the student to edit: ";
                    cin >> regNo;
                    for (int i = 0; i < counter2; i++)
                    {
                        if (regNo == stdRegNoList[i])
                        {
                            global = i;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        cout << "The Registration number  you entered do not match any of data " << endl
                             << endl;
                    }
                    else
                    {
                        cout << "Enter the new details of the course : ";
                        cin >> regNo;
                        getline(cin, studentName);
                        if (isValidRegNo(regNo))
                        {
                            if (isValidStudentName(studentName))
                            {
                                updateStudent(stdNamesList, stdRegNoList, studentName, regNo);
                                cout << "STUDENT has been edited successfully" << endl
                                     << endl;
                            }
                            else
                                cout << "INVALID STUDENT NAME" << endl
                                     << endl;
                        }
                        else
                            cout << "INVALID REGISTRATION NUMBER" << endl
                                 << endl;
                    }
                }
                break;
                case 8: //deleting a student
                {
                    flag = 0;
                    cout << "Enter registration Number of the student to delete: ";
                    cin >> regNo;
                    for (int i = 0; i < counter2; i++)
                    {
                        if (regNo == stdRegNoList[i])
                        {
                            global = i;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        cout << "The Registration number you entered do not match any of data " << endl
                             << endl;
                    }
                    else
                    {
                        deleteStudent(stdNamesList, stdRegNoList, studentName, regNo);
                        cout << "STUDENT has been deleted successfully " << endl
                             << endl;
                    }
                }
                break;
                case 9: //viewing student names their registration number and courses registered against them
                {
                    cout << left << setw(30) << "Registration number " << setw(30) << "Student Name "
                         << "Courses " << endl
                         << endl;
                    viewallstudents(stdRegNoList, stdNamesList, stdCourseList);
                }
                break;
                case 10: //registring a course for a student
                {
                    flag = 0;
                    cout << "Enter registration Number of the student for course registration: ";
                    cin >> regNo;
                    for (int i = 0; i < counter2; i++)
                    {
                        if (regNo == stdRegNoList[i])
                        {
                            global = i;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        cout << "The Registration number you entered do not match any of data " << endl
                             << endl;
                    }
                    else
                    {
                        cout << "Enter Course Code to register: ";
                        cin >> code;
                        if (isValidCourseCode(code))
                        {
                            registerCourse(stdRegNoList, stdCourseList, codelist, regNo, code);
                        }
                        else
                        {
                            cout << "INVALID COURSE CODE" << endl
                                 << endl;
                        }
                    }
                }
                break;
                case 11: //unregistring a course for a student
                {
                    flag = 0;
                    cout << "Enter the registration number of the student : ";
                    cin >> regNo;
                    for (int i = 0; i < counter2; i++)
                    {
                        if (regNo == stdRegNoList[i])
                        {
                            global = i;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        unRegisterCourse(stdRegNoList, codelist, stdCourseList, regNo, code);
                    }
                    else
                    {
                        cout << "THIS REGISTRATION NUMBER DO NOT MATCH OUR DATA " << endl
                             << endl;
                    }
                }
                break;
                case 12: //loging out of the system
                {
                    opp = 1;
                }
                break;

                case 13: //saving courses in a file
                {
                    opp = 0;
                    saveCourses(codelist, namelist, semesterlist, creditlist);
                }
                break;
                default:
                {

                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "PLEASE ENTER THE VALID VALUE" << endl
                         << endl;
                }
                break;
                }
            }
        }
        else
        {
            cout << "Dear User, Username/password is incorrect. Enter the" << endl
                 << "username/password again to get access to the system" << endl
                 << endl;
        }
    }
    return 0;
}
