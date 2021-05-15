#include "vector/vector_c++.h"
#include <iostream>
int main()
{
    shitong::Vector<int> vecter1(10, 5, 1);
    std::cout << vecter1[2] << std::endl;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    shitong::Vector<int> B(a, sizeof(a) / sizeof(int) - 1);
    std::cout << "size:" << B.size() << std::endl;
    std::cout << "init:";
    B.output();
    std::cout << std::endl
              << "unsort:";
    B.unsort();
    B.output();
    std::cout << std::endl
              << "sort:";
    B.sort();
    B.output();
    B.remove(3);
    std::cout << std::endl
              << "remove(3):";
    B.output();
}