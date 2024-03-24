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

    std::cout << "Initial array:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    int comparisons = 0, swaps = 0;

    // Запускаем и измеряем время для Insertion Sort
    auto start_insertion = std::chrono::steady_clock::now();
    insertionSort(people_span, comparisons, swaps);
    auto end_insertion = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_insertion = end_insertion - start_insertion;

    std::cout << "Array after Insertion Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Insertion Sort
    std::cout << "Insertion Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Insertion Sort Swaps: " << swaps << std::endl;
    std::cout << "Insertion Sort Time: " << elapsed_seconds_insertion.count() << "s\n";
    std::cout << std::endl;

    return 0;
}

