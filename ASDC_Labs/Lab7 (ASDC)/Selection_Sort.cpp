#include "header1.h"

// Selection Sort
void selectionSort(std::span<Person> arr, int& comparisons, int& swaps)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            ++comparisons;
            if (arr[j].form < arr[min_idx].form)
            {
                min_idx = j;
            }
        }
        std::swap(arr[min_idx], arr[i]);
        ++swaps;
    }
}

void runSortAlgorithm(std::span<Person> people_span)
{
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
}

int main()
{
    runExample();

    return 0;
}
