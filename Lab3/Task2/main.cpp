#include <iostream>

// Объявление функции hello в main.cpp
int hello(int a);

int main() {
    int result = hello(5); // Вызываем функцию hello и сохраняем результат
    std::cout << "Результат функции hello: " << result << std::endl;
    return 0;
}

