// sum.cpp
#include "sum.h"
#include<iostream>

int var=10;
const int const_var=20; // 对头文件中的声明进行定义，extern修饰符可有可无，因为当extern与赋值同时存在时，即为定义，extern失去意义。下面的const_var同理。
int sum(int x, int y)
{   
    return x + y;
}