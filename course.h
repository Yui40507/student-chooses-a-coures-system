#ifndef	COURSE_H
#define COURSE_H

#include"student.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Student;

class Course {
private:
    string code;
    string title;
    int capacity;
    vector<Student*> enrolledStudents;

public:
    Course(string code, string title, int capacity)
        : code(code), title(title), capacity(capacity) {
    }

    string getCode() const { return code; }
    string getTitle() const { return title; }
    bool isFull() const { return enrolledStudents.size() >= capacity; }

    void addStudent(Student* const student);
    void removeStudent(Student* const student);
    void printStudents() const;
    int getCapacity() const;
    int getEnrolledCount() const;

};

#endif

