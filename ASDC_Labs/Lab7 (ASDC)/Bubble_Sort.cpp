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

    // Запускаем и измеряем время для Bubble Sort
    auto start_bubble = std::chrono::steady_clock::now();
    bubbleSort(people_span, comparisons, swaps);
    auto end_bubble = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_bubble = end_bubble - start_bubble;

    std::cout << "Array after Bubble Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Bubble Sort
    std::cout << "Bubble Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Bubble Sort Swaps: " << swaps << std::endl;
    std::cout << "Bubble Sort Time: " << elapsed_seconds_bubble.count() << "s\n";
    std::cout << std::endl;

    return 0;
}

