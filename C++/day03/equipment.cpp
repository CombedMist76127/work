#include <iostream>
#include <vector>
#include <string>

// 定义学生类
class Student {
public:
    std::string name;
    int id;
    int age;
    float grade;

    // 构造函数
    Student(std::string n, int i, int a, float g)
        : name(n), id(i), age(a), grade(g) {}
};

// 定义学生管理类
class StudentManager {
private:
    std::vector<Student> students;

public:
    // 添加学生
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    // 删除学生
    void deleteStudent(int id) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it);
                std::cout << "学生删除成功！" << std::endl;
                return;
            }
        }
        std::cout << "未找到该学生！" << std::endl;
    }

    // 修改学生信息
    void modifyStudent(int id, const Student& newStudent) {
        for (auto& student : students) {
            if (student.id == id) {
                student = newStudent;
                std::cout << "学生信息修改成功！" << std::endl;
                return;
            }
        }
        std::cout << "未找到该学生！" << std::endl;
    }

    // 显示所有学生信息
    void displayStudents() const {
        for (const auto& student : students) {
            std::cout << "姓名: " << student.name
                      << ", 学号: " << student.id
                      << ", 年龄: " << student.age
                      << ", 成绩: " << student.grade << std::endl;
        }
    }
};

int main() {
    StudentManager manager;

    // 添加一些学生
    manager.addStudent(Student("张三", 1, 20, 85.5));
    manager.addStudent(Student("李四", 2, 21, 90.0));
    manager.addStudent(Student("王五", 3, 22, 78.0));

    // 显示所有学生信息
    std::cout << "当前学生列表：" << std::endl;
    manager.displayStudents();

    // 删除一个学生
    manager.deleteStudent(2);

    // 显示所有学生信息
    std::cout << "删除后的学生列表：" << std::endl;
    manager.displayStudents();

    // 修改一个学生信息
    manager.modifyStudent(1, Student("张三（修改后）", 1, 21, 88.8));

    // 显示所有学生信息
    std::cout << "修改后的学生列表：" << std::endl;
    manager.displayStudents();

    return 0;
}
