
//this program is about working of LMS(learning management system)
//this program can add new courses,delete courses,edit course,view all course and view courses by semester,save and load courses from file
#include <iostream>
#include <iomanip>
#include <fstream>  // for ifstream and ofstreams
#include <string>
using namespace std;
//global variables
int counter = 0;
int counter1 = 0;
int counter2 = 0; // num of students 
int global;
int counter3[100] = {0}; //counter for courses registered against a student

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

//viewing students and the courses in which they are registered
void viewallstudents(string stdRegNoList[], string stdNamesList[], string stdCourseList[][100])
{
    for (int i = 0; i < counter2; i++)
    {
        cout << left << setw(30) << stdRegNoList[i] << setw(30) << stdNamesList[i];
        for (int j = 0; j < counter3[i]; j++) // view courses registered by 1 student
        {
            cout << stdCourseList[i][j];
            if (j + 1 < counter3[i])
                cout << ",";
        }
        cout << endl
             << endl;
    }
}

//unregistering course for a student
void unRegisterCourse(string stdRegNoList[], string courseList[], string stdCourseList[][100], string regNo, string courseCode)
{
    int a = -100;
    
    for (int j = 0; j < counter3[global]; j++)
    {
        if (courseCode == stdCourseList[global][j])
        {
            a = j;

            break;
        }
    }
    if (a == -100){
        cout << "Student has not registered this course" << endl;
    }
    else{
        for (int i = a; i < counter3[global]; i++)
        {
            stdCourseList[global][i] = stdCourseList[global][i + 1];
        }
        counter3[global]--;
        cout << "Course has successfully unregistered for the student " << endl
                << endl;
    }
    
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
        cout << "THE STUDENT IS ALREADY REGISTERED IN THIS COURSE" << endl
             << endl;
    }
}
//checking validity of student registration number
bool isValidRegNo(string regno)
{
    bool found = false;
    if (regno.size() == 10)
    {
        if (regno[0] == 'V')
        {
            if (regno[1] == '2')
            {
                if (regno[2] == '0')
                {
                    if (regno[3] >= '2' /* && regno[3] <= '9' */ )
                    {
                        if (regno[4] >= '0' && regno[4] <= '2')
                        {
                            if (regno[5] == '0')
                            {
                                if (regno[6] == '0')
                                {
                                    if (regno[7] >= '0' && regno[7] <= '9')
                                    {
                                        if (regno[8] >= '0' && regno[8] <= '9')
                                        {
                                            if (regno[9] >= '0' && regno[9] <= '9')
                                            {
                                                // if (regno[10] >= '0' && regno[10] <= '9')
                                                
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
    ifstream user;      // input file stream, i.e. a stream of data used for reading input from a file.
    user.open("Users.txt");  // Users.txt has users'names , one per line
    if (user.is_open()) {
        for (int i = 0; !user.eof(); i++) { // read until it hits EOF error
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
    ofstream file("Courses.txt");
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

            if (coursecode[2] >= 'A' && coursecode[2] <= 'Z')

                if (coursecode[3] >= 'A' && coursecode[3] <= 'Z')
                    
                    if (isdigit(coursecode[4]))
                        if (isdigit(coursecode[5]))
                            if (isdigit(coursecode[6]))
                                if (isdigit(coursecode[7]))
                                return 1;
    }
    else
        return 0;
}
//function to check validity of CourseName
bool isValidCourseName(string coursename)
{
    int a = coursename.size();
    if (a > 60) {
        return 0;
    }
    else {

        bool flag = 0;
        int length = coursename.size();
        for (int i = 0; i < length ; i++) {
            // if ((coursename[i] >= 'A' && coursename[i] <= 'Z') || (coursename[i] >= 'a' && coursename[i] <= 'z') || coursename[i] == ' ')
                flag = 1;
            // else
            //     return 0;
        }
        return 1;
    }
}
//function to check validity CreditHours
bool isValidCreditHours(int credit)
{
    if (credit > 0 && credit <= 4)
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

//loading student info from a file
void LoadStudents(string RegNoList[], string StdNameList[], string StdCourseList[][100])
{
    int count;
    int use;
    string total;
    string line, line1;
    ifstream stufile;
    stufile.open("Students.txt");
    if (stufile.is_open())
    {
        for (int i = 0; !stufile.eof(); i++)
        {
            getline(stufile, line, ',');
            if (isValidRegNo(line))
            {
                RegNoList[counter2] = line;
                getline(stufile, line);
                if (isValidStudentName(line))
                {
                    StdNameList[counter2] = line;
                    {

                        getline(stufile, line1);
                        count = 0;
                        for (int j = 0; line1[j] != '\0'; j++)
                        {
                            if (line1[j] == ',')
                                count++;
                        }
                        use = 0;
                        for (int a = 0; a < count + 1; a++)
                        {

                            total = "";
                            for (int o = use; o < use + 8; o++)
                            {
                                total = total + line1[o];
                            }

                            use = use + 9;
                            if (isValidCourseCode(total))
                            {

                                StdCourseList[i][a] = total;
                                counter3[i]++;
                            }
                            else
                            {
                                cout << i + 1 << " " << a + 1 << " INVALID COURSECODE" << endl
                                     << endl;
                                break;
                            }
                        }
                    }

                    counter2++;
                }
                else
                {
                    cout << i + 1 << " INVALID STUDENT NAME" << endl
                         << endl;
                }
            }
            else
            {
                cout << i + 1 << " INVALID REGISTRATION NUMBER" << endl
                     << endl;
            }
        }
        cout << "STUDENT INFO LOADED" << endl
             << endl;
    }
    else
    {
        cout << "ERROR OPENING Students.txt FILE" << endl;
    }
}

//saving student information in a file
void saveStudents(string RegNoList[], string StdNameList[], string StdCourseList[][100])
{
    ofstream stufile("Students.txt");
    if (stufile.is_open())
    {
        for (int i = 0; i < counter2; i++)
        {
            stufile << RegNoList[i] << "," << StdNameList[i] << endl;

            for (int j = 0; j < counter3[i]; j++)
            {

                stufile << StdCourseList[i][j];
                if ((counter3[i]) != j + 1)
                {
                    stufile << ",";
                }
            }
            if (counter2 != i + 1)
                stufile << endl;
        }
        cout << "Information of the students has successfully saved " << endl;
    }
    else
    {
        cout << "ERROR OPENING Students.txt FILE" << endl
             << endl;
    }
    stufile.close();
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
                // cout << line;
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
                    cout << i + 1 << " COURSE NAME IS INVALID " <<  endl;
                    break;
                }
            }
            else {
                cout << i + 1 << " COURSE CODE IS INVALID " << line << endl;
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
    if (searchcode(code, codelist) == -1)
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
    else 
        cout << "COURSE ALREADY ADDED" << endl;
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
// change to ViewStudentCourses
void ViewSemesterCourses(string codelist[], int creditlist[], int semesterlist[], string namelist[], int semester)

{
    for (int i = 0; i < counter; i++)
        if (semester == semesterlist[i])
            cout << setw(13) << left << codelist[i] << setw(31) << left << namelist[i] << setw(15) << left << creditlist[i] << endl;
}

void printallcourse(){
    cout << "List of courses:" << endl <<
            "ENGL1010 2 1 Academic English 1" << endl <<
            "ENGL1020 2 2 Academic English 2" << endl <<
            "MATH1010 4 1 Calculus 1" << endl <<
            "COMP1010 4 1 Intro to Programming" << endl <<
            "ELEC2010 4 2 Intro to Circuit" << endl <<
            "COMP2050 4 4 Artificial Intelligence" << endl <<
            "COMP2020 3 3 Computer Organization" << endl <<
            "MECE3030 4 4 Dynamics" << endl <<
            "MECE4010 3 6 Heat Transfer" << endl <<
            "HASS1010 2 1 Philosophy" << endl <<
            "HASS1020 2 2 HCM Ideology" << endl;
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
    int jadugar;
    bool cheetah = 0;
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
    LoadStudents(stdRegNoList, stdNamesList, stdCourseList);   //loading student info
    cout << setw(75) << "**WELCOME TO UNVERESTY MANGEMENT SYSTEM**" << endl
         << endl;
    cout << endl
         << endl;
    while (opp == 1)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
        }
        jadugar = 0;
        cout << endl
             << "Choose the option for Login" << endl
             << "1 for Admin" << endl
             << "2 for Student" << endl
             << "3 to exit the program" << endl
             << "Enter option: >>";
        cin >> jadugar;

        if (jadugar == 1)
        {

            cout << "Dear User, current software is intended for authorized users only." << endl
                 << "Login to the system to get access as admin." << endl;
            //login information
            cout << endl
                 << "Password >> ";
            cin >> password;
            cout << endl;
            if (password == "admin")
            {
                opp = 0;
                cout << "You have successfully logged into the system" << endl
                     << endl;
                //MAIN PART OF PROGRAM
                function = 0;
                while (function != 10) //loop used for repetition of program
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
                        //  << setw(76) << "10   Register the course for student" << endl
                        //  << setw(78) << "11   Unregister the course for student" << endl
                         << setw(65) << "10   Logout of the system" << endl
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
                        printallcourse();
                        int temp;
                        cout << "Enter 1 to add all courses/ 2 to add course manually >>";
                        cin >> temp;
                        if (temp == 2){
                        cout << "Enter the detail of the course >> code(space-bar)credit(space-bar)sem ";
                        cin >> code >> credit >> semester;
                        cout << "Enter the course name >>";
                        cin.ignore(1, ' ');
                        getline(cin, name);
                        cout << endl
                             << endl;
                        AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                        cout << endl
                             << endl;
                        }
                        else if (temp == 1){                      
                            code = "ENGL1010";
                            name = "Academic English 1";
                            credit = 2;
                            semester = 1;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "ENGL1020";
                            name = "Academic English 2";
                            credit = 2;
                            semester = 2;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "MATH1010";
                            name = "Calculus 1";
                            credit = 4;
                            semester = 1;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "COMP1010";
                            name = "Intro to Programming";
                            credit = 4;
                            semester = 1;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "ELEC2010";
                            name = "Intro to Circuit";
                            credit = 4;
                            semester = 2;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "COMP2050";
                            name = "Artificial Intelligence";
                            credit = 4;
                            semester = 4;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "COMP2020";
                            name = "Computer Organization";
                            credit = 3;
                            semester = 3;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "MECE3030";
                            name = "Dynamics";
                            credit = 4;
                            semester = 4;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "MECE4010";
                            name = "Heat Transfer";
                            credit = 3;
                            semester = 6;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "HASS1010"; 
                            name = "Philosophy";
                            credit = 2;
                            semester = 1;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);
                            code = "HASS1020";
                            name = "HCM Ideology";
                            credit = 2;
                            semester = 2;
                            AddCourse(codelist, creditlist, semesterlist, namelist, code, credit, semester, name);                             
                        }
                    }
                    break;
                    case 2: //edit course case
                    {
                        cout << "All current courses:" << endl;
                        cout << setw(10) << left << "Course Code   " << setw(30) << left << "Name   " << setw(10) << left << "Credit Hours   " << setw(10) << left << "Semester   " << endl;
                        cout << endl
                             << endl;
                        ViewCourses(codelist, creditlist, semesterlist, namelist);
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
                            printallcourse();
                            cout << "Enter the new detail of the course >> code(space-bar)credit(space-bar)sem " ;
                            cin >> code >> credit >> semester;
                            cout << "Enter the course name >>";
                            cin.ignore(1, ' ');
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
                        cout << "All current courses:" << endl;
                        cout << setw(10) << left << "Course Code   " << setw(30) << left << "Name   " << setw(10) << left << "Credit Hours   " << setw(10) << left << "Semester   " << endl;
                        cout << endl
                             << endl;
                        ViewCourses(codelist, creditlist, semesterlist, namelist);
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
                        cout << "Enter details of student (Student ID) >>";
                        cin >> regNo;
                        cout << "Enter new student name >>";                       
                        cin.ignore(1, ' ');
                        getline(cin, studentName);
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
                        cout << "Enter registration Number of the student to edit >> ";
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
                            cout << "Enter the new details of the student (Student ID) >>";
                            cin >> regNo;
                            cout << "Enter student name >>";
                            cin.ignore(1, ' ');
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
    
                    case 10: //loging out of the system
                    {
                        saveCourses(codelist, namelist, semesterlist, creditlist);
                        saveStudents(stdRegNoList, stdNamesList, stdCourseList);
                        opp = 1;
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

        else if (jadugar == 2) // for student login
        {

            int muntakhib = 0;
            int size1;
            flag = 0;

            cout << endl
                 << "Student should enter his registration number and password" << endl
                 << endl;
            cout << "Enter registration Number (Student ID) >>";
            cin >> regNo;
            cout << "Enter Password >>";
            cin >> password;

            for (int shida = 0; shida < counter2; shida++)
            {
                if (regNo == stdRegNoList[shida])
                {
                    global = shida;
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                if (password == "vinuni")
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(100, '\n');
                    }

                    while (muntakhib != 4 && muntakhib != 5)
                    {
                        cout << endl
                                << "Enter 1 to view registered course" << endl
                                << "Enetr 2 to register new course" << endl
                                << "Enter 3 to unregister course" << endl
                                << "Enter 4 to logout of the system" << endl
                                // << "Enter 5 to exit" << endl
                                << "Choose option: ";
                        cin >> muntakhib;
                        switch (muntakhib)
                        {

                        case 1:
                        {
                            cout << left << setw(30) << "Registration number " << setw(30) << "Student Name "
                                    << "Courses " << endl
                                    << endl;
                            cout << left << setw(30) << stdRegNoList[global] << setw(30) << stdNamesList[global];

                            for (int j = 0; j < counter3[global]; j++)
                            {
                                cout << stdCourseList[global][j];
                                if (j + 1 < counter3[global])
                                    cout << ",";
                            }
                            cout << endl
                                    << endl;
                            break;
                        }
                        
                        case 2: 
                        {
                            ViewCourses(codelist, creditlist, semesterlist, namelist);
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
                            break;
                        }

                        case 3: 
                        {
                            cout << "Enter Course Code to unregister: ";
                            cin >> code;
                            if (isValidCourseCode(code))
                            {
                                unRegisterCourse(stdRegNoList, codelist, stdCourseList, regNo, code);
                            }
                            else
                            {
                                cout << "INVALID COURSE CODE" << endl
                                     << endl;
                            }
                            break;
                        }

                        case 4:
                        {
                            opp = 1;
                            break;
                        }

                       

                        // default:
                        // {
                        //     cout << "ENTER A VALID VALUE (1 , 2 OR 3)" << endl
                        //             << endl;
                        // }
                        }
                    }
                }
                    else
                    {
                        cout << "INVALID PASSWORD" << endl
                             << endl;
                    }
                }

            else
            {
                cout << "THIS REGISTRATION NUMBER DOES NOT MATCH OUR DATA" << endl
                     << endl;
            }
        }
        else if (jadugar == 3){
            opp = 0;
                        
        }

        else
        {
            cout << "ENTER A VALID VALUE(1 OR 2)" << endl
                 << endl;
        }
        
    }
    system("pause");
    return 0;
}


