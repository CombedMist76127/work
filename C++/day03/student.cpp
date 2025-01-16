#include <iostream>
#include <string>
 
class Student {
private:
    std::string name;
    std::string studentId;
    int score;
 
public:
    Student(const std::string& name, const std::string& studentId, int score)
        : name(name), studentId(studentId), score(score) {}
 
    void viewScore() const {
        std::cout << "姓名: " << name << "\n学号: " << studentId << "\n成绩: " << score << std::endl;
    }
 
    // 其他setter和getter方法（如果需要）
};
 
int main() {
    Student student("张三", "123456789", 90);
    student.viewScore();
    return 0;
}
