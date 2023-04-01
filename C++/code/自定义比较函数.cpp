#include <iostream>     // std::cout
#include <algorithm>    // std::equal_range
#include <vector>       // std::vector
using namespace std;
//以普通函数的方式定义查找规则
bool mycomp(int i, int j) { return i > j; }
//以函数对象的形式定义查找规则
class mycomp2 {
public:
    bool operator()(const int& i, const int& j) {
        return i > j;
    }
};
int main() {
    int a[9] = { 1,2,3,4,4,4,5,6,7};
    //从 a 数组中找到所有的元素 4
    pair<int*, int*> range = equal_range(a, a + 9, 4);
    cout << "a[9]：";
    for (int *p = range.first; p < range.second; ++p) {
        cout << *p << " ";
    }
    vector<int>myvector{ 7,8,5,4,3,3,3,3,2,1 };
    pair<vector<int>::iterator, vector<int>::iterator> range2;
    //在 myvector 容器中找到所有的元素 3
    range2 = equal_range(myvector.begin(), myvector.end(), 3,mycomp2());//使用函数对象
    // range2 = equal_range(myvector.begin(), myvector.end(), 3,mycomp);//使用普通函数
    cout << "\nmyvector：";
    for (auto it = range2.first; it != range2.second; ++it) {
        cout << *it << " ";
    }
    return 0;
}