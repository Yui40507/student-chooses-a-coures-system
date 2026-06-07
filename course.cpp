#include "course.h"

void Course::addStudent(Student* const student)
{
    enrolledStudents.push_back(student);
}

void Course::removeStudent(Student* const student)
{
    auto it = find(enrolledStudents.begin(),
                   enrolledStudents.end(),
                   student);

    if (it != enrolledStudents.end())
    {
        enrolledStudents.erase(it);
    }
}

void Course::printStudents() const
{
    cout << "課程 " << title << " 的學生名單：" << endl;

    if (enrolledStudents.empty())
    {
        cout << "（尚無人修課）" << endl;
        return;
    }

    for (auto s : enrolledStudents)
    {
        cout << " - " << s->getId()
             << ": " << s->getName()
             << endl;
    }
}
