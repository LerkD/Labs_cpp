// Двоичный поиск 

/*Для демонстрации алгоритма двоичного поиска я составила задачу.
Программа запрашивает у пользоватиля размер массива, заполняет его рандомно и сортирует.
Необъодимо написать программу для выполнения бинарного поиска в этом векторе.
Программа должна запрашивать у пользователя число, которое необходимо найти.
Затем ей необходимо использовать бинарный поиск для поиска этого числа в массиве.
После завершения поиска программа должна вывести индекс найденного элемента и количество попыток, затраченных на поиск.
Если элемент не найден в массиве, программа должна сообщить об этом.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

int binarySearch(const std::vector<int>& arr, int target, int& attempts)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        attempts++;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;  // Элемент не найден
}

int main()
{
    srand(time(nullptr));

    int size;
    std::cout << "Enter the size of the vector: ";
    std::cin >> size;
    std::cout << std::endl;

    std::vector<int> arr(size);

    // Заполняем вектора случайными значениями
    std::generate(arr.begin(), arr.end(), []() { return rand() % 100; });
    
    // Сортировка вектора перед бинарным поиском
    std::sort(arr.begin(), arr.end());

    std::cout << "Vector elements: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    int target;
    std::cout << "Enter the number to find: ";
    std::cin >> target;
    std::cout << std::endl;

    int attempts = 0;
    int result = binarySearch(arr, target, attempts);

    if (result != -1)
    {
        std::cout << "Element " << target << " found at index " << result << " with " << attempts << " attempts." << std::endl;
    }
    else
    {
        std::cout << "Element " << target << " was not found in the vector." << std::endl;
    }

    std::cout << std::endl;
    return 0;
}
