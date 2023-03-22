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
int main()
{
    allocatorExample(5);
    return 0;
}