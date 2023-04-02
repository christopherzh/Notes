#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void iostateTest()
{
    // 这几个bit都是static const，因此直接用作用域访问，或者用类的对象（比如cin）来访问都可以
    cout << istream::goodbit << endl; // 000
    cout << istream::badbit << endl;  // 001
    cout << istream::eofbit << endl;  // 010
    cout << istream::failbit << endl; // 100
}

void ioTest()
{

    ifstream ifs(".\\file.in");
    ofstream ofs(".\\file.out");
    ofstream::pos_type pt;
    string s;
    vector<string> v;
    char ch;
    char ca[20];
    int i;
    int j;
}

istream &E1(istream &is)
{
    string s;
    while (is >> s)
    {
        cout << s;
    }
    is.clear();
    return is;
}

void E8_4()
{
    ifstream ifs(".\\file.in");
    string s;
    vector<string> v;
    while (getline(ifs, s, ' '))
    {
        v.push_back(s);
    }
    for (const auto &i : v)
    {
        cout << i << endl;
    }
}

void E8_10()
{
    ifstream ifs(".\\file.in");
    string s;
    vector<string> v;
    while (getline(ifs, s))
    {
        v.push_back(s);
    }
    for (const auto &i : v)
    {
        istringstream iss(i);
        while (iss >> s)
        {
            cout << s << endl;
        }
    }
}

int main()
{
    ioTest();
}