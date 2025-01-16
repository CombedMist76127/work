#include <cmath>
 
class Circle {
public:
    Circle(int x, int y, int r) : center(x, y), radius(r) {}
 
    // 判断两个圆是否相切
    bool isTangentTo(const Circle& other) const {
        int distanceSquared = (center - other.center).getSquaredLength();
        int sumOfRadii = radius + other.radius;
        int differenceOfRadii = std::abs(radius - other.radius);
 
        // 如果两个圆相切，它们的半径之和减去两个圆半径的差的绝对值应该等于两圆心距的平方
        return distanceSquared == sumOfRadii - differenceOfRadii &&
               distanceSquared > 0 && sumOfRadii > differenceOfRadii;
    }
 
private:
    Point center; // 假设有一个已定义的Point类来表示圆心
    int radius; // 圆的半径
};
