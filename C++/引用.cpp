#include <iostream>
using namespace std;
// 指向指针的引用示例
void example1()
{
    // i和j有着不同的地址
    int i = 42;
    int j = 43;
    int *p = &j; // p是指向j的指针
    int *const &const_r = &i; 
    // 从右向左读const_r的定义，离变量名最近的符号是对变量类型最直接的影响。因此，const_r是一个引用；
    // 声明符的其余部分用以确定其引用的类型是什么，此例中符号*说明const_r引用的是一个指针；
    // 最后，声明的基本数据类型const_r引用的是一个int指针；
    cout<<i<<endl;
    // 同时，&左面的const修饰符修饰的是其左面的*符号，表示const_r引用的是一个常量int指针。
    *const_r = 55; //正确，const_r引用的是一个常量int指针，但指向的i变量的值可以修改。
    //const_r = p; //报错，const_r引用的是一个常量int指针，不可改变原本指向的地址。
    cout<<i<<endl;
}
int main()
{
    example1();
    return 0;
}