#include "listNode/list_c++.h"
#include<cstdlib>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    srand(shitong::seed);
    shitong::List<int> listTest;
    int i = 20;
    while (i--)
    {
        listTest.insertAsLast(rand() % 20);
    }
    cout << "list:";
    listTest.output();
    std::cout << std::endl;
    cout << "reverse:";
    listTest.reverse();
    listTest.output();
    std::cout << std::endl;
    std::cout << "max:" << listTest.selectMax()->data << ' ' << "size:" << listTest.size() << std::endl;
    i = 5;
    while (i--)
    {
        listTest.remove(listTest.first());
    }
    cout << "cut:";
    listTest.output();
    std::cout << std::endl
              << listTest.size() << endl;
    listTest.sort();
    cout << "sorted:";
    listTest.output();
}