# C++泛型编程
## 一、基本思想
&ensp;&ensp;&ensp;&ensp;泛型编程（Generic Programming）是一种语言机制，通过它可以实现一个标准的容器库。    
&ensp;&ensp;&ensp;&ensp;像类一样，泛型也是一种抽象数据类型，但是泛型不属于面向对象，它是面向对象的补充和发展。在面向对象编程中，当算法与数据类型有关时，面向对象在对算法的抽象描述方面存在一些缺陷。    
&ensp;&ensp;&ensp;&ensp;**泛型在C++中的主要实现为模板函数和模板类。**    
&ensp;&ensp;&ensp;&ensp;通常使用普通的函数实现一个与数据类型有关的算法是很繁琐的，比如两个数的加法，要考虑很多类型：
```cpp
int add(int a,int b) { return a+b; }
float add(float a,float b) { return a+b; }
```
&ensp;&ensp;&ensp;&ensp;在C++中可以通过函数重载来解决这个问题，但是反复写相同算法的函数是比较辛苦的，更重要的是函数重载是静态编译，运行时占用过多内存。    
&ensp;&ensp;&ensp;&ensp;在此我们可以用C++的模板函数来表达通用型的函数，如下：   
```cpp
template<typename T>            // 模板声明
T add(T a,T b) { return a+b; }  // 注意形参和返回值的类型
```
&ensp;&ensp;&ensp;&ensp;这时C++编译器会根据`add`函数的参数类型来生成一个与之对应的带具体参数类型的函数并调用。   
```cpp
#include <iostream>
using namespace std;

template <typename T>
T add(T a,T b)   //注意形参和返回类型
{ 
    return a+b;
} 
void main()
{
    int num1, num2, sum; 
    cin>>num1>>num2;
    sum=add(num1,num2); //用int匹配模版参数T，若sum,num1,num2类型不一致则无法匹配。
    cout<<sum;
}
```
## 二、函数模板
### 1）性质
1. 函数模板并不是真正的函数，它只是C++编译生成具体函数的一个模子。   
2. 函数模板本身并不生成函数，实际生成的函数是替换函数模板的那个函数，比如上例中的`add(sum1,sum2)`，这种替换是编译期就绑定的。   
3. 函数模板不是只编译一份满足多重需要，而是为每一种替换它的函数编译一份。   
4. 函数模板不允许自动类型转换。   
5. 函数模板不可以设置默认模板实参。比如`template<typenameT=0>`不可以。

### 2）语法
&ensp;&ensp;&ensp;&ensp;下面的几种写法是等效的并且`class`和`typename`是可以互换的。    
```cpp
C++模版函数语法
template <typename模版参数列表…>
函数返回类型 函数名（形参列表…）

template <typenameT1, typename T2>         // template <classT1,class T2> 
T1 fun(T1, T2, int )
{ //…..}
template <typenameT1,T2> T1 fun(T1, T2, int )
{ //…..}

=============================================
C++模版类的语法
template <class模版参数列表…>
class 类名
{ //类体}
成员的实现…

//类声明部分，有两个模板参数T1，T2
template <classT1, class T2 >
class A {
    private:
    int a;
    T1 b; //成员变量也可以用模板参数
public:
    int fun1(T1 x, int y );
    T2 fun2(T1 x, T2 y);
}

//类实现部分
template <classT1, class T2 >
int A<T1>:: fun1(T1 x, int y ){//实现…… }
template <classT1, class T2 >
T2 A<T1,T2>:: fun2(T1 x, T2 y) {//实现…… }

//使用类A
int main( ) {
    A<int, float> a;        //定义对象a,并用int替换T1, float替换T2
                            //实例化a,调用a的属性和方法……
}
```
&ensp;&ensp;&ensp;&ensp;由上例可以看出, 类模板参数`T1`，`T2`对类的成员变量和成员函数均有效。   
&ensp;&ensp;&ensp;&ensp;在C++编程中，当你要实现的一个类的某些成员函数和成员变量的算法数据类型有关，可以考虑用类模板。C++版的数据结构算法大都用类模板实现。    
## 三、类模板
**类模板的性质：**   
1. 类模板不是真正的类，它只是C++编译器生成具体类的一个模子。
2. 类模板可以设置默认模板实参。
