#ifndef COURSE_H
#define COURSE_H

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
    int credits;

    string day;
    int startPeriod;
    int endPeriod;

    vector<Student*> enrolledStudents;

public:
    Course(
        string code,
        string title,
        int capacity,
        int credits,
        string day,
        int startPeriod,
        int endPeriod
    )
        : code(code),
        title(title),
        capacity(capacity),
        credits(credits),
        day(day),
        startPeriod(startPeriod),
        endPeriod(endPeriod) {
    }

    string getCode() const { return code; }
    string getTitle() const { return title; }

    int getCredits() const { return credits; }

    string getDay() const { return day; }

    int getStartPeriod() const { return startPeriod; }

    int getEndPeriod() const { return endPeriod; }

    bool isFull() const {
        return enrolledStudents.size() >= capacity;
    }

    void addStudent(Student* const student);
    void removeStudent(Student* const student);
    void printStudents() const;

    int getCapacity() const;
    int getEnrolledCount() const;
};

#endif
