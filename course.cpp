#include "course.h"

void Course::addStudent(Student* const student) {
    enrolledStudents.push_back(student);
}

void Course::removeStudent(Student* const student) {
    auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);
    }
}

void Course::printStudents() const {
    cout << "課程 " << title << " 的學生名單：" << endl;
    if (enrolledStudents.empty()) {
        cout << "（尚無人修課）" << endl;
    }
    for (auto s : enrolledStudents) {
        cout << " - " << s->getId() << ": " << s->getName() << endl;
    }
}
int Course::getCapacity() const {
    return capacity;
}

int Course::getEnrolledCount() const {
    return enrolledStudents.size();
}