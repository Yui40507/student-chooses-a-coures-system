#include "student.h"
#include "course.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ======================= 查找學生 =======================
Student* findStudent(vector<Student>& students, const string& id)
{
    auto it = find_if(students.begin(), students.end(),
        [&](const Student& s)
        {
            return s.getId() == id;
        });

    return it != students.end() ? &(*it) : nullptr;
}

// ======================= 查找課程 =======================
Course* findCourse(vector<Course>& courses, const string& code)
{
    auto it = find_if(courses.begin(), courses.end(),
        [&](const Course& c)
        {
            return c.getCode() == code;
        });

    return it != courses.end() ? &(*it) : nullptr;
}

// ======================= main =======================
int main()
{
    vector<Student> students;
    vector<Course> courses;

    int choice;

    cout << "歡迎使用選課系統！" << endl;

    while (true)
    {
        cout << endl << "請選擇登入方式：" << endl;
        cout << "1. 學生登入" << endl;
        cout << "2. 老師登入" << endl;
        cout << "3. 離開系統" << endl;
        cout << "請輸入選項：";

        cin >> choice;
        cin.ignore();

        // ==================================================
        // 學生登入
        // ==================================================
        if (choice == 1)
        {
            string sid, pwd;

            cout << "輸入學生ID：";
            getline(cin, sid);

            Student* currentStudent = findStudent(students, sid);

            if (!currentStudent)
            {
                cout << "找不到該學生ID。" << endl;
                continue;
            }

            cout << "輸入密碼：";
            getline(cin, pwd);

            if (!currentStudent->verifyPassword(pwd))
            {
                cout << "密碼錯誤。" << endl;
                continue;
            }

            cout << "登入成功！" << endl;

            while (true)
            {
                cout << endl << "===== 學生選課系統 =====" << endl;
                cout << "1. 加選課程" << endl;
                cout << "2. 退選課程" << endl;
                cout << "3. 顯示我的課表" << endl;
                cout << "4. 顯示課程學生名單" << endl;
                cout << "5. 顯示所有課程" << endl;
                cout << "6. 更改密碼" << endl;
                cout << "7. 登出" << endl;
                cout << "請輸入選項：";

                cin >> choice;
                cin.ignore();

                // ---------------- 加選 ----------------
                if (choice == 1)
                {
                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course = findCourse(courses, ccode);

                    if (!course)
                    {
                        cout << "找不到課程。" << endl;
                        continue;
                    }

                    currentStudent->enroll(course);
                }

                // ---------------- 退選 ----------------
                else if (choice == 2)
                {
                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course = findCourse(courses, ccode);

                    if (!course)
                    {
                        cout << "找不到課程。" << endl;
                        continue;
                    }

                    currentStudent->drop(course);
                }

                // ---------------- 課表 ----------------
                else if (choice == 3)
                {
                    currentStudent->printCourses();
                }

                // ---------------- 課程名單 ----------------
                else if (choice == 4)
                {
                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course = findCourse(courses, ccode);

                    if (!course)
                    {
                        cout << "找不到課程。" << endl;
                        continue;
                    }

                    course->printStudents();
                }

                // ---------------- 所有課程 ----------------
                else if (choice == 5)
                {
                    if (courses.empty())
                    {
                        cout << "尚未建立任何課程。" << endl;
                        continue;
                    }

                    cout << "所有課程清單：" << endl;

                    for (const auto& c : courses)
                    {
                        cout << " - " << c.getCode()
                             << ": " << c.getTitle()
                             << "（" << c.getCredits() << "學分）"
                             << " [" << c.getDay()
                             << " " << c.getStartPeriod()
                             << "-" << c.getEndPeriod() << "]"
                             << "（" << c.getEnrolledCount()
                             << "/" << c.getCapacity() << "）";

                        if (c.isFull())
                        {
                            cout << "【已額滿】";
                        }

                        cout << endl;
                    }
                }

                // ---------------- 改密碼 ----------------
                else if (choice == 6)
                {
                    string newPassword;

                    cout << "請輸入新密碼：";
                    getline(cin, newPassword);

                    currentStudent->setPassword(newPassword);

                    cout << "密碼已更改成功！" << endl;
                }

                // ---------------- 登出 ----------------
                else if (choice == 7)
                {
                    cout << "已登出。" << endl;
                    break;
                }

                else
                {
                    cout << "無效選項。" << endl;
                }
            }
        }

        // ==================================================
        // 老師登入
        // ==================================================
        else if (choice == 2)
        {
            cout << "老師登入成功！" << endl;

            while (true)
            {
                cout << endl << "===== 老師選課系統 =====" << endl;
                cout << "1. 新增學生" << endl;
                cout << "2. 新增課程" << endl;
                cout << "3. 查詢課程學生名單" << endl;
                cout << "4. 顯示所有課程" << endl;
                cout << "5. 離開" << endl;
                cout << "請輸入選項：";

                cin >> choice;
                cin.ignore();

                // ---------------- 新增學生 ----------------
                if (choice == 1)
                {
                    string id, name, pwd;

                    cout << "輸入學生ID：";
                    getline(cin, id);

                    cout << "輸入學生姓名：";
                    getline(cin, name);

                    cout << "輸入密碼：";
                    getline(cin, pwd);

                    students.emplace_back(id, name, pwd);

                    cout << "學生已新增。" << endl;
                }

                // ---------------- 新增課程（完整版本） ----------------
                else if (choice == 2)
                {
                    string code, title, day;
                    int cap, credits, start, end;

                    cout << "輸入課程代碼：";
                    getline(cin, code);

                    cout << "輸入課程名稱：";
                    getline(cin, title);

                    cout << "輸入人數上限：";
                    cin >> cap;

                    cout << "輸入學分：";
                    cin >> credits;

                    cin.ignore();

                    cout << "輸入星期（Mon/Tue/...）：";
                    getline(cin, day);

                    cout << "輸入開始節次：";
                    cin >> start;

                    cout << "輸入結束節次：";
                    cin >> end;

                    cin.ignore();

                    courses.emplace_back(code, title, cap, credits, day, start, end);

                    cout << "課程已新增。" << endl;
                }

                // ---------------- 課程名單 ----------------
                else if (choice == 3)
                {
                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course = findCourse(courses, ccode);

                    if (course)
                        course->printStudents();
                    else
                        cout << "找不到課程。" << endl;
                }

                // ---------------- 所有課程 ----------------
                else if (choice == 4)
                {
                    for (const auto& c : courses)
                    {
                        cout << c.getCode()
                             << " " << c.getTitle()
                             << "（" << c.getCredits() << "學分）"
                             << " [" << c.getDay()
                             << " " << c.getStartPeriod()
                             << "-" << c.getEndPeriod() << "]"
                             << endl;
                    }
                }

                // ---------------- 離開 ----------------
                else if (choice == 5)
                {
                    break;
                }
            }
        }

        // ==================================================
        // 離開系統
        // ==================================================
        else if (choice == 3)
        {
            cout << "離開系統。" << endl;
            break;
        }

        else
        {
            cout << "無效選項。" << endl;
        }
    }

    return 0;
}
