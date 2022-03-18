# C++
## const
1. const用于修饰它左侧的内容（类型 int、指针 *），当const处于最左端时，它修饰右边的内容
2. const 修饰类成员函数，其目的是防止成员函数修改被调用对象的值，如果我们不想修改一个调用对象的值，所有的成员函数都应当声明为 const 成员函数。
**注意**：const 关键字不能与 static 关键字同时使用，因为 static 关键字修饰静态成员函数，静态成员函数不含有 this 指针，即不能实例化，const 成员函数必须具体到某一实例。
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
   
# Docker
## 安装vim
cat >/etc/apt/sources.list <<EOF
deb http://deb.debian.org/debian buster main
deb http://security.debian.org/debian-security buster/updates main
deb http://deb.debian.org/debian buster-updates main
EOF

执行成功后，再运行下面的命令即可

apt-get update
apt-get install -y vim



