# C++——继承与多态
## 一、C++继承
### 1）继承
&ensp;&ensp;&ensp;&ensp;继承是实现代码重用的重要手段，继承是利用已存在的类的形式，在保持原有类特性的基础上进行扩展，增加功能。这样产生新的类，称为**派生类**。继承的语法是：在代码中和原来一样给出该类的名字，但在左括号前加一个冒号和基类的名字（对于多重继承，要给出多个基类名，用逗号隔开）。    
&ensp;&ensp;&ensp;&ensp;派生类继承基类的数据和函数，继承可以调用基类的函数实现自己的函数。

```C++
class A
{
public:
    void Func1(void);
    void Func2(void);
};

class B : public A   //B继承A
{
public:
    void Func3(void)
    {
        A::Func1();//先调用基类的函数
        ...        //自己的实现代码
    }
    void Func4(void)
    {
        ...  //自己的实现代吗
            A::Func2(); //后调用基类的函数
    }
};
```
### 2）成员访问限定符与继承的关系：公有派生、私有派生
|继承方式  |基类的public成员  |基类的protected成员  |基类的private成员  |继承引起的访问控制关系变化概括  
|--------- |----------------|--------------------|-------------------|----------------------
|`public`继承  |仍为`public`成员  |仍为`protected`成员  |不可见  |基类的非私有成员在子类的访问属性都不变  
|`protected`继承  |变为`protected`成员  |变为`protected`成员  |不可见  |基类的非私有成员都成为子类的保护成员  
|`private`继承  |变为`private`成员  |变为`private`成员  |不可见  |基类的非私有成员都成为子类的私有成员    

&ensp;&ensp;&ensp;&ensp;其中，**公有派生是主流**。

### 3）派生编程的步骤：
四大步：  

* 吸收基类的成员：不论是数据成员，还是函数成员，处构造函数与析构函数外全盘接受
* 改造基类成员：声明一个和某某类成员同名的新成员，对于成员函数参数表也应完全相同，这称为同名覆盖，否则是重载。派生类中的新成员就屏蔽了基类同名成员。
* 发展新成员：派生类新成员必须与基类成员不同名，他的加入保证派生类在功能上有所扩展。
* 重写构造函数与析构函数。所谓不能继承构造函数并不是不能利用基类的构造函数，而是把基类的构造函数作为新的构造函数的一部分或者说是调用基类的构造函数。

### 4）派生类构造函数的定义：

* 派生类构造函数的定义：(类外定义)
```
派生类名::派生类名（参数总表）:基类名1（参数名表1），基类名2（参数名表2），......，成员对象名1（成员对象参数名表1），成员对象名2（成员对象参数名表2），......

{

派生类新增成员的初始化；

}//所列出的成员全部为新增成员对象的名字
```

* 在构造函数的声明中，冒号及冒号以后的部分必须略去。
* 构造函数不能继承但是可以利用，把基类的构造函数作为新的类的构造函数的一部分，或者说是调用基类的构造函数。
* 派生类构造函数各部分执行的顺序：
    * 首先，调用基类的构造函数，按他们在派生类中的先后顺序依次调用。
    * 调用成员对象的构造函数按他们在类定义中声明的先后顺序，依次调用。
    * 派生类的构造函数体中的操作

>注意：
>* 在派生类构造函数中，只要基类不是使用无参的默认构造函数都要显示的给出基类名与参数表。
>* 如果基类没有定义构造函数，则派生类也可以不定义全部采用系统给定的默认构造函数。
>* 如果基类定义了带有形参表的构造函数派生类就应当定义构造函数。

### 5）派生类与基类的类型兼容性原则
* 子类拥有父类的所有属性和行为，子类是一种特殊的父类
* 子类对象可以直接当父类对象使用
* 子类对象可以直接赋值或初始化父类对象
* 父类对象的指针和引用可以直接指向子类对象
* 子类对象的指针和引用不能直接指向父类对象，但可以通过强制类型转换完成

```C++
class Person
{
public:
    void Display()
    {
        cout << _name << endl;
    }
protected:
    string _name;
};

class Student : public Person
{
public:
    int _num;
};

void Test()
{
    Person p;
    Student s;

    //子类对象可以赋值给父类对象
    p = s;
    //父类对象不可以赋值给子类对象
    //s = p;//error

    //父类对象的指针和引用可以指向子类对象
    Person *p1 = &s;
    Person& r1 = s;

    //子类对象的指针和引用不能指向父类的对象(但是可以通过强制类型转化完成)
    Student *p2 = (Student*)&p;
    Student& r2 = (Student&)p;
}
```
### 6）派生类的默认成员函数

&ensp;&ensp;&ensp;&ensp;在继承关系中，派生类如果没有显示定义这六个成员函数，编译系统会默认合成六个成员函数，即构造函数，拷贝构造函数，析构函数，赋值操作符重载，取地址操作符重载，`const`修饰的取地址操作符重载。
### 7）单继承与多重继承
* 单继承：一个子类只有一个直接父类
* 多重继承：一个子类有两个或两个以上直接父类

### 8）友元与继承
&ensp;&ensp;&ensp;&ensp;友元关系不能继承，基类的友元对派生类没有特殊的访问权限。
```C++
//友元与继承
class Person
{
    friend void Display(Person& p, Student& s);
protected:
        string _name; //姓名
};

class Student : public Person
{
protected:
    int _stuNum; //学号
};

void Display(Person& p, Student& s)
{
    cout << p._name << endl;
    cout << s._name << endl;
    cout << s._stuNum << endl;
}

void Test()
{
    Person p;
    Student s;
    Display(p, s);
}
```
### 9）继承与静态成员：
&ensp;&ensp;&ensp;&ensp;基类定义了static成员，则整个继承体系中只有一个这样的成员。无论派生出多少个子类，都只有一个`static`成员实例。即：如果我们重新定义了一个静态成员，所有在基类中的其他重载函数会被隐藏。
```C++
class dad
{
public:
static int a;
static int geta()
{
return a;
}
static int geta(int b)
{
return a + b;
}
};
int dad::a = 99;
class son :public dad
{
public:
static int a;//基类静态成员的属性将会被隐藏
static int geta(int b, int c)//重新定义一个函数，基类中重载的函数被隐藏
{
return a + b + c;
}
};
int son::a = 66;
class girl:public dad
{
public:
static int a;//基类静态成员的属性将会被隐藏
static void geta(int b, int c)//改变基类函数的某个特征，返回值或者参数个数，将会隐藏基类重载的函数
{
cout << a + b + c << endl;
}
};
int girl::a = 44;
void test()
{
son s;
girl g;
cout << s.a << endl;//输出66
cout << s.geta(1, 2) << endl;;//只能访问son类中的geta，不能访问父类中的geta
cout << g.a << endl;//输出44，只能访问girl中的a
g.geta(3, 4);//只能访问girl中的geta
}
```
### 10）虚基类：
#### 1.虚基类：
&ensp;&ensp;&ensp;&ensp;如果一个类派生有多个直接基类，而这些基类又有一个共同的基类，即菱形派生，则在最终的派生类中会保留该间接基类的共同基类的多份同名成员。在引用这些同名的成员时必须在派生类对象后增加直接基类，以免产生二义性，使其唯一的标识一个成员。如：`c1.A::diaplay()`。在一个类中保留间接共同基类的多分同名成员，这种现象是人们不希望出现的。C++提供虚基类的方法，使得在继承间接共同基类时只保留一份成员。
```C++
class  A//声明基类A
{…};
class B :virtual public  A//声明类B是类A的公用派生类，A是B的虚基类
{…};
class C :virtual public  A//声明类C是类A的公用派生类，A是C的虚基类
{…};

//注意：虚基类并不是在声明基类时声明的，而是在声明派生类时，指定继承方式时声明的。因为一个基类可以在生成一个类时作为虚基类，而在生成另一个派生类时不作为虚基类。
```
&ensp;&ensp;&ensp;&ensp;声明虚基类的一般形式：`class 派生类名：virtual 访问限定符继承方式  基类名`    
&ensp;&ensp;&ensp;&ensp;经过这样的声明后，当基类通过多条派生路径被一个派生类继承时，该派生类只继承该基类一次。    
&ensp;&ensp;&ensp;&ensp;需要注意的是，为了保证虚基类在派生类中只继承一次，应当在该基类的所有直接派生类中声明为虚基类，否则仍会出现对基类的多次继承。    
#### 2.虚基类的初始化与构造函数
&ensp;&ensp;&ensp;&ensp;虚基类的初始化如果在虚基类中定义了带参数的构造函数，而且没有定义默认构造函数，则在其所有派生类中（包括直接派生和间接派生的类中），通过构造函数的初始化表对虚基类进行初始化。
```C++
class
A//定义基类A
{
   A(int i){ } //基类构造函数，有一个参数};
class B :virtual public A
//A作为B的虚基类
{
   B(int n):A(n){ } //B类构造函数，在初始化表中对虚基类初始化
};
class C
:virtual public A //A作为C的虚基类
{
   C(int n):A(n){ }
//C类构造函数，在初始化表中对虚基类初始化
};
class D :public B,public C
//类D的构造函数，在初始化表中对所有基类初始化
{
   D(int n):A(n),B(n),C(n){ }
};
```
&ensp;&ensp;&ensp;&ensp;在定义类D的构造函数时，与以往的使用方法不同。规定：
* 在最后的派生类中，不仅要负责对直接基类进行初始化，还要负责对虚基类进行初始化。C++编译系统只执行最后的派生类对虚基类的构造函数的调用，而忽略虚基类的其他派生对（如类B和类C）虚基类的构造函数的调用,这样就保证虚基类的数据成员不会被多次初始化
* 使用多重继承时要格外小心，经常出现二义性问题，一般只有在比较简单和不易出现二义性的情况才使用多重继承，能用单一继承解决的问题就不要用多重继承。

## 二、C++多态
&ensp;&ensp;&ensp;&ensp;C++中的虚函数的作用主要是实现了多态的机制。关于多态，简而言之就是用父类型别的指针指向其子类的实例，然后通过父类的指针调用实际子类的成员函数。这种技术可以让父类的指针有“多种形态”。
### 1）多态的引入：
```C++
class Parent
{
public:
    Parent(int a){
        this->a = a;
    }
    printP(){
        cout<<"Parent"<<endll;
    }
private:
    int a;

};

class Son:public Parent{
public:
    Son(int b):Parent(10){
        this->b = b;
    }
    printP(){
        cout<<"Son"<<endll;
    }
private:
    int b;
};

void howtoPrint(Parent *base){
    base->printP();
}

void howtoPrint2(Parent &base){
    base.printP();
}
```
&ensp;&ensp;&ensp;&ensp;上边定义了两个类，并且父类与子类都有一个同名函数`printP()`，下面通过几种方式测试案例：   

* 定义一个基类指针，让指针分别指向基类与子类对象，然后调用`printP()`
```C++
void main(int argc, char const *argv[])
{
    Parent *p = NULL;
    Parent p1(20);
    Son s1(30);//

    p = &p1;//指针执行基类
    p1->printP();//

    p = &s1;//类型兼容性原则
    p->printP();
}

//两个执行的结果都是调用基类的printP()函数
```
* 定义基类的引用分别指向基类与派生类
```C++
void main(int argc, char const *argv[])
{


        Parent &base = p;//父类的别名
        base.printP();//执行父类

        Parent &base2 = s1;//别名
        base2.printP();//执行父类
}
//结果也都是调用父类的printP()函数
```
* 定义一个函数，即上边的`howtoPrint()`，函数参数为基类指针，然后定义一个指向基类的指针，让改指针分别指向基类对象与派生类对象
```C++
void main(int argc, char const *argv[])
{
    Parent *p = NULL;
    Parent p1(20);
    Son s1(30);

    p = &p1;
    howtoPrint(&p1);
    p = &s1;
    howtoPrint(&s1);
}
//结果都是执行父类的printP()函数
```
* 定义一个函数，即上边的`howtoPrint2()`函数，函数参数为基类对象的引用然后分别传入基类对象引用和子类对象引用：
```C++
void main(int argc, char const *argv[])
{
    Parent *p = NULL;
    Parent p1(20);
    Son s1(30);

    howtoPrint2(p1);
    howtoPrint2(s1);
}
```
&ensp;&ensp;&ensp;&ensp;上边的四种情形，不管我们怎么改变调用方式，始终都是调用的基类的函数。为了解决当传入子类对象时调用子类函数，传入基类对象时调用基类函数，C++提供了多态的解决方案。    
### 2）多态：
&ensp;&ensp;&ensp;&ensp;多态是面向对象程序设计的关键技术之一。若程序语言不支持多态，不能称之为面向对象的语言。利用多态技术，可以调用同一个函数名的函数，实现完全不同的功能。   
&ensp;&ensp;&ensp;&ensp;C++有两种多态：    
1. 编译时的多态：通过函数的重载与运算符的重载实现的
2. 运行时的多态：运行时的多态是指在程序运行前，无法根据函数名和参数来确定调用哪一个函数，必须在程序执行过程中，根据执行的具体情况来动态的确定。它是通过类继承关系和虚函数来实现的。目的是建立一种通用的程序。

### 3）虚函数：
&ensp;&ensp;&ensp;&ensp;虚函数是一个类的成员函数，在类成员函数前添加`virtual`关键字后，该函数就被称作虚函数。有了虚函数之后就可以根据传入对象的不同调用不同的成员函数。   
&ensp;&ensp;&ensp;&ensp;当在派生类中重新定义虚函数时，不必加关键字`virtual`。但重定义时不仅要同名，而且它的参数表和返回值类型必须全部与基类中的虚函数一样，否在会出错。   
&ensp;&ensp;&ensp;&ensp;以下为加了虚函数实现多态的结果：   
```C++
class Parent
{
public:
    Parent(int a){
        this->a = a;
    }
    virtual printP(){
        cout<<"Parent"<<endll;
    }
private:
    int a;

};

class Son:public Parent{
public:
    Son(int b):Parent(10){
        this->b = b;
    }
    printP(){ //子类的virtual写可不写，只需要父类写就可以了
        cout<<"Son"<<endll;
    }
private:
    int b;
};
```
&ensp;&ensp;&ensp;&ensp;基类与派生类的的同名函数要想实现多态，基类的同名函数前必须加上`virtual`关键字。  
&ensp;&ensp;&ensp;&ensp;下面调用上边的四个测试函数看问题是否解决：
```C++
//测试一：
void main(int argc, char const *argv[])
{
    Parent *p = NULL;
    Parent p1(20);
    Son s1(30);

    p = &p1;
    p1->printP();//执行父类的打印函数


    p = &s1;
    p->printP();//执行子类的打印函数
}

//测试二：
void main(int argc, char const *argv[])
{
    Parent p1(20);
    Son s1(30);
    
    Parent &base = p1;//父类的别名
    base.printP();//执行父类

    Parent &base2 = s1;//别名
    base2.printP();//执行子类 
}


//测试三：
void howtoPrint(Parent *base){ //一个调用语句执行不同的函数
    base->printP();
}

void main(int argc, char const *argv[])
{
    Parent p1(20);
    Son s1(30);
    howtoPrint(&p1);//父类
    howtoPrint(&s1);//子类
}

//测试四：
void howtoPrint2(Parent &base){//一个调用语句执行不同的函数
    base.printP();
}

void main(int argc, char const *argv[])
{
    Parent *p = NULL;
    Parent p1(20);
    Son s1(30);

    howtoPrint2(p1);//父类
    howtoPrint2(s1);//子类
}
```
### 4）多态实现的基础
1. 要有继承    
2. 要有虚函数重写
3. 父类指针（引用）指向子类对象

### 5）多态的理论基础
#### 1.静态联编与动态联编
联编：指一个程序块、代码之间相互关联的过程。    
* 静态联编：指程序的匹配连接在编译阶段实现。函数重载运算符重载都是静态联编
* 动态联编：指程序联编推迟到运行时进行，又称迟联编。`switch`、`if`语句都是动态联编的例子
#### 2.重载、重写、重定义
* 函数重载：
    * 函数重载必须在同一个类中进行
    * 子类无法重载父类函数，父类同名函数将被子类同名函数覆盖
    * 重载是在编译阶段根据参数类型和个数决定函数调用（静态联编）
* 函数重写：
    * 函数重写必须发生在子类与父类之间
    * 父类与子类的函数原型完全一样
    * 使用virtual声明之后能够产生多态（如果不写`virtual`关键字，称为重定义）
    * 非虚函数重写是重定义，虚函数重写是多态
### 6）多态实现原理——`VPTR`指针与虚函数表
&ensp;&ensp;&ensp;&ensp;主要根据编译器在何处动了手脚，从而支持了多态。    
&ensp;&ensp;&ensp;&ensp;从下面的代码来分析：   
```C++
class Parent{
    public:
        Parent(int a=0){
            this->a = a;}
        virtual void print(){ //编译器可能动手脚的地方1  
            cout<<"parent"<<endl;}  
    private:
        int a;
};

class Son:public Parent{
    public:
       Son(int a=0,int b=0):Parent(a){
           this->b = b;}
       void print(){
           cout<<"Son"<<endl;}
    private:
        int b;
    };

  void play(Parent *p){ //编译器可能动手脚的地方2  
        p->print();}

    void main(int argc, char const *argv[])
    {
        Parent p; //编译器可能动手脚的地方3  
        Son s;
        play(&s)
        return 0;
    }
```
&ensp;&ensp;&ensp;&ensp;真正绑定关系的地方就是上面代码的地方3处，就是创建对象的时候，这时候C++编译器会偷偷地给对象添加一个`vptr`指针。
