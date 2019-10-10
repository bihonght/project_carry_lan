
//this program is about working of LMS(lerning mangement system)
//this program can add new courses,delete courses,edit course,view all course and view courses by semester,save and load courses from file
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
//global variables
int counter = 0;
int counter1 = 0;
int global;
//loading user information
bool loadUsers(string userslist[], string passwordslist[])
{
    string line;
    ifstream user;
    user.open("Users.txt");
    if (user.is_open()) {
        for (int i = 0; !user.eof(); i++) {
            getline(user, line, ',');
            userslist[i] = line;
            getline(user, line);
            passwordslist[i] = line;

            counter1++;
        }
    }
    else {
        cout << "Sorry, we are unable to run the program, as user data does not exist." << endl
             << endl;
    }
}
//saving courses in a file
bool saveCourses(string codelist[], string namelist[], int semesterlist[], int creditlist[])
{
    ofstream file;
    file.open("Courses.txt");
    if (file.is_open()) {
        for (int i = 0; i < counter; i++) {
            file << codelist[i] << "," << namelist[i] << "," << creditlist[i] << "," << semesterlist[i] << endl;
        }
        cout << endl
             << "Courses has been saved successfully " << endl;
        return 1;
    }
    else {
        cout << "ERROR OPENING FILE Courses.txt" << endl;
        return 0;
    }
    file.close();
}
//function to check validity of CourseCode
bool isValidCourseCode(string coursecode)
{
    if (coursecode[0] >= 'A' && coursecode[0] <= 'Z') {

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
    if (a > 50) {
        return 0;
    }
    else {

        bool flag = 0;
        int length = coursename.size();
        for (int i = 0; i < length; i++) {
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
    if (s > 0 && s < 9) {
        return 1;
    }
    else {
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
    if (file1.is_open()) {
        for (int i = 0; !file1.eof(); i++) {
            getline(file1, line, ',');
            if (isValidCourseCode(line)) {
                codelist[i] = line;
                getline(file1, line, ',');
                if (isValidCourseName(line)) {
                    namelist[i] = line;
                    file1 >> a;
                    if (isValidCreditHours(a)) {
                        creditlist[i] = a;
                        file1.ignore(1, ',');
                        file1 >> a;
                        if (isValidSemester(a)) {
                            semesterlist[i] = a;

                            counter++;
                            file1.ignore(1, '\0');
                        }
                        else {
                            cout << i + 1 << " SEMESTER INVALID " << endl;
                            break;
                        }
                    }
                    else {
                        cout << i + 1 << " CREDIT HOUR INVALID " << endl;
                        break;
                    }
                }
                else {
                    cout << i + 1 << " COURSE NAME IS INVALID " << endl;
                    break;
                }
            }
            else {
                cout << i + 1 << " COURSE CODE IS INVALID " << endl;
                break;
            }
        }
        cout << "COURSES LOADED SUCCESSFULLY " << endl
             << endl;
    }
    else {
        cout << "ERROR OPENING FILE OR FILE DOES NOT EXIST";
    }
    file1.close();
}
//function to add a new course in LMS
void AddCourse(string codelist[], int creditlist[], int semesterlist[], string namelist[], string code, int credit, int semester, string name)
{
    if (isValidCourseCode(code))
        if (isValidCreditHours(credit))
            if (isValidSemester(semester))
                if (isValidCourseName(name)) {
                    codelist[counter] = code;
                    creditlist[counter] = credit;
                    semesterlist[counter] = semester;
                    namelist[counter] = name;
                    counter++;
                    cout << "Course has been added successfully" << endl
                         << endl;
                }
                else
                    cout << "INVALID COURSENAME" << endl;
            else
                cout << "INVAID SEMESTER " << endl;
        else
            cout << "INVALID CREDIT HOUR" << endl;
    else
        cout << "INVALID COURSE CODE" << endl;
}
//function to edit a course from the list
void EditCourse(string codelist[], int creditlist[], int semesterlist[], string namelist[], string code, int credit, int semester, string name)
{

    if (isValidCourseCode(code))
        if (isValidCreditHours(credit))
            if (isValidSemester(semester))
                if (isValidCourseName(name)) {
                    codelist[global] = code;
                    creditlist[global] = credit;
                    semesterlist[global] = semester;
                    namelist[global] = name;
                }
                else
                    cout << "INVALID COURSENAME" << endl;
            else
                cout << "INVAID SEMESTER " << endl;
        else
            cout << "INVALID CREDIT HOUR" << endl;
    else
        cout << "INVALID COURSE CODE" << endl;

    cout << "Course has been edited successfully" << endl;
}
//funtion to delete a course
void DeleteCourse(string codelist[], int creditlist[], int semesterlist[], string namelist[], string code)
{
    int o;
    bool flag = false;
    for (int i = 0; i < counter; i++) {
        if (code == codelist[i]) {
            flag = true;
            o = i;
        }
    }
    for (int a = o; a < counter; a++) {
        codelist[a] = codelist[a + 1];
        creditlist[a] = creditlist[a + 1];
        semesterlist[a] = semesterlist[a + 1];
        namelist[a] = namelist[a + 1];
    }
    if (flag == true)
        cout << "Course has been deleted successfully" << endl;
    else
        cout << "THIS COURSECODE DO NOT MATCH ANY DATA" << endl;
    counter--;
}
//funtion to output all the courses that created
void ViewCourses(string codelist[], int creditlist[], int semesterlist[], string namelist[])
{
    for (int i = 0; i < counter; i++)
        cout << setw(14) << left << codelist[i] << setw(30) << left << namelist[i] << setw(15) << left << creditlist[i] << setw(10) << left << semesterlist[i] << endl;

    cout << endl;
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
    for (int i = 0; i < counter; i++) {
        if (code == codelist[i]) {
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
    for (int i = 0; i <= counter; i++) {
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
    char* function = new char; //DYNAMIC variable for use of function number
    int a;
    int opp = 1;
    //declaration of variables through which data is stored in arrays
    string code;
    string name;
    int credit;
    int semester;
    string username;
    string password;
    //loading courses from file
    loadCourses(codelist, namelist, semesterlist, creditlist);
    loadUsers(userslist, passwordslist);
    cout << setw(75) << "**WELCOME TO UNVERESTY MANGEMENT SYSTEM**" << endl
         << endl;
    cout << endl
         << endl;
    while (opp == 1) {
        cout << "Dear User, current software is intended for authorized users only." << endl
             << "Login to the system to get access." << endl;
        //login information
        cout << "Username :  ";
        cin >> username;
        cout << endl
             << "Password :  ";
        cin >> password;
        cout << endl;
        if (searchlogin(userslist, passwordslist, username, password)) {
            opp = 0;
            cout << "You have successfully logged into the system" << endl;
            //MAIN PART OF PROGRAM
            *function = '0';
            while (*function != '7' && *function != '6') //loop used for repetition of program
            { //interface
                cout << setw(72) << "Choose an option from the following" << endl
                     << endl
                     << setw(55) << "1    Add Course" << endl
                     << setw(58) << "2    Update Course" << endl
                     << setw(58) << "3    Delete Course" << endl
                     << setw(61) << "4    Veiw All Courses" << endl
                     << setw(71) << "5    View Courses Of A Semester" << endl
                     << setw(65) << "6    Logout of the system" << endl
                     << setw(57) << "7    Exit program" << endl
                     << endl
                     << endl;
                //
                if (cin.fail()) {

                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                cout << "Enter the number of operation you want to perform >> ";
                cin >> function;
                cout << endl;
                switch (*function) {

                case '1': //add course case
                {
                    cout << "Enter the detail of the course >> ";
                    cin >> code >> credit >> semester;
                    cin.ignore(1, ' ');
                    getline(cin, name);
                    cout << endl;
                    AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                    cout << endl;
                } break;
                case '2': //edit course case
                {
                    cout << "Enter the code of course you want to EDIT >> ";
                    cin >> code;
                    a = searchcode(code, codelist);
                    if (a == -1) {
                        cout << "THIS COURSECODE DO NOT MATCH ANY DATA" << endl;
                    }
                    else {
                        global = a;
                        cout << "Enter the new detail of the course >> ";
                        cin >> code >> credit >> semester;
                        getline(cin, name);
                        cout << endl;
                        EditCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                        cout << endl;
                    }
                } break;
                case '3': //delete course case
                {
                    cout << "Enter the code of the course you want to delete >> ";
                    cin >> code;
                    cout << endl;
                    DeleteCourse(codelist, creditlist, semesterlist, namelist, code);
                } break;
                case '4': //view all courses case
                {
                    cout << setw(10) << left << "Course Code   " << setw(30) << left << "Name   " << setw(10) << left << "Credit Hours   " << setw(10) << left << "Semester   " << endl;
                    cout << endl;
                    ViewCourses(codelist, creditlist, semesterlist, namelist);
                } break;
                case '5': //view courses by semester
                {
                    cout << "Enter the name of semester >> ";
                    cin >> semester;
                    cout << endl;
                    cout << setw(10) << left << "Course Code   " << setw(30) << "Name   " << setw(10) << left << "Credit Hours   " << endl;
                    cout << endl;
                    ViewSemesterCourses(codelist, creditlist, semesterlist, namelist, semester);
                } break;
                case '6': {
                    opp = 1;

                } break;

                case '7': //save courses
                {
                    opp = 0;
                    saveCourses(codelist, namelist, semesterlist, creditlist);
                } break;
                default: {
                    delete function;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "PLEASE ENTER THE VALID VALUE" << endl;
                } break;
                }
                delete function;
            }
        }
        else {
            cout << "Dear User, Username/password is incorrect. Enter the" << endl
                 << "username/password again to get access to the system" << endl
                 << endl;
        }
    }
    return 0;
}


