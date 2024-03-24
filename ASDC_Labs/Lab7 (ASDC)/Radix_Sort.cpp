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

    // Запускаем и измеряем время для Radix Sort
    auto start_radix = std::chrono::steady_clock::now();
    radixSort(people_span, comparisons, swaps);
    auto end_radix = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_radix = end_radix - start_radix;

    std::cout << "Array after Radix Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Radix Sort
    std::cout << "Radix Sort Comparisons: " << comparisons /*Будет 0*/ << std::endl; // По сути не нужно, так как алгоритм Radix Sort не зависит от сравнений элементов.
    std::cout << "Radix Sort Swaps: " << swaps << std::endl;
    std::cout << "Radix Sort Time: " << elapsed_seconds_radix.count() << "s\n";
    std::cout << std::endl;

    return 0;
}
