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

    // Запускаем и измеряем время для Merge Sort
    auto start_merge = std::chrono::steady_clock::now();
    mergeSort(people_span, 0, people_span.size() - 1, comparisons, swaps);
    auto end_merge = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_merge = end_merge - start_merge;

    std::cout << "Array after Merge Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Merge Sort
    std::cout << "Merge Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Merge Sort Swaps: " << swaps << std::endl;
    std::cout << "Merge Sort Time: " << elapsed_seconds_merge.count() << "s\n";
    std::cout << std::endl;

    return 0;
}

