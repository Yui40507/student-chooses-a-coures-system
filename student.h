#ifndef STUDENT_H
#define STUDENT_H

#include "course.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Course;

class Student {
private:
    string id;
    string name;
    vector<Course*> enrolledCourses;
    string password;

public:
    Student(string id, string name, string password)
        : id(id), name(name), password(password){}

    string getId() const { return id; }
    string getName() const { return name; }
	void setPassword(const string& newPassword) { password = newPassword; }

    void enroll(Course* course);
    void drop(Course* course);
    void printCourses() const;
    bool verifyPassword(const string& input) const;

};

#endif // !STUDENT_H

