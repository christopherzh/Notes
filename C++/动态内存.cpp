#include <iostream>
#include <vector>
#include <string>
#include <cstring>
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

void shared_ptrExample()
{
    shared_ptr<string> p1(make_shared<string>("asd"));
    cout << p1.use_count() << endl;
    shared_ptr<string> p2(p1);
    cout << p2.use_count() << endl;
    shared_ptr<string> p3;
    cout << p3.use_count() << endl;

    shared_ptr<int> sp(new int[10](), [](int *p)
                       { delete[] p; });
    cout << *(sp.get() + 1);
}

void weak_ptrExample()
{
    shared_ptr<string> sp1(make_shared<string>("asd"));
    cout << sp1.use_count() << endl;
    weak_ptr<string> wp1 = sp1;
    cout << sp1.use_count() << endl; // 弱指针不增加引用数
    shared_ptr<string> sp2 = wp1.lock();
    cout << sp1.use_count() << endl;
}

void unique_ptrExample()
{
    unique_ptr<string> up1(new string("aaa"));
    unique_ptr<string> up2(up1.release()); // 将up1转移给up2
    cout << *up2 << endl;
    unique_ptr<string> up3(new string("bbb"));
    up2.reset(up3.release());
    cout << *up2 << endl;
}
int main()
{
    // allocatorExample(5);
    // shared_ptrExample();
    // weak_ptrExample();
    unique_ptrExample();
    return 0;
}