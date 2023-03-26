#include <iostream>
#include <string>
#include <exception>
#include <unordered_map>
#include <algorithm>
#include <map>
using std::cout, std::endl, std::string;
// unordered_multimap示例 http://c.biancheng.net/view/7248.html
void unorderedMultimapExample()
{
    // 创建空容器
    std::unordered_multimap<string, string> uoMp;
    // 向空容器中连续添加 5 个键值对
    uoMp.emplace("Python教程", "http://c.biancheng.net/python/");
    uoMp.emplace("STL教程", "http://c.biancheng.net/stl/");
    uoMp.emplace("Java教程", "http://c.biancheng.net/java/");
    uoMp.emplace("C教程", "http://c.biancheng.net");
    uoMp.emplace("C教程", "http://c.biancheng.net/c/"); // unordered_multimap允许重复的键值对

    auto itr = uoMp.equal_range("C教程"); // 使用equal_range查找key对应的一系列值，返回的是一个迭代器
    for (auto it = itr.first; it != itr.second; it++)
    {
        cout << it->first << ":" << it->second << endl;
    }
}

void mapExample()
{
    std::map<string, int> m{{"a", 0}, {"b", 1}};
    m["c"] = 1;                            // 添加{"c",1}
    auto lb = m.lower_bound("a");          // 返回一个指向当前 map 容器中第一个大于或等于 key 的键值对的双向迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
    auto ub = m.upper_bound("a");          // 返回一个指向当前 map 容器中第一个大于 key 的键值对的迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。
    auto er = m.equal_range("a");          // 该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower_bound() 方法的返回值等价，pair.second 和 upper_bound() 方法的返回值等价。
    if (lb == er.first && ub == er.second) // 也就是说，该方法将返回一个范围，该范围中包含的键为 key 的键值对（map 容器键值对唯一，因此该范围最多包含一个键值对）。
    {
        cout << "lb == er.first && ub == er.second" << endl;
    }

    try
    {
        cout << m.at("d"); // 找到 map 容器中 key 键对应的值，如果找不到，该函数会引发 out_of_range 异常。
    }
    catch (std::out_of_range e)
    {
        cout << e.what();
    }
}
int main()
{
    unorderedMultimapExample();
    mapExample();
    return 0;
}

