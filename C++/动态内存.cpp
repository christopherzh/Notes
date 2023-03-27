#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

void allocatorExample(int n)
{
    allocator<string> alloc;
    string *const p = alloc.allocate(n); // 分配内存
    string s;
    auto q = p;
    while (q != p + n && cin >> s)
    {
        alloc.construct(q++, s); // 构造对象
    }
    const string::size_type size = q - p;
    cout << "----------------------------" << endl;
    while (q != p)
    {
        cout << *--q << endl; // 倒着输出
        alloc.destroy(q);     // 销毁对象
    }
    alloc.deallocate(p, n); // 释放内存
}

void shared_ptrExample(){
    shared_ptr<string> p1(make_shared<string>("asd"));
    cout<<p1.use_count()<<endl;
    shared_ptr<string> p2(p1);
    cout<<p2.use_count()<<endl;
    shared_ptr<string> p3;
    cout<<p3.use_count()<<endl;
}

int main()
{
    // allocatorExample(5);
    shared_ptrExample();
    return 0;
}