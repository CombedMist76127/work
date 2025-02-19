# C++基础
## 一、C++输入输出流的使用
### 示例程序
#### 输出
```cpp
#include <iostream>
using namespace std;

int main_1() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```
#### 输入
```cpp
#include "iostream"
using namespace std;

int main()
{
    char name[128];
    char ch = 'A';
    cin >> name;
    cout << name << endl;
    cout << static_cast<int>(ch) << endl;

    return 0;
}
```
## 二、C++命名空间
### 1.**命名空间如何使用**    
&ensp;&ensp;&ensp;&ensp;程序中使用的是`std::cout`和`std::cin`，而不是直接写`cout`和`cin`。这是因为C++中的所有标准库内容都放在了一个叫"std"的命名空间里。命名空间的作用是为了避免不同代码之间的名字冲突。   
### 2.**如何自己编写命名空间**       
&ensp;&ensp;&ensp;&ensp;在C++中，我们可以自己定义命名空间，将相关的变量、函数等封装到一个命名空间里，避免与其他部分的代码产生冲突。定义命名空间的基本格式如下：
```cpp
namespace 命名空间名{
	数据类型1 变量1;
	数据类型2 变量2;
	...
	数据类型n 变量n;
}
```
### 3.**命名空间冲突的问题**   
* 当命名空间中的变量与全局变量发生冲突时，通常使用作用域运算符`::` 来访问全局变量，避免歧义。这种方式我们称为“匿名空间”或者“域调用”。
* 当命名空间中的变量与局部变量发生冲突时，程序会优先使用局部变量。此时，可以通过命名空间名来明确使用命名空间中的变量。

### 4.**命名空间嵌套**    
&ensp;&ensp;&ensp;&ensp;在C++中，命名空间不仅可以独立存在，还可以嵌套在其他命名空间中。嵌套命名空间的作用是将更细粒度的功能模块分组管理。通过命名空间的嵌套，我们可以进一步组织代码，避免命名冲突。   
```cpp
#include <iostream>
#include <cstring>


using namespace std;
// 命名空间问题

namespace group {
	int value;
	namespace zhangsan {
		int value;
	}
	namespace lisi {
		int value;
	}
}
using namespace group;
int main()
{
	// 访问问题
	lisi::value = 60;
	zhangsan::value = 50;
	return 0;
}
```
## 三、C++中的字符串   
### 1.**赋值操作**    
&ensp;&ensp;&ensp;&ensp;C++ 的`string`类支持多种赋值方式：
```cpp
string s1 = "Hello";      // 直接赋值
string s2;
s2 = "World";             // 使用赋值运算符
string s3(s1);            // 拷贝构造
string s4(5, 'A');        // 重复字符赋值，s4 = "AAAAA"
```
### 2.**查找和替换**    
&ensp;&ensp;&ensp;&ensp;`string`提供了`find()`和`replace()`函数用于查找和替换子字符串：
```cpp
string s = "Hello, World!";
size_t pos = s.find("World");  // 查找子字符串 "World"
if (pos != string::npos) {
    s.replace(pos, 5, "C++");  // 替换为 "C++"
}
```
### 3.**字符串比较**    
&ensp;&ensp;&ensp;&ensp;C++ 中可以直接使用关系运算符（如 ==, !=, <, > 等）来比较 string 对象：
```cpp
string s1 = "apple";
string s2 = "banana";

if (s1 == s2) {
    cout << "The strings are equal" << endl;
} else if (s1 < s2) {
    cout << "s1 comes before s2" << endl;
}
```
### 4.**字符串存取**   
&ensp;&ensp;&ensp;&ensp;可以使用下标操作符 [] 或 at() 方法来访问和修改字符串中的字符：
```cpp
string s = "Hello";
char c = s[1];      // 访问第二个字符 'e'
char c2 = s.at(2);  // 使用 at() 方法访问第三个字符 'l'
```
**注意**："[]"不会检查越界，而"at()"会进行越界检查。   
### 5.**字符串插入**   
&ensp;&ensp;&ensp;&ensp;使用`insert()`函数可以在指定位置插入子字符串：
```cpp
string s = "Hello!";
s.insert(5, " C++");  // 在索引5的位置插入 " C++"，结果为 "Hello C++!"
```
### 6.**字符串删除**   
&ensp;&ensp;&ensp;&ensp;`string`类提供`erase()`函数来删除字符串中的部分内容：
```cpp
string s = "Hello, C++!";
s.erase(5, 7);  // 从索引5开始，删除7个字符，结果为 "Hello"
```
### 7.**字符串清空**   
&ensp;&ensp;&ensp;&ensp;可以使用 clear() 函数来清空字符串的内容：
```cpp
string s = "Hello!";
s.clear();  // 清空字符串，s 变为空字符串 ""
```
### 8.**风格转换**   
#### **C++ 字符串转风格字符串**    
&ensp;&ensp;&ensp;&ensp;使用`string`类的`.c_str()`成员函数可以将C++字符串转换为C风格的字符串`（const char*）`。
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string cppStr = "Hello, C++";
    const char* cStr = cppStr.c_str();  // 转换为 C 风格字符串
    printf("%s\n", cStr);  // 使用 C 风格函数
    return 0;
}
```
#### **C风格字符串转C++字符串**    
&ensp;&ensp;&ensp;&ensp;C风格的字符串（字符数组）可以直接赋值给C++的`string`，C++会自动进行转换。
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    const char* cStr = "Hello, C";
    string cppStr = cStr;  // 自动转换为 C++ 字符串
    cout << cppStr << endl;
    return 0;
}
```
## 四、C++中的结构体    
&ensp;&ensp;&ensp;&ensp;C++中结构体和类的唯一的区别，就是默认的访问控制权限不同：   
* 类中成员的默认访问权限：private    
* 结构体中成员的默认访问权限：public

&ensp;&ensp;&ensp;&ensp;在C++中，结构体与类几乎没有区别（除了默认的访问权限外，结构体默认是`public`的），可以包含数据成员和成员函数。这使得C++的结构体功能大大增强，能够支持面向对象编程。    
## 五、C++中的bool类型   
&ensp;&ensp;&ensp;&ensp;bool类型是C++中用于表示布尔值的数据类型，表示真或假。   
### **取值**   
* true：表示真，数值为 1。   
* false：表示假，数值为 0。   
### **使用示例**   
```cpp
#include <iostream>
using namespace std;

int main() {
    bool isTrue = true;   // 布尔变量赋值为 true
    bool isFalse = false; // 布尔变量赋值为 false

    cout << isTrue << endl;  // 输出 1
    cout << isFalse << endl; // 输出 0

    return 0;
}
```
## 六、git在Linux环境下的配置    
**git自动推送**   
&ensp;&ensp;&ensp;&ensp;linux下git的安装：   
`sudo apt-get install git`   
### 1.**绑定公钥**   
```
# 1 绑定ssh 公钥   绑定linux 和 gitee 的公钥
	# 在linux 中输入 以下指令 创建 ssh 公秘钥

linux:~$ ssh-keygen -t rsa

# 会出现以下内容直接三个回车即可

Generating public/private rsa key pair.
Enter file in which to save the key (/home/student/.ssh/id_rsa): 
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/student/.ssh/id_rsa.
Your public key has been saved in /home/student/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:RAWcRj9btk/1CfCGdItyXdZ08q/eEDeP6P88T2V1w/o student@student-machine
The key's randomart image is:
+---[RSA 2048]----+
|       o++.o ..++|
|       .+.. B =oo|
|       ...o+o* o=|
|       .  o=..o.B|
|        S . ..oo*|
|             +.*+|
|            . =Eo|
|           . . * |
|            ..o.B|
+----[SHA256]-----+
```
先在linux 中获取公钥
```
# 将公钥放到gitee中

# 输入指令 可以获取linux中的公钥

linux:~$ cat ~/.ssh/id_rsa.pub
```
### 2.将获取的公钥放入到gitee中   
* **点击设置**，完成公钥对接；   
* **获取仓库的ssh**；   
```
# 配置用户名和邮箱
git config --global user.name "your name"
git config --global user.email "your email"

# 创建一个新文件夹 工作区
	# 创建工作区文件夹

	mkdir C++_Code
	cd C++_Code/

	# 创建 .git 文件
	git init

# 绑定远程地址
# 注意 绑定的地址 是ssh 地址 不是 https 地址
# 如果 已经绑定了 https 则直接运行下面这一行 会把原来的连接进行覆盖
# ssh_url 换成你自己仓库 的 shh 地址
git remote add origin ssh_url
```
