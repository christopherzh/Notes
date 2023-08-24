// const_var.cpp
#include <iostream>
#include "const_var.h"
extern const int const_var; // 不引入包含变量声明的头文件的使用示例。注：需与定义该变量的源文件进行连接。
void show()
{
    std::cout << "show const_var=" << const_var << std::endl;
}