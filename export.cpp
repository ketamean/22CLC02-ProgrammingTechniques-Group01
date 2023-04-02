#include <fstream>
#include "header.h"
using namespace std;

void exportStudents() {
    if (!L_Student.head)    return;
    DLL<STUDENT*>* cur = L_Student.head;
    string filepath = "CSV\\STUDENT.csv";
    ofstream ofs(filepath);
    ofs << "username, password,No,studentID,firstname,lastname,gender(0-male/1-female),DateofBirth(mm/dd/yyyy),socialID,CLASS";
    DLL<STUDENT*>* dum; // the node to be deleted
    while (cur) {
        // current student == cur->data;
        ofs << cur->data->user->username << ',' << cur->data -> user -> password << ',';
        ofs << cur->data->No << ',' << cur->data->studentID << ',' << cur->data->firstname << ',' << cur->data->lastname << ',';
        ofs << cur->data -> gender << ',';
        ofs << DateToString(cur->data->DoB) << ',';
        ofs << cur->data -> socialID << ',';
        ofs << cur->data->Class->convertToString();
        ofs << '\n';

        dum = cur;
        cur = cur -> next;
        delete dum->data;
        delete dum;
    }
    ofs.close();
    return;
}

void exportStaffs() {
    if (!L_Staff.head)  return;
    DLL<STAFF*>* cur = L_Staff.head;
    string filepath = "CSV\\STAFF.csv";
    ofstream ofs(filepath);
    ofs << "username,password,firstname,lastname\n";
    DLL<STAFF*>* dum; // the node to be deleted
    while (cur)
    {
        // current staff == cur -> data;
        ofs << (cur -> data -> user) -> username << ',' << (cur -> data -> user) -> password << ',';
        ofs << cur -> data -> firstname << ',' << cur -> data -> lastname;
        ofs << '\n';

        dum = cur;
        cur = cur -> next;
        delete dum->data;
        delete dum;
    }
    ofs.close();
    return;
}

void exportClasses() {
    if (!L_Class.head)  return;
    DLL<CLASS>* cur = L_Class.head;
    string filepath = "CSV\\CLASS.csv";
    ofstream ofs(filepath);
    ofs << "yearIn,K,Program,No\n";
    DLL<CLASS>* dum; // the node to be deleted
    while (cur)
    {
        CLASS cla = cur -> data;
        ofs << cla.yearIn << ',' << cla.K << ',';
        ofs << convertFromProgram(cla.program) << ',' << cla.No;
        ofs << '\n';

        dum = cur;
        cur = cur -> next;
        delete dum;
    }
    ofs.close();
    return;
}

void exportStudentsInACourse(COURSE* c, uint startYear) {
    DLL<SCOREBOARD*> *cur = c->students.head;
    if ( !cur ) return;
        // will not do anything if there is no student in the list of students in the course;

    ofstream ofs("CSV/SemInSchoolYear/CourseInSemester/StudentsInCourse/" + c->ID + ".csv");

    ofs << "StudentID,othermark,midtermMark,finalMark,totalMark" << endl;         // this is title line
    
    DLL<SCOREBOARD*>* tmp; // the node to be deleted
    while (cur != nullptr)
    {
        ofs << cur->data->student->studentID <<',' << cur->data->otherMark << ',' << cur->data->midtermMark << ',' << cur->data->finalMark << ',' << cur->data->totalMark << endl;

        tmp = cur;
        cur = cur -> next;
        delete tmp->data;   // delete node->data first
        delete tmp;         // delete a node of the COURSE::students list
    }
    ofs.close();
}

void exportCoursesInASemester(std::string filename, SEMESTER* sem, uint startYear) {
    DLL<COURSE*>* cur = sem->course.head;
    ofstream out(filename);
    
    DLL<COURSE*>* temp; // node to be deleted
    out << "ID,Name,Teacher,Credit,Max Students,Day,Session"; 
    while(cur)
    {
        out << cur->data->ID << ',' << cur->data->name << ',' << cur->data->teacher << ',' << cur->data->credit << ',' << cur->data->maxStudents << ',' << cur->data->day << ',' << cur->data->session;
        out << ',' << cur->data->ID + ".csv" << '\n';
        
        exportStudentsInACourse(cur->data, startYear);
        
        temp = cur; 
        cur = cur->next;
        delete temp->data;
        delete temp;
    }

    out.close();
}

void exportASemesterInASchoolYear(std::string filename, SEMESTER* sem, uint startYear) {
    if ( !sem ) return;

    // open the file that has been created
    ofstream out(filename, std::ofstream::app); // append
    string file = "CSV/SemInSchoolYear/" + to_string(startYear) + "_sem" + to_string(sem->No) + ".csv";
    out << sem->No << ',' << DateToString(sem->startdate) << ',' << DateToString(sem->enddate) << endl;
    out.close();
    exportCoursesInASemester(file, sem, startYear);
}

void exportSchoolYears() {
    DLL<SCHOOLYEAR>* cur = L_SchoolYear.head;
    if ( !cur ) return; // will not do anything if there is no school year => no semester => no course

    // since then, list.tail != nullptr
    ofstream out("CSV/SchoolYear.csv");
    out << "yearbegin,yearend,semester file,sem1,sem2,sem3" << endl;    // title line

    string file;
    DLL<SCHOOLYEAR>* dummy; // the node to be deleted
    while ( cur != L_SchoolYear.tail->next ) {
        out << cur->data.begin << ',';
        out << cur->data.end << ',';

        file = "CSV/SemInSchoolYear/" + to_string(cur->data.begin) + "_" + to_string(cur->data.end) + ".csv";
        out << file << ',';

        out << ((cur->data.sem1)? 1:0) << ',';
        out << ((cur->data.sem2)? 1:0) << ',';
        out << ((cur->data.sem3)? 1:0) << endl;

        // create an empty file
        ofstream out(file); // append
        out.close();

        exportASemesterInASchoolYear(file, cur->data.sem1, 1);
        exportASemesterInASchoolYear(file, cur->data.sem2, 2);
        exportASemesterInASchoolYear(file, cur->data.sem3, 3);

        delete cur->data.sem1;
        delete cur->data.sem2;
        delete cur->data.sem3;

        dummy = cur;
        cur = cur->next;
        delete dummy;
    }
    out.close();
}