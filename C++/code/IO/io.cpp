#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

void iostateTest(){
    // 这几个bit都是static const，因此直接用作用域访问，或者用类的对象（比如cin）来访问都可以
    cout<<istream::goodbit<<endl; // 000
    cout<<istream::badbit<<endl; // 001
    cout<<istream::eofbit<<endl; // 010
    cout<<istream::failbit<<endl; // 100
}

istream& E1(istream &is){
    string s;
    while(is>>s){
        cout<<s;
    }
    is.clear();
    return is;
}

void E4(){
    ifstream ifs(".\\file.in");
    string s;
    vector<string> v;
    while(getline(ifs,s,' ')){
        v.push_back(s);
    }
    for(const auto &i:v){
        cout<<i<<endl;
    }
}

void E10(){
    ifstream ifs(".\\file.in");
    string s;
    vector<string> v;
    while(getline(ifs,s)){
        v.push_back(s);
    }
    for(const auto &i:v){
        istringstream iss(i);
        while(iss>>s){
            cout<<s<<endl;
            
        }
    }
}

int main(){
    // E1(cin);
    E10();
}