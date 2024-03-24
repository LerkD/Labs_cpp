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

   // Запускаем и измеряем время для Selection Sort
    auto start_selection = std::chrono::steady_clock::now();
    selectionSort(people_span, comparisons, swaps);
    auto end_selection = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_selection = end_selection - start_selection;

    std::cout << "Array after Selection Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей для Selection Sort
    std::cout << "Selection Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Selection Sort Swaps: " << swaps << std::endl;
    std::cout << "Selection Sort Time: " << elapsed_seconds_selection.count() << "s\n";
    std::cout << std::endl;

    return 0;
}

