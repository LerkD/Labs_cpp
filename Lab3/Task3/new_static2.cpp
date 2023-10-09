#include <iostream>
// Первоначальный вариант
int a = 0; // переменная a доступна из любой функции в этом файле и имеет глобальную видимость.

void staticMemory()
{
    std::cout << "a: " << a << std::endl;
    a += 1;
}

int main()
{
    staticMemory(); // выводит 0
    staticMemory(); // выводит 1
    staticMemory(); // выводит 2
    return 0;
}
