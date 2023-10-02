#include <iostream>
#include <string>

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string userName;
    std::cout << "Введите ваше имя: ";
    std::cin >> userName;

    std::cout << "Привет, " << userName << "! Рад видеть вас во вселенной, мяу!" << std::endl;

    return 0;
}
