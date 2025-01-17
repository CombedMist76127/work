#include <iostream>
#include <cmath>
 
class Circle {
private:
    double radius; // 半径
public:
    Circle(double r) : radius(r) {} // 构造函数
 
    double area() const { // 计算并返回圆的面积
        return 3.14159 * radius * radius;
    }
 
    double circumference() const { // 计算并返回圆的周长
        return 2 * 3.14159 * radius;
    }
 
    void resize(double percent) { // 按指定百分比调整圆的半径
        radius *= (1 + percent / 100.0);
    }
};
 
int main() {
    Circle c1(10.0); // 创建一个半径为10的圆
    std::cout << "Circle c1: Area = " << c1.area() << ", Circumference = " << c1.circumference() << std::endl;
 
    c1.resize(20); // 圆的半径增加20%
    std::cout << "After resizing, Circle c1: Area = " << c1.area() << ", Circumference = " << c1.circumference() << std::endl;
 
    return 0;
}
