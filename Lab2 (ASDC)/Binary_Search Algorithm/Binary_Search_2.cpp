// Двоичный поиск - пример использования 

/*Мне понравилась необычная задача - нахождение квадратного корня с помощью бинарного поиска.
Необычной она мне кажется, тк, бинарный поиск, будто чаще всего используется с векторами.
Я реализовала ее по аналогии с первой задачей с вектором, но тут, мне кажется, получилось интереснее.*/

#include <iostream>

double binarySearchSqrt(double x, double epsilon = 1e-6)
{
    if (x < 0)
    {
        std::cerr << "Error: Cannot compute square root of a negative number." << std::endl;
        return -1; // Возвращаем -1 для обозначения ошибки
    }

    double low = 0.0;
    double high = x;
    double result = 0.0;
    int attempts = 0;

    while (high - low > epsilon)
    {
        result = (low + high) / 2.0;
        double square = result * result;

        if (square < x)
        {
            low = result;
        }
        else
        {
            high = result;
        }

        attempts++;
    }

    std::cout << "Number of attempts: " << attempts << std::endl;

    return result;
}

int main()
{
    double number;
    std::cout << "Enter a number to find its square root: ";
    std::cin >> number;

    double sqrtValue = binarySearchSqrt(number);

    if (sqrtValue != -1)
    {
        std::cout << "Square root of " << number << " is approximately: " << sqrtValue << std::endl;
    }

    return 0;
}
