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

   // Запускаем и измеряем время для Shell Sort
    auto start_shell = std::chrono::steady_clock::now();
    shellSort(people_span, comparisons, swaps);
    auto end_shell = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_shell = end_shell - start_shell;

    std::cout << "Array after Shell Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Shell Sort
    std::cout << "Shell Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Shell Sort Swaps: " << swaps << std::endl;
    std::cout << "Shell Sort Time: " << elapsed_seconds_shell.count() << "s\n";
    std::cout << std::endl;

    return 0;
}
