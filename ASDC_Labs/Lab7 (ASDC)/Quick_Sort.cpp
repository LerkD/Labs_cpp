#include "header1.h"

// Quick Sort
int partition(std::span<Person> arr, int low, int high, int& comparisons, int& swaps)
{
    Person pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j)
    {
        ++comparisons;
        if (arr[j].form < pivot.form)
        {
            ++i;
            std::swap(arr[i], arr[j]);
            ++swaps;
        }
    }
    std::swap(arr[i + 1], arr[high]);
    ++swaps;
    return i + 1;
}

void quickSort(std::span<Person> arr, int low, int high, int& comparisons, int& swaps)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, comparisons, swaps);
        quickSort(arr, low, pi - 1, comparisons, swaps);
        quickSort(arr, pi + 1, high, comparisons, swaps);
    }
}

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
   runExample();

    return 0;
}
