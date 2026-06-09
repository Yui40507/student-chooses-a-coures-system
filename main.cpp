#include "student.h"
#include "course.h"

Student* findStudent(vector<Student>& students, const string& id) {
    auto it = find_if(students.begin(), students.end(),
        [&](const Student& s) {
            return s.getId() == id;
        });

    return it != students.end() ? &(*it) : nullptr;
}

Course* findCourse(vector<Course>& courses, const string& code) {
    auto it = find_if(courses.begin(), courses.end(),
        [&](const Course& c) {
            return c.getCode() == code;
        });

    return it != courses.end() ? &(*it) : nullptr;
}

int main() {

    vector<Student> students;
    vector<Course> courses;

    int choice;

    cout << "歡迎使用選課系統！" << endl;

    while (true) {

        cout << endl;
        cout << "===== 主選單 =====" << endl;
        cout << "1. 學生登入" << endl;
        cout << "2. 老師登入" << endl;
        cout << "3. 離開系統" << endl;
        cout << "請輸入選項：";

        cin >> choice;
        cin.ignore();

        if (choice == 1) {

            string sid;
            string pwd;

            cout << "輸入學生ID：";
            getline(cin, sid);

            Student* currentStudent =
                findStudent(students, sid);

            if (!currentStudent) {
                cout << "找不到該學生ID。" << endl;
                continue;
            }

            cout << "輸入密碼：";
            getline(cin, pwd);

            if (!currentStudent->verifyPassword(pwd)) {
                cout << "密碼錯誤！" << endl;
                continue;
            }

            cout << "登入成功！" << endl;

            while (true) {

                cout << endl;
                cout << "===== 學生選單 =====" << endl;
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

                if (choice == 1) {

                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course =
                        findCourse(courses, ccode);

                    if (course)
                        currentStudent->enroll(course);
                    else
                        cout << "找不到課程。" << endl;
                }

                else if (choice == 2) {

                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course =
                        findCourse(courses, ccode);

                    if (course)
                        currentStudent->drop(course);
                    else
                        cout << "找不到課程。" << endl;
                }

                else if (choice == 3) {

                    currentStudent->printCourses();
                }

                else if (choice == 4) {

                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course =
                        findCourse(courses, ccode);

                    if (course)
                        course->printStudents();
                    else
                        cout << "找不到課程。" << endl;
                }

                else if (choice == 5) {

                    if (courses.empty()) {

                        cout << "尚未建立任何課程。"
                             << endl;
                    }
                    else {

                        cout << endl;
                        cout << "===== 所有課程 ====="
                             << endl;

                        for (const auto& c : courses) {

                            cout
                                << c.getCode()
                                << " | "
                                << c.getTitle()
                                << " | "
                                << c.getCredits()
                                << "學分 | "
                                << c.getDay()
                                << " "
                                << c.getStartPeriod()
                                << "-"
                                << c.getEndPeriod()
                                << "節 | "
                                << c.getEnrolledCount()
                                << "/"
                                << c.getCapacity()
                                << endl;
                        }
                    }
                }

                else if (choice == 6) {

                    string newPassword;

                    cout << "輸入新密碼：";
                    getline(cin, newPassword);

                    currentStudent->setPassword(
                        newPassword
                    );

                    cout << "密碼修改成功！"
                         << endl;
                }

                else if (choice == 7) {

                    cout << "已登出。" << endl;
                    break;
                }

                else {

                    cout << "無效選項。" << endl;
                }
            }
        }

        else if (choice == 2) {

            cout << "老師登入成功！"
                 << endl;

            while (true) {

                cout << endl;
                cout << "===== 老師選單 ====="
                     << endl;

                cout << "1. 新增學生"
                     << endl;

                cout << "2. 新增課程"
                     << endl;

                cout << "3. 顯示課程學生名單"
                     << endl;

                cout << "4. 顯示所有課程"
                     << endl;

                cout << "5. 離開"
                     << endl;

                cout << "請輸入選項：";

                cin >> choice;
                cin.ignore();

                if (choice == 1) {

                    string id;
                    string name;

                    cout << "輸入學生ID：";
                    getline(cin, id);

                    cout << "輸入學生姓名：";
                    getline(cin, name);

                    students.emplace_back(
                        id,
                        name,
                        id
                    );

                    cout << "學生新增成功！"
                         << endl;
                }

                else if (choice == 2) {

                    string code;
                    string title;
                    string day;

                    int cap;
                    int credits;
                    int startPeriod;
                    int endPeriod;

                    cout << "輸入課程代碼：";
                    getline(cin, code);

                    cout << "輸入課程名稱：";
                    getline(cin, title);

                    cout << "輸入人數上限：";
                    cin >> cap;

                    cout << "輸入學分：";
                    cin >> credits;

                    cout << "輸入星期(Mon/Tue/Wed/Thu/Fri)：";
                    cin >> day;

                    cout << "輸入開始節次：";
                    cin >> startPeriod;

                    cout << "輸入結束節次：";
                    cin >> endPeriod;

                    cin.ignore();

                    courses.emplace_back(
                        code,
                        title,
                        cap,
                        credits,
                        day,
                        startPeriod,
                        endPeriod
                    );

                    cout << "課程新增成功！"
                         << endl;
                }

                else if (choice == 3) {

                    string ccode;

                    cout << "輸入課程代碼：";
                    getline(cin, ccode);

                    Course* course =
                        findCourse(courses, ccode);

                    if (course)
                        course->printStudents();
                    else
                        cout << "找不到課程。"
                             << endl;
                }

                else if (choice == 4) {

                    if (courses.empty()) {

                        cout << "尚未建立課程。"
                             << endl;
                    }
                    else {

                        for (const auto& c : courses) {

                            cout
                                << c.getCode()
                                << " | "
                                << c.getTitle()
                                << " | "
                                << c.getCredits()
                                << "學分 | "
                                << c.getDay()
                                << " "
                                << c.getStartPeriod()
                                << "-"
                                << c.getEndPeriod()
                                << "節 | "
                                << c.getEnrolledCount()
                                << "/"
                                << c.getCapacity()
                                << endl;
                        }
                    }
                }

                else if (choice == 5) {

                    cout << "離開老師模式。"
                         << endl;

                    break;
                }

                else {

                    cout << "無效選項。"
                         << endl;
                }
            }
        }

        else if (choice == 3) {

            cout << "感謝使用，再見！"
                 << endl;

            break;
        }

        else {

            cout << "無效選項。"
                 << endl;
        }
    }

    return 0;
}
