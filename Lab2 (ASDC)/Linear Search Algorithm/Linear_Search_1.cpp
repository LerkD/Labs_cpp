// Алгорит линейного поиска - самый простой вариант 

#include <iostream>

main()
{
    int size;
    std::cout <<"Enter size of your array: ";
    std::cin >> size;
    std::cout << std::endl;
    int *a = new int [size];
    srand(time(NULL)); // Использую эту функцию, чтобы при генерации рандомных чисел, они не повторялись 

    for (int i = 0; i < size; i++)
    {
        a[i] = rand()%100;
        std::cout << a[i] << " ";
    }
     std::cout << std::endl;

    int search;
    int num_found = 0;
    std::cout << std::endl;
    std::cout << "Enter numer you want to find: ";
    std::cin >> search;
    std::cout << std::endl;
    
    for (int i = 0; i < size; i++)
    {
        if (a[i] == search)
        {
            std::cout << "Number " << search << " was found in index " << i << std::endl;
            num_found += 1;
        }
    }

    if (num_found == 0)
    {
        std::cout << "Number " << search << " wasn't found" << std::endl;
    }

    std::cout << std::endl;
}