#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HasPtr // 一个指针通过拷贝和赋值被复制n次，使用use维护n的数量，以进行恰合时宜的析构和拷贝赋值
{
public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0), use(new string::size_type(1)){};
    ~HasPtr();
    HasPtr(const HasPtr &hp):ps(hp.ps),i(hp.i),use(hp.use){++*use;}; // 直接复制指针本身，使用use来记录指针复制了多少次
    HasPtr &operator=(const HasPtr &rhp);
    void show(){cout<<*use<<endl;};
private:
    string *ps; // 指向一个字符串
    int i;
    string::size_type *use; //ps被引用的次数
};
HasPtr::~HasPtr()
{
    if (--*use == 0)
    {
        delete use;
        delete ps;
    }
}
// 具有隐藏的this指针，即赋值号左侧的对象
HasPtr &HasPtr::operator=(const HasPtr &rhp)
{ 
    ++*rhp.use; //运算符右侧的use增加了
    if(--*use==0){ //运算符左侧原本的use因为赋了新值而减少，当减少到0时，应当释放内存，这里析构函数不起作用
        delete ps;
        delete use;
    }
    ps=rhp.ps;
    i=rhp.i;
    use=rhp.use;
}
int main(){
    HasPtr h("hi mom!");
	HasPtr h2 = h;
    HasPtr h3(h);
    h.show();
    h2.show();
    h3.show();
}