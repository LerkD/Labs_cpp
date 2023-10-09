#include <iostream>
// Глобальная переменная в main.cpp
int globalVar = 10;

// Объявление функции hello в main.cpp
int hello(int a);

int main() {
    int result = hello(5); // Вызываем функцию hello и сохраняем результат
    std::cout << "Результат функции hello: " << result << std::endl;
    return 0;
}
