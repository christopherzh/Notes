// 将一个类或类成员函数定义为另一个类的友元
#include <iostream>
#include <string>
using namespace std;
namespace betweenClass // 类之间的友元关系
{

    class Screen // 先声明Screen
    {
        friend class Window; // 再声明友元，隐式的假定该名字在当前作用域可见

    private:
        int x = 1920;
        int y = 1080;
    };

    class Window // 最后声明Window
    {
    public:
        void square(Screen &s)
        {
            cout << "betweenClass:" << s.x * s.y << endl;
        }
    };
}

namespace classFunction // 类的成员函数作为友元
{
    class Screen; // 最初的最初，也是最重要的，声明Screen，以便Window中的Screen能被找到
    class Window // 首先，定义Window类，声明square函数，但不定义它
    {
    public:
        void square(Screen &s);
        
    };

    class Screen // 随后，定义Screen，进行友元声明
    {
        friend void Window::square(Screen &s);

    private:
        int x = 1920;
        int y = 1080;
    };
    void Window::square(Screen &s) // 最后，定义square函数
    {
        cout << "classFunction:" << s.x * s.y << endl;
    }

}

int main()
{
    betweenClass::Screen s;
    betweenClass::Window w;
    w.square(s);

    classFunction::Screen ss;
    classFunction::Window ww;
    ww.square(ss);
    return 0;
}