#include "student.h"
#include "course.h"

void Student::enroll(Course* course) {

    for (auto c : enrolledCourses) {
        if (c == course) {
            cout << "你已經選過這門課了。" << endl;
            return;
        }
    }

    for (auto c : enrolledCourses) {

        if (c->getDay() == course->getDay()) {

            bool overlap =
                !(course->getEndPeriod() < c->getStartPeriod()
                    || course->getStartPeriod() > c->getEndPeriod());

            if (overlap) {
                cout << "課程時間衝突，無法加選。" << endl;
                return;
            }
        }
    }

    if (course->isFull()) {
        cout << "課程已滿，無法加選。" << endl;
        return;
    }

    enrolledCourses.push_back(course);

    course->addStudent(this);

    cout << "加選成功！" << endl;
}

void Student::drop(Course* course) {

    auto it = find(
        enrolledCourses.begin(),
        enrolledCourses.end(),
        course
    );

    if (it != enrolledCourses.end()) {

        enrolledCourses.erase(it);

        course->removeStudent(this);

        cout << "成功退選課程。" << endl;
    }
    else {
        cout << "你沒有修這門課。" << endl;
    }
}

void Student::printCourses() const {

    cout << "學生 "
        << name
        << " 的課表："
        << endl;

    if (enrolledCourses.empty()) {

        cout << "（尚未選任何課程）" << endl;
        return;
    }

    for (auto c : enrolledCourses) {

        cout
            << " - "
            << c->getCode()
            << ": "
            << c->getTitle()
            << " ("
            << c->getCredits()
            << "學分)"
            << endl;
    }

    cout << endl;
    cout << "總學分："
        << getTotalCredits()
        << endl;
}

bool Student::verifyPassword(
    const string& input
) const {
    return input == password;
}

int Student::getTotalCredits() const {

    int total = 0;

    for (auto c : enrolledCourses) {
        total += c->getCredits();
    }

    return total;
}
