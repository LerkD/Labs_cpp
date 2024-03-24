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

    // Запускаем и измеряем время для Quick Sort
    auto start_quick = std::chrono::steady_clock::now();
    quickSort(people_span, 0, people_span.size() - 1, comparisons, swaps);
    auto end_quick = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_quick = end_quick - start_quick;

    std::cout << "Array after Quick Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Quick Sort
    std::cout << "Quick Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Quick Sort Swaps: " << swaps << std::endl;
    std::cout << "Quick Sort Time: " << elapsed_seconds_quick.count() << "s\n";
    std::cout << std::endl;


    return 0;
}

