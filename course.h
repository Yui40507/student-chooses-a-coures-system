#ifndef COURSE_H
#define COURSE_H

#include "student.h"
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

    int credits;          // ⭐ 學分
    string day;           // ⭐ 星期
    int startPeriod;      // ⭐ 開始節次
    int endPeriod;        // ⭐ 結束節次

    vector<Student*> enrolledStudents;

public:
    Course(string code,
           string title,
           int capacity,
           int credits,
           string day,
           int startPeriod,
           int endPeriod)
        : code(code),
          title(title),
          capacity(capacity),
          credits(credits),
          day(day),
          startPeriod(startPeriod),
          endPeriod(endPeriod)
    {}

    string getCode() const { return code; }
    string getTitle() const { return title; }

    int getCapacity() const { return capacity; }
    int getEnrolledCount() const { return enrolledStudents.size(); }

    bool isFull() const { return enrolledStudents.size() >= capacity; }

    int getCredits() const { return credits; }

    string getDay() const { return day; }
    int getStartPeriod() const { return startPeriod; }
    int getEndPeriod() const { return endPeriod; }

    void addStudent(Student* const student);
    void removeStudent(Student* const student);
    void printStudents() const;
};

#endif
