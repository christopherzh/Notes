#include <iostream>
using namespace std;

int a, val = 2;
static int b;
enum Color
{
    red,
    green
};
void fun(int val)
{
    static int c;
    enum Type
    {
        A,
        B
    };
    struct Local
    {
        //static constexpr int cc=1; // 错误，局部类中不允许静态成员
        Color color;
        int locVal;
        void locFun()
        {
            //locVal = val; // 错误，不能访问函数的普通局部变量
            locVal = ::val; // 访问函数外层变量
            cout << locVal;
            locVal = a;   // 访问函数外层变量
            locVal = b;   // 访问函数外部静态变量
            locVal = c;   // 访问函数内静态变量
            locVal = red; // 访问函数外枚举成员
            locVal = A;   // 访问函数内枚举成员
        }

        struct U; // 在局部类中声明嵌套类
    };
    struct Local::U
    { // 定义嵌套类，该类也是一个局部类
    };
    Local lc;
    lc.locFun();
}

int main()
{
    fun(1); // 局部类
    return 0;
}