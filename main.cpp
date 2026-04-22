#include"student.h"
#include "course.h"

Student* findStudent(vector<Student>& students, const string& id) {
    auto it = find_if(students.begin(), students.end(), [&](const Student& s) {
        return s.getId() == id;
        });
    return it != students.end() ? &(*it) : nullptr;
}

Course* findCourse(vector<Course>& courses, const string& code) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
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

        cout << endl << "請選擇登入方式：" << endl;
        cout << "1. 學生登入" << endl;
        cout << "2. 老師登入" << endl;
        cout << "3. 離開系統" << endl;
        cout << "請輸入選項：";

        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            cout << "輸入學生ID：";
            string sid, pwd;
            getline(cin, sid);
            Student* currentStudent = findStudent(students, sid);

            if (currentStudent) {
                cout << "輸入密碼：";
                getline(cin, pwd);
                if (currentStudent->verifyPassword(pwd)) {
                    cout << "登入成功！" << endl;
                    while (true) {
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

                        if (choice == 1) {
                            string ccode;
                            cout << "輸入課程代碼：";
                            getline(cin, ccode);
                            Course* course = findCourse(courses, ccode);
                            if (course) currentStudent->enroll(course);
                            else cout << "找不到課程。" << endl;
                        }
                        else if (choice == 2) {
                            string ccode;
                            cout << "輸入課程代碼：";
                            getline(cin, ccode);
                            Course* course = findCourse(courses, ccode);
                            if (course) currentStudent->drop(course);
                            else cout << "找不到課程。" << endl;
                        }
                        else if (choice == 3) {
                            currentStudent->printCourses();
                        }
                        else if (choice == 4) {
                            string ccode;
                            cout << "輸入課程代碼：";
                            getline(cin, ccode);
                            auto cit = find_if(courses.begin(), courses.end(), [&](Course& c) {
                                return c.getCode() == ccode;
                                });
                            if (cit != courses.end()) {
                                cit->printStudents();
                            }
                            else {
                                cout << "找不到該課程。" << endl;
                            }
                        }

                        else if (choice == 5) {
                            if (courses.empty()) {
                                cout << "尚未建立任何課程。" << endl;
                            }
                            else {
                                cout << "所有課程清單：" << endl;
                                for (const auto& c : courses) {
                                    cout << " - " << c.getCode() << ": " << c.getTitle()
                                        << "（已修人數：" << c.getEnrolledCount()
                                        << " / 上限：" << c.getCapacity() << "）" << endl;
                                }
                            }
                        }
						else if (choice == 6) {
							string newPassword;
							getline(cin, newPassword);
							currentStudent->setPassword(newPassword);
							cout << "密碼已更改成功！" << endl;
						}
						else if (choice == 7) {
							cout << "已登出，感謝使用！" << endl;
							break;
						}
                        else {
                            cout << "無效的選項，請重新輸入。" << endl;
                        }
                    }
				}
				else {
					cout << "密碼錯誤，請重新登入。" << endl;
			}
			}
			else {
				cout << "找不到該學生ID。" << endl;
			}
		}
        else if (choice == 2) {
            cout << "老師登入成功！" << endl;

            while (true) {
                cout << endl << "===== 老師選課系統 =====" << endl;
                cout << "1. 新增學生" << endl;
                cout << "2. 新增課程（含人數上限)" << endl;
                cout << "3. 顯示課程學生名單" << endl;
                cout << "4. 顯示所有課程" << endl;
                cout << "5. 離開" << endl;
                cout << "請輸入選項：";
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    string id, name;
                    cout << "輸入學生ID：";
                    getline(cin, id);
                    cout << "輸入學生姓名：";
                    getline(cin, name);
                    students.emplace_back(id, name, id);
                    cout << " 學生已新增。" << endl;
                }
                else if (choice == 2) {
                    string code, title;
                    int cap;
                    cout << "輸入課程代碼：";
                    getline(cin, code);
                    cout << "輸入課程名稱：";
                    getline(cin, title);
                    cout << "輸入人數上限：";
                    cin >> cap;
                    cin.ignore();
                    courses.emplace_back(code, title, cap);
                    cout << "課程已新增。" << endl;
                }
                else if (choice == 3) {
                    string ccode;
                    cout << "輸入課程代碼：";
                    getline(cin, ccode);
                    auto cit = find_if(courses.begin(), courses.end(), [&](Course& c) {
                        return c.getCode() == ccode;
                        });
                    if (cit != courses.end()) {
                        cit->printStudents();
                    }
                    else {
                        cout << "找不到該課程。" << endl;
                    }
                }
                else if (choice == 4) {
                    if (courses.empty()) {
                        cout << "尚未建立任何課程。" << endl;
                    }
                    else {
                        cout << "所有課程清單：" << endl;
                        for (const auto& c : courses) {
                            cout << " - " << c.getCode() << ": " << c.getTitle()
                                << "（已修人數：" << c.getEnrolledCount()
                                << " / 上限：" << c.getCapacity() << "）" << endl;
                        }
                    }
                }
                else if (choice == 5) {
                    cout << "感謝使用，再見！" << endl;
                    break;
                }
                else {
                    cout << "無效的選項，請重新輸入。" << endl;
                }
            }
        }
        else if (choice == 3) {
            cout << "你已選擇離開系統。" << endl;
            break;
        }
        else
        {
            cout << "無效的選擇，請重新選擇！" << endl;
        }
    }
    return 0;
}
