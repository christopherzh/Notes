# C++基础

## const
### 基础知识
1. const对象必须初始化。初始化时，赋予的值是不是const都可以，因为常量特征仅在执行时改变其值才会发挥作用。const对象仅在文件内有效。（C++ primer 5th P54）
2. 顶层const：对象本身是个常量，例如常量指针。  底层const：指针所指向的对象是一个常量。此外，声明引用的const(const int &r)都是底层const。（C++ primer 5th P57-58）
### 与引用
1. 不能让一个非常量引用指向一个常量对象。但允许一个常量引用(const int &r)绑定非常量的对象、字面值或一般表达式。对常量的引用可能引用一个并非const的对象。
### 与指针
1. 指向常量的指针(pointer to const)(const int *ptrToConst)不能用于改变其所指对象的值。同样的，不能让一个非常量指针指向常量。
2. 常量指针(const pointer)(int *const cptr)必须初始化，初始化后，地址本身不能改变。
### constexpr
1. 常量表达式：编译时就可确定结果的表达式。
2. 字面值类型：算数类型、引用、指针等。
3. 将变量声明为constexpr类型以便编译器验证变量值是否为一个常量表达式。
4. constexpr指针初始值必须是nullptr或0，或存于某个固定地址的对象。
```cpp
constexpr int mf = 20;
constexpr int *p = nullptr;  //p是一个指向整数的常量指针，是顶层指针
const int *q = nullptr; //qq是一个指向整数常量的指针，是底层指针
```
### 类型别名
![](image/2023-03-15-16-20-41.png)
### auto类型说明符
auto会忽略掉顶层const，而decltype不会忽略。
![](image/2023-03-15-17-29-01.png)
![](image/2023-03-15-17-29-39.png)
### decltype
![](image/2023-03-15-17-30-21.png)
![](image/2023-03-15-18-31-57.png)
### 优先级
1. const用于修饰它左侧的内容（类型 int、指针 *），当const处于最左端时，它修饰右边的内容
### 与类和函数
1. const 修饰类成员函数，其目的是防止成员函数修改被调用对象的值，如果我们不想修改一个调用对象的值，所有的成员函数都应当声明为 const 成员函数。
**注意**：const 关键字不能与 static 关键字同时使用，因为 static 关键字修饰静态成员函数，静态成员函数不含有 this 指针，即不能实例化，const 成员函数必须具体到某一实例。
1. const修饰函数的三种用法：修饰返回值（当函数的返回值为引用时，避免被调用者修改），修饰函数参数（防止传递的参数在函数内部被修改），修饰类的成员函数（也称为**常量成员函数**， const修饰成员函数，根本上是修饰了this 指针）
   
## 指针
1. - 指针数组：int *ptrs[10] 包含十个指向int的指针的数组
   - 数组指针：int (*Parray)[10] 指向包含10个int元素的数组的指针
   - 判断复杂数组声明的方法：从数组名字开始，从内向外读。上例中，从Parray开始，*表示它是一个指针，然后[10]说明它指向大小为10的数组的指针，最后是int，说明了数组中元素是int。

## 引用
### 左值引用与右值引用
#### 左值引用与const
引用是变量的别名，由于右值没有地址，无法被修改，所以左值引用无法指向右值。但const左值引用可以指向右值。
```cpp
int &ref_a = 5 //编译失败
const int &ref_a = 5; //成功
```
这是因为const左值引用不会修改指向值，因此可以指向右值，这也是为什么要使用```const value_type&```作为函数参数的原因之一，例如```std::vector```的```push_back```：
```cpp
void push_back(const value_type& val);
```
如果没有```const```，```vec.push_back(5)```这样的代码就无法编译通过了。

#### 右值引用
https://zhuanlan.zhihu.com/p/335994370
右值引用可以指向右值，不能指向左值，右值引用的标志为```&```

#### 利用 ```std::move``` 使右值引用指向左值
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

#### 左值引用、右值引用本身是左值还是右值？
被声明出来的左、右值引用都是左值。 因为被声明出的左右值引用是有地址的，也位于等号左边。

右值引用既可以是左值也可以是右值，如果有名称则为左值，否则是右值。

或者说：作为函数返回值的 `&&` 是右值，直接声明出来的 `&&` 是左值。 这同样也符合对左值，右值的判定方式：其实引用和普通变量是一样的，`int &&ref = std::move(a)`和 `int a = 5`没有什么区别，等号左边就是左值，右边就是右值。

最后，从上述分析中我们得到如下结论：

- 从性能上讲，左右值引用没有区别，传参使用左右值引用都可以避免拷贝。
- 右值引用可以直接指向右值，也可以通过std::move指向左值；而左值引用只能指向左值(const左值引用也能指向右值)。
- 作为函数形参时，右值引用更灵活。虽然const左值引用也可以做到左右值都接受，但它无法修改，有一定局限性。

#### 右值引用和std::move的应用场景
1. 实现移动语义，避免深拷贝

#### 完美转发 `std::forward`
和`std::move`一样，它的兄弟`std::forward`也充满了迷惑性，虽然名字含义是转发，但他并不会做转发，同样也是做类型转换.

与move相比，forward更强大，move只能转出来右值，forward都可以。

> `std::forward<T>(u)`有两个参数：`T`与 `u`。
a. 当T为左值引用类型时，u将被转换为T类型的左值； 
b. 否则u将被转换为T类型右值。

# C++面向对象
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



# 工程实践
## 结构体踩坑！！！
[C语言内存对齐详解](https://www.cnblogs.com/wuyudong/p/memory-alignment.html)
为了提高CPU的存储速度，编译器对一些变量的起始地址做了“对齐”处理。在默认情况下，编译器规定各成员变量存放的起始地址相对于结构的起始地址的偏移量必须为该变量的类型所占用的字节数的倍数。
- char              偏移量必须为sizeof(char)即1的倍数
- int                偏移量必须为sizeof(int)即4的倍数
- float             偏移量必须为sizeof(float)即4的倍数
- double          偏移量必须为sizeof(double)即8的倍数
- short            偏移量必须为sizeof(short)即2的倍数
各成员变量在存放的时候根据在结构中出现的顺序依次申请空间，同时按照上面的对齐方式调整位置，空缺的字节编译器会自动填充。同时编译器为了确保结构的大小为结构的字节边界数（即该结构中占用最大空间的类型所占用的字节数）的倍数，所以在为最后一个成员变量申请空间后，还会根据需要自动填充空缺的字节。