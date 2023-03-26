#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <cstring>
#include <stack>
using std::cout, std::endl, std::string, std::vector, std::array, std::list, std::forward_list;

void vectorExample()
{
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int>::difference_type dt;
    vector<int>::size_type st;
    vector<int>::reference r = v.at(0);
    cout << v.max_size() << endl;
}
void arrayExample()
{
    array<int, 5> a1 = {1, 2, 3, 4, 5};
    // for(auto i=a1.begin();i!=a1.end();i++){
    //     cout<<*i<<endl;
    // }
}

void flExample()
{ // 删除f中所有奇数
    forward_list<int> f{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto prev = f.before_begin();
    auto curr = f.begin();
    while (curr != f.end())
    {
        if (*curr % 2)
        {
            curr = f.erase_after(prev);
        }
        else
        {
            prev++;
            curr++;
        }
    }
    for (auto i = f.begin(); i != f.end(); i++)
    {
        cout << *i << endl;
    }
}

void stringConvert(){ // char与string的各种转换
    // https://blog.csdn.net/amin_hui/article/details/115359358
    string s="string";
    char* pc="char";
    const char* pc1;

    // char* 转 string
    string s1(pc); // char*赋值给s
    s1.assign(pc,strlen(pc)); // char*赋值给s,指针指向内容及地址不改变

    // string 转 char*
    pc1=s.data(); // data()仅返回字符串内容，而不含有结束符’\0’
    pc1=s.c_str(); // c_str()函数返回一个以’\0’结尾的字符数组

    pc1=new char[s.size()+1]; //char长度应该大于等于string
    s.copy(const_cast<char*>(pc1),s.size(),0); // 要想指针指向内容及地址不改变，使用该方式
}

void stringChange1(string &s,string &oldVal,string &newVal){
    s.erase(oldVal.begin(),oldVal.begin());
    oldVal.insert(0,newVal);

    // oldVal.replace(0,oldVal.size(),newVal);
}
// 练习9.45
string& stringChange3(string &s,const string &front,const string &back){
    s.insert(s.begin(),front.begin(),front.end());
    s.append(back);
    return s;
} 

// 练习9.46
string& stringChange4(string &s,const string &front,const string &back){
    s.insert(0,front);
    s.insert(s.size(),back);
    return s;
} 

int main()
{
    vectorExample();
    arrayExample();
    flExample();
    stringConvert();
    return 0;
}