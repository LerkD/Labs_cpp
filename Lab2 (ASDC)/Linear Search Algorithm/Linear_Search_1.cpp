// Алгорит линейного поиска - самый простой вариант 

#include <iostream>
#include <chrono>

int main()
{
    int size;
    std::cout << "Enter size of your array: ";
    std::cin >> size;
    std::cout << std::endl;
    int *a = new int[size];
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        a[i] = rand() % 100;
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    int search;
    int num_found = 0;
    std::cout << std::endl;
    std::cout << "Enter number you want to find: ";
    std::cin >> search;
    std::cout << std::endl;

    // Измерение времени линейного поиска
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++)
    {
        if (a[i] == search)
        {
            std::cout << "Number " << search << " was found in index " << i << std::endl;
            num_found += 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Linear Search Time: " << duration.count() << " seconds" << std::endl;

    if (num_found == 0)
    {
        std::cout << "Number " << search << " wasn't found" << std::endl;
    }

    std::cout << std::endl;

    delete[] a; // Еще освобождаю выделенную память 

    return 0;
}
