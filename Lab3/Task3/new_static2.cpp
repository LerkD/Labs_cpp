#include <iostream>

// Вариант, эквивалентный static1.cpp 

void staticMemory()
{
    static int a = 0; // Локальная статическая переменная, переменная а иметь локальную видимость только внутри этой функции
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
