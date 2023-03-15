// sum_main.cpp
// 编译命令： g++ sum_main.cpp sum.cpp const_var.cpp -o main
#include "sum.h" // 预处理后，源文件中已包含头文件中的声明，因此后续使用头文件中声明的变量时，无需重新声明
#include "const_var.h"
#include <iostream>

int main()
{
    std::cout << "sum=" << sum(1, 3) << std::endl;
    std::cout << "const_var=" << const_var << std::endl;
    std::cout << "var=" << var << std::endl;
    show();
    return 0;
}