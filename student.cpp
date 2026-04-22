#include"student.h"

void Student::enroll(Course* course) {
    // 檢查是否已修過這門課
    for (auto c : enrolledCourses) {
        if (c == course) {
            cout << "你已經選過這門課了，不能重複加選。" << endl;
            return;
        }
    }

    // 檢查課程是否已滿
    if (course->isFull()) {
        cout << "課程已滿，無法加選。" << endl;
        return;
    }

    // 通過檢查，正式加選
    enrolledCourses.push_back(course);
    course->addStudent(this);
    cout << "加選成功！" << endl;
}


void Student::drop(Course* course) {
    auto it = find(enrolledCourses.begin(), enrolledCourses.end(), course);
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
    cout << "學生 " << name << " 的課表：" << endl;
    if (enrolledCourses.empty()) {
        cout << "（尚未選任何課程）" << endl;
        return;
    }
    for (auto c : enrolledCourses) {
        cout << " - " << c->getCode() << ": " << c->getTitle() << endl;
    }
}

bool Student::verifyPassword(const string& input) const
{
    return input == password;
}
