#pragma once

#include <string>
#include "../header.h"

struct STUDENT;

struct COURSE {
    std::string ID = "";
    std::string name = "";
    std::string teacher = "";
    ushort credit = 0, maxStudents = 50;
    WeekDay day = MON;
    Session session = S1; // S1--S4
    LIST<DLL, STUDENT*> students;

    void updateInfo ();                         // update info of this course
    void importInfo(STUDENT& SV);
    bool addStudents(std::string filename);
    /// this function will upload the list of students enrolled in the course from a file (filename)

    void add1Student (LIST <SLL, STUDENT>&L, STUDENT & SV);
    /// add1Student: Add a student to the course, includes:
    ///     student: is student needs to be added 
    /// This function does not return anything
    void in(STUDENT ST);                    //***************
    void Export(LIST <SLL, STUDENT>& L) ; //***************
    void remove1Student (STUDENT student);
    /// remove1Student: Remove a student from the course, includes:
    ///        student: is the student need to be removed from the course
    /// This function does not return anything
    /////////////////
    // scores are members of STUDENT
    void importScore ();    // file CSV _ task 20
    bool updateResult ();  // get data from keyboard
    void updateResultByID(LIST <SLL, STUDENT> L);
    void UpdateST(LIST <SLL, STUDENT>& L, LIST <SLL, STUDENT>& L1);
                                                // task 22
                                                // search for student in the list `students` using `ID`:   if found, update new score; otherwise, pop up "there is no student with ID " << ID << " in this course."
    void ReadFileFromTeacher(LIST <SLL, STUDENT>& L);
    bool exportStudents(std::string filename);
};