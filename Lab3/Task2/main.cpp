#include <iostream>

// Определение функции hello в main.cpp (с модификатором static)
static int hello(int a)
{
    return (a + a);
};

int main() {
    int result = hello(5); // Вызываем функцию hello и сохраняем результат
    std::cout << "hello result: " << result << std::endl;
    return 0;
}

