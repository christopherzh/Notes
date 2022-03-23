# C++
## const
1. const用于修饰它左侧的内容（类型 int、指针 *），当const处于最左端时，它修饰右边的内容
2. const 修饰类成员函数，其目的是防止成员函数修改被调用对象的值，如果我们不想修改一个调用对象的值，所有的成员函数都应当声明为 const 成员函数。
**注意**：const 关键字不能与 static 关键字同时使用，因为 static 关键字修饰静态成员函数，静态成员函数不含有 this 指针，即不能实例化，const 成员函数必须具体到某一实例。
3. const修饰函数的三种用法：修饰返回值（当函数的返回值为引用时，避免被调用者修改），修饰函数参数（防止传递的参数在函数内部被修改），修饰类的成员函数（也称为**常量成员函数**， const修饰成员函数，根本上是修饰了this 指针）
## 多态与虚函数
[C++之多态性](https://blog.csdn.net/studyhardi/article/details/90815766?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-5.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-5.pc_relevant_default&utm_relevant_index=10)
[C++ 多态的实现及原理](https://www.cnblogs.com/cxq0017/p/6074247.html)
[C++虚函数和虚函数表原理](https://blog.csdn.net/u012630961/article/details/81226351)
[虚函数实现原理](https://blog.csdn.net/wanghaobo920/article/details/7674631?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_antiscanv2&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1.pc_relevant_antiscanv2&utm_relevant_index=1)
1. 多态是利用虚函数与虚函数表来实现的，通过指向对象的指针来调用类中的函数时，系统会根据指针指向的对象的类（而不是该指针定义时的类型）来决定调用哪个函数（父类的方法为虚函数）；该过程是通过对象中一个指向虚函数表的指针来实现调用的，也称为“晚绑定” （要让编译器采用晚绑定，就要在基类中声明函数时使用virtual关键字，这样的函数我们就称之为虚函数，一旦某个函数在基类中声明为virtual，那么在所有的派生类中该函数都是virtual，而不需要再显式地声明为virtual)
2. 压制多态可以使用域操作符来实现
```c++
class Base{
public:
    virtual void f1(){
        cout<<"base:f1()";
    }
};
class Derive:public Base{
public:
    void f1(){
        cout<<"derive:f1()";
    }
};
int main(){
   Derive* bp=new Derive();
   bp->Base::f1();//base:f1()
   bp->f1();//derive:f1()
   return 0;
}

```
3. 多继承情况下，派生类中有多个虚函数表，虚函数的排列方式和继承的顺序一致。派生类重写函数将会覆盖所有虚函数表的同名内容，**派生类自定义新的虚函数将会在第一个类（按照派生类的继承顺序，而不是成员初始化列表中的顺序）的虚函数表的后面进行扩充。** [C++继承中构造顺序](https://blog.csdn.net/tangjienihaoma/article/details/84526995)

## 指针
1. - 指针数组：int *ptrs[10] 包含十个指向int的指针的数组
   - 数组指针：int (*Parray)[10] 指向包含10个int元素的数组的指针

## 引用
### 左值引用与const
引用是变量的别名，由于右值没有地址，无法被修改，所以左值引用无法指向右值。但const左值引用可以指向右值。
```cpp
int &ref_a = 5 //编译失败
const int &ref_a = 5; //成功
```
这是因为const左值引用不会修改指向值，因此可以指向右值，这也睡为什么要使用```const value_type&```作为函数参数的原因之一，例如```std::vector```的```push_back```：
```cpp
void push_back(const value_type& val);
```
如果没有```const```，```vec.push_back(5)```这样的代码就无法编译通过了。

### 右值引用
https://zhuanlan.zhihu.com/p/335994370
右值引用可以指向右值，不能指向左值，右值引用的标志为```&```

### 利用 ```std::move``` 使右值引用指向左值
```cpp
int a = 5; // a是个左值
int &ref_a_left = a; // 左值引用指向左值
int &&ref_a_right = std::move(a); // 通过std::move将左值转化为右值，可以被右值引用指向
 
cout << a; // 打印结果：5
```
```std::move```是一个非常有迷惑性的函数，不理解左右值概念的人们往往以为它能把一个变量里的内容移动到另一个变量，但事实上```std::move```移动不了什么，唯一的功能是把左值强制转化为右值，让右值引用可以指向左值。其实现等同于一个类型转换：`static_cast<T&&>(lvalue)`。 所以，单纯的```std::move(xxx)```不会有性能提升。

同样的，右值引用能指向右值，本质上也是把右值提升为一个左值，并定义一个右值引用通过`std::move`指向该左值：
```cpp
int &&ref_a = 5;
ref_a = 6; 
 
等同于以下代码：
 
int temp = 5;
int &&ref_a = std::move(temp);
ref_a = 6;
```

### 左值引用、右值引用本身是左值还是右值？
被声明出来的左、右值引用都是左值。 因为被声明出的左右值引用是有地址的，也位于等号左边。

右值引用既可以是左值也可以是右值，如果有名称则为左值，否则是右值。

或者说：作为函数返回值的 `&&` 是右值，直接声明出来的 `&&` 是左值。 这同样也符合对左值，右值的判定方式：其实引用和普通变量是一样的，`int &&ref = std::move(a)`和 `int a = 5`没有什么区别，等号左边就是左值，右边就是右值。

最后，从上述分析中我们得到如下结论：

- 从性能上讲，左右值引用没有区别，传参使用左右值引用都可以避免拷贝。
- 右值引用可以直接指向右值，也可以通过std::move指向左值；而左值引用只能指向左值(const左值引用也能指向右值)。
- 作为函数形参时，右值引用更灵活。虽然const左值引用也可以做到左右值都接受，但它无法修改，有一定局限性。

### 右值引用和std::move的应用场景
1. 实现移动语义，避免深拷贝

### 完美转发 `std::forward`
和`std::move`一样，它的兄弟`std::forward`也充满了迷惑性，虽然名字含义是转发，但他并不会做转发，同样也是做类型转换.

与move相比，forward更强大，move只能转出来右值，forward都可以。

> `std::forward<T>(u)`有两个参数：`T`与 `u`。
a. 当T为左值引用类型时，u将被转换为T类型的左值； 
b. 否则u将被转换为T类型右值。

# Linux
## 链接
[有关链接的博客讲解](http://c.biancheng.net/linux/ln.html)
- 硬链接： 与普通文件没什么不同，inode都指向同一个文件在硬盘中的区块
- 软链接： 保存了其代表的文件的绝对路径，是另外一种文件，在硬盘上有独立的区块，访问时替换自身路径。类似于windows的快捷方式。
### 为什么 ln 不允许硬链接到目录
Linux 系统中的硬链接有两个限制：
1. 不能跨越文件系统。
2. 不允许普通用户对目录作硬链接。

至于第一个限制，很好理解，而第二个就不那么好理解了。

我们对任何一个目录用 ls-l 命令都可以看到其链接数至少是 2，这也说明了系统中是存在基于目录的硬链接的，而且命令 ln -d（-d选项表示针对目录建立硬链接）也允许 root 用户尝试对目录作硬链接。这些都说明了系统限制对目录进行硬链接只是一个硬性规定，并不是逻辑上不允许或技术上不可行。那么操作系统为什么要进行这个限制呢？

这是因为，如果引入了对目录的硬连接就有可能在目录中引入循环链接，那么在目录遍历的时候系统就会陷入无限循环当中。也许有人会说，符号连接不也可以引入循环链接吗，那么为什么不限制目录的符号连接呢？

原因就在于，在 Linux 系统中，每个文件（目录也是文件）都对应着一个 inode 结构，其中 inode 数据结构中包含了文件类型（目录、普通文件、符号连接文件等）的信息，也就是说，操作系统在遍历目录时可以判断出其是否是符号连接。既然可以判断出它是否是符号连接，当然就可以采取一些措施来防范进入过大过深的循环层次，于是大部分系统会规定在连续遇到 8 个符号连接后就停止遍历。但是对于硬链接，由于操作系统中采用的数据结构和算法限制，目前是不能防范这种死循环的。

基于这样的考虑，系统不允许普通用户建立目录硬链接。
## 常用命令
1. 查看端口占用情况  lsof -i:端口号 
   


