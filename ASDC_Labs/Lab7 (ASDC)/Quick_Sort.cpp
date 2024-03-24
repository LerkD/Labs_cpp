#include "header.h"

void runSortAlgorithm(std::span<Person> people_span)
{
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
}

int main()
{
    std::array<Person, 5> people = {
        {{"Lera", 12, Gender::Girl},
         {"Anton", 9, Gender::Boy},
         {"Dima", 7, Gender::Boy},
         {"Catea", 8, Gender::Girl},
         {"Asea", 3, Gender::Girl}}};

    runSortAlgorithm(people);

    std::cout << "------------\n" << std::endl;

    // Другая конфигурация 
    std::array<Person, 5> people2 = {
        {{"Anton", 9, Gender::Boy},
         {"Lera", 12, Gender::Girl},
         {"Catea", 8, Gender::Girl},
         {"Asea", 3, Gender::Girl},
         {"Dima", 7, Gender::Boy}}};

    runSortAlgorithm(people2);

    std::cout << "------------\n" << std::endl;

    // Другая конфигурация 
    std::array<Person, 5> people3 = {
        {{"Asea", 3, Gender::Girl},
         {"Anton", 9, Gender::Boy},
         {"Dima", 7, Gender::Boy},
         {"Catea", 8, Gender::Girl},
         {"Lera", 12, Gender::Girl}}};

    runSortAlgorithm(people3);

    std::cout << "------------\n" << std::endl;
    std::cout << "Different size: \n" << std::endl;

    std::array<Person, 12> people_long = {
        {{"Lera", 12, Gender::Girl},
         {"Anton", 9, Gender::Boy},
         {"Dima", 7, Gender::Boy},
         {"Catea", 8, Gender::Girl},
         {"Asea", 3, Gender::Girl},
         {"Masha", 1, Gender::Girl},
         {"Vasea", 5, Gender::Boy},
         {"Danil", 2, Gender::Boy},
         {"Anea", 4, Gender::Girl},
         {"Sonya", 11, Gender::Girl},
         {"Misha", 10, Gender::Boy},
         {"Olea", 11, Gender::Girl}}};

    runSortAlgorithm(people_long);

    return 0;
}
