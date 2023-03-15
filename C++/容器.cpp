#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// unordered_multimap示例 http://c.biancheng.net/view/7248.html
void unorderedMultimapExample()
{
    // 创建空容器
    std::unordered_multimap<std::string, std::string> uoMp;
    // 向空容器中连续添加 5 个键值对
    uoMp.emplace("Python教程", "http://c.biancheng.net/python/");
    uoMp.emplace("STL教程", "http://c.biancheng.net/stl/");
    uoMp.emplace("Java教程", "http://c.biancheng.net/java/");
    uoMp.emplace("C教程", "http://c.biancheng.net");
    uoMp.emplace("C教程", "http://c.biancheng.net/c/"); // unordered_multimap允许重复的键值对

    auto itr = uoMp.equal_range("C教程"); // 使用equal_range查找key对应的一系列值，返回的是一个迭代器
    for (auto it = itr.first; it != itr.second; it++)
    {
        std::cout << it->first << ":" << it->second << std::endl;
    }
}

int main()
{
    unorderedMultimapExample();
    return 0;
}