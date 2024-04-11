#include "header1.h"

// Insertion Sort
void insertionSort(std::span<Person> arr, int& comparisons, int& swaps)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        Person key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].form > key.form)
        {
            ++comparisons;
            arr[j + 1] = arr[j];
            ++swaps;
            --j;
        }
        arr[j + 1] = key;
    }
}

void runSortAlgorithm(std::span<Person> people_span)
{
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
}

int main()
{
    runExample();

    return 0;
}
