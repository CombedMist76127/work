# C++扩展
## 一、动态内存
&ensp;&ensp;&ensp;&ensp;动态内存管理是C++中一个重要概念，涉及在程序运行时动态申请和释放内存。与静态内存分配（如栈内存）不同，动态内存分配允许程序在需要时申请内存，使用完后再释放，这对于处理大小不确定的对象非常有用。    
&ensp;&ensp;&ensp;&ensp;在C++中，动态内存主要通过`new`和`delete`运算符进行分配和释放。
### 1）使用`new`分配内存
#### 1.动态分配单个对象
**初始化：**
```C++
int *pi1 = new int; // 默认初始化
int *pi2 = new int(); // 值初始化
int *pi2 = new int(1024); // 直接初始化
string *ps = new string(10,'9');
// 若 obj 是一个 int ，则 p1 是 int* ；
// 不能用 {...} 代替 (obj) 包含多个对象；
auto p1 = new auto(obj);
```
#### 2.动态分配多个对象
**初始化：**
```C++
int *pia = new int[get_size()]; // 维度不必是常量，但是必须是整形
int *p1 = new int[42]; // 未初始化

// 以下为上一行的等价调用
typedef int arrT[42]；
int *p = new arrT;
int *p2 = new int[42](); // 值初始化
// 初始值列表中没有给定初始值的元素进行“值初始化”，如果初始值列表中元素超出，new会失败
int *p3 = new int[5]{1,2,3,4,5};
```
> **使用注意：**
> * 大多数应用应该使用标准库容器而不是动态分配的数组
> * 动态分配数组的类必须定义自己版本的拷贝、复制、销毁对象的操作

### 2）使用`delete`释放内存
* `delete`单个对象：`delete p`;
* `delete`动态数组：`delete [] pa`;

> **注意：**
> * 不要`delete`非`new`分配的对象
> * 不要重复`delete`
> * 可以`delete`空指针
> * 可以`delete`动态分配的`const`对象
## 二、引用
### 1）定义
&ensp;&ensp;&ensp;&ensp;引用并非对象，别名**未分配空间**。引用就是某个目标变量的“别名”(alias)，对引用的操作与对变量直接操作效果完全相同。
### 2）形式   
&ensp;&ensp;&ensp;&ensp;引用的形式一般为：`int &a = b;`
### 3）理解与使用：
&ensp;&ensp;&ensp;&ensp;申明一个引用的时候，必须初始化。引用声明完毕后，相当于目标变量名有两个名称，即该目标原名称和引用名，不能再把该引用名作为其他变量名的别名。声明一个引用，不是新定义了一个变量，它只表示该引用名是目标变量名的一个别名，它本身不是一种数据类型 ，因此引用本身不占存储单元，系统也不给引用分配存储单元。不能建立数组的引用。    
> **注意**
> * 非常量引用不能绑定到字面值或表达式的计算结果    
> * 一般来说， 引用类型和绑定的对象类型需严格匹配    
> * 程序把引用和其初始值绑定到一起（对引用的操作都在其绑定的对象上进行），因此一旦初始化完成，无法另引用重新绑定到另外一个对象。因此必须初始化    
> * 引用本身并非对象，故不能定义引用的引用    
### 4）引用与指针
* 指针不同与引用， 指针本身就是一个对象
* 因为引用不是对象，没有实际地址，所以不能定义指向引用的指针
* 指针是一个对象，所以 存在对指针的引用
* 一般来说，指针类型和指向的对象类型也需严格匹配
* 编译器并不负责检查试图拷贝或以其它方式访问无效指针
* 和试图使用未经初始化的变量一样，使用未经无效指针的 后果无法估计
* 空指针：不指向任何对象（不要混淆空指针和空类型`(void)`的指针）
```C++
int *p1 = nullptr; (C++11)
int *p2 = 0;
int *p3 = NULL; //#include cstdlib
```
* 把 int 变量直接赋给指针是错误的，即使变量的值恰好等于0
* 空类型(void)指针用于存放

## 三、函数
### 1）默认参数
#### 1.概念
&ensp;&ensp;&ensp;&ensp; C++语言中的函数，可以在声明函数时，为函数参数定义一个默认值，**可以简化函数调用和提高代码重用性**。    
#### 2.运行机制
&ensp;&ensp;&ensp;&ensp;在调用有默认参数值的函数时，如果没有提供某个有默认值参数的实参，那么编译器在编译阶段，就会使用默认值当做实参。    
#### 3.代码示例
&ensp;&ensp;&ensp;&ensp;下面的代码中，为`void fun(int num = 5) `函数，提供了默认参数值5。    
&ensp;&ensp;&ensp;&ensp;如果调用`fun`函数，不传入参数，则使用默认参数值5；不传入参数，打印的值为5；    
&ensp;&ensp;&ensp;&ensp;如果调用`fun`函数，显示传入参数，则使用传入的参数；传入参数7，则打印的值为7。   
```C++
// 导入标准io流头文件，其中定义了std命名空间
#include <iostream>
// 导入std命名空间
using namespace std;

// 设置了默认参数的函数
void fun(int num = 5) {
    cout << "num = " << num << endl;
}

int main() {
    // 不传入参数，使用默认参数值5
    fun();
    // 显式传入参数值7
    fun(7);
    
    // 控制台暂停
    system("pause");

    return 0;
}
```
#### 4.定义规则
&ensp;&ensp;&ensp;&ensp;默认参数必须定义在参数列表的末尾。一旦在函数的参数列表中出现了默认参数，那么之后的所有参数都必须有默认参数，否则编译时会报错。
### 2）占位参数
#### 1.概念
&ensp;&ensp;&ensp;&ensp;占位参数是指在函数定义时只指定参数类型，而不指定具体参数名称的参数。这些参数的作用是在调用函数时占据一个位置，以便在以后的开发过程中可以根据需要传递不同类型的参数。
> **注意：** 占位参数在函数体内是无法被使用的
#### 2.代码示例
```C++
int func(int x,int );

... ...

func(1,2);   //调用func函数
```
### 3）函数重载
#### 1.概念
&ensp;&ensp;&ensp;&ensp;函数重载是指在同一个作用域中定义几个同名但参数数量或类型不同的函数。编译器通过函数参数的类型和数量来区分哪个重载函数被调用。   
&ensp;&ensp;&ensp;&ensp;函数重载概念是编程中的一个重要特性，它允许在同一作用域内定义多个同名函数，但这些函数的参数列表（参数的数量、类型或顺序）必须不同。通过这种方式，函数重载为程序员提供了更大的灵活性，使得他们可以根据不同的参数类型和数量来调用不同的函数实现，从而实现功能的多样化和代码的复用。
#### 2.代码示例
&ensp;&ensp;&ensp;&ensp;以下是一个C++函数重载的例子：
```C++
#include <iostream>
using namespace std;
 
// 函数重载示例
void print(int a) {
    cout << "Print int: " << a << endl;
}
 
void print(double a) {
    cout << "Print double: " << a << endl;
}
 
void print(const char* a) {
    cout << "Print string: " << a << endl;
}
 
int main() {
    print(5);      // 调用 print(int a)
    print(5.5);    // 调用 print(double a)
    print("Hello"); // 调用 print(const char* a)
    return 0;
}
```
&ensp;&ensp;&ensp;&ensp;在这个例子中，`print`函数被重载了三次，每个版本接受一个`int`、`double`或`const char*`类型的参数。在`main`函数中，当调用`print`时，编译器会根据传入参数的类型或数量来选择合适的函数版本。
#### 3.分类
&ensp;&ensp;&ensp;&ensp;C++函数重载可以分为以下几种分类：
* 参数个数不同：在同一个作用域中，函数名相同但参数个数不同的多个函数被视为重载函数。
* 参数类型不同：在同一个作用域中，函数名相同但参数类型不同的多个函数被视为重载函数。
* 参数顺序不同：在同一个作用域中，函数名相同但参数顺序不同的多个函数被视为重载函数。

## 四、面向对象编程
### 1）概念
&ensp;&ensp;&ensp;&ensp;面向对象编程（OOP）是一种编程范式，它将数据（属性）和操作数据的方法（函数）封装在单个单元中，这个单元被称为对象。OOP的核心思想是将现实世界中的事物抽象为对象，并通过类和对象来实现代码的组织和重用。
### 2）核心特征
&ensp;&ensp;&ensp;&ensp;C++中的面向对象编程具有三大核心特性：**封装**、**继承**和**多态**。  
* 封装（Encapsulation）‌：封装是将数据和操作数据的函数绑定在一起，并对外隐藏对象的内部实现细节，仅对外提供公共的访问接口。这有助于保护对象的状态，避免外部代码直接访问和修改对象的内部数据。
* 继承（Inheritance）‌：继承是一种层次结构，允许一个类（派生类）继承另一个类（基类）的属性和方法。派生类可以重用基类的代码，并添加或重写基类的方法，从而实现代码的复用和扩展。
* 多态（Polymorphism）‌：多态允许使用基类的引用或指针来调用派生类中的重写方法。这意味着同一个函数调用可以根据调用对象的实际类型执行不同的代码，从而提高了代码的灵活性和可扩展性。
## 五、UML类图
### 1）概念
&ensp;&ensp;&ensp;&ensp;UML（统一建模语言）类图是一种用于描述面向对象系统中类及其相互关系的图形表示方法。在C++项目中，UML类图可以帮助开发者理解和设计类的结构、继承关系、关联、聚合等。
### 2）主要元素
一个典型的UML类图包含以下几个主要元素：   
**1.类（Class）‌：** 用矩形表示，包含三部分：类名、属性和方法。   
* 类名‌：位于矩形的顶部中央。
* 属性（Attributes）‌：位于矩形的上半部分，表示类的成员变量。
* 方法（Methods）‌：位于矩形的下半部分，表示类的成员函数。

**2.关系（Relationships）‌：**    
* 关联（Association）‌：用实线表示，表示类与类之间的一种联系。可以在线上添加多重性（multiplicity）来说明一个类的对象可以与另一个类的多少个对象关联。
* 继承（Generalization/Inheritance）‌：用带空心三角形的实线表示，指向基类（父类）。  
* 实现（Realization/Interface Implementation）‌：用带空心菱形的实线表示，指向接口。
* 依赖（Dependency）‌：用带箭头的虚线表示，表示一个类依赖于另一个类。
* 聚合（Aggregation）‌：用带空心菱形的实线表示，表示一个类包含另一个类的对象，但两个类的生命周期独立。
* 组合（Composition）‌：用带实心菱形的实线表示，表示一个类包含另一个类的对象，且两个类的生命周期密切相关。

### 3）代码示例
&ensp;&ensp;&ensp;&ensp;假设我们有一个简单的C++程序，包含一个`Person`类和一个`Student`类，`Student`继承自`Person`。我们可以为这个系统设计一个简单的UML类图。
```C++
// Person.h
class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a);
    void setName(std::string n);
    std::string getName();
    void setAge(int a);
    int getAge();
};

// Student.h
class Student : public Person {
private:
    std::string studentId;

public:
    Student(std::string n, int a, std::string id);
    void setStudentId(std::string id);
    std::string getStudentId();
};
```
**UML类图描述**   
1‌.Person类‌   
* 类名：Person   
* 属性：      
    * `- name: std::string`
    * `- age: int`

* 方法：   
    * `+ Person(std::string, int)`
    * `+ setName(std::string): void`
    * `+ getName(): std::string`
    * `+ setAge(int): void`
    * `+ getAge(): int`

2.Student类‌     
* 类名：Student   
* 属性：   
    * `- studentId: std::string`
* 方法：   
    * `+ Student(std::string, int, std::string)`
    * `+ setStudentId(std::string): void`
    * `+ getStudentId(): std::string`
* 继承关系：  
    * Student继承自Person（带空心三角形的实线）

### 4）绘制和使用方法
‌**1.选择工具‌：**    
&ensp;&ensp;&ensp;&ensp;有许多工具可以用来绘制UML类图，如Visual Paradigm、StarUML、PlantUML、Lucidchart等。

‌**2.绘制步骤‌：**
* 识别系统中的类及其属性。
* 确定类的方法。
* 识别类之间的关系（继承、实现、关联、聚合等）。
* 使用工具绘制类图，添加类、属性、方法和关系。

‌**3.使用‌：**
* UML类图可以用于系统设计阶段的沟通和讨论。
* 可以作为开发过程中的文档，帮助新加入的成员快速理解系统结构。
* 可以在代码实现过程中作为参考，确保实现符合设计。
