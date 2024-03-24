#include "header.h"

int main()
{
    std::array<Person, 5> people = {
        {{"Lera", 12, Gender::Girl},
         {"Anton", 9, Gender::Boy},
         {"Dima", 7, Gender::Boy},
         {"Catea", 8, Gender::Girl},
         {"Asea", 3, Gender::Girl}}};

    std::span<Person> people_span(people);

    std::cout << "\nInitial array:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    int comparisons = 0, swaps = 0;

    // Запускаем и измеряем временя для Heap Sort
    auto start_heap = std::chrono::steady_clock::now();
    heapSort(people_span, comparisons, swaps);
    auto end_heap = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_heap = end_heap - start_heap;

    std::cout << "Array after Heap Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Heap Sort
    std::cout << "Heap Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Heap Sort Swaps: " << swaps << std::endl;
    std::cout << "Heap Sort Time: " << elapsed_seconds_heap.count() << "s\n";
    std::cout << std::endl;

    return 0;
}