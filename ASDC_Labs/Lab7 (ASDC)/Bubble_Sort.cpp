#include "header1.h"

// Bubble Sort
void bubbleSort(std::span<Person> arr, int& comparisons, int& swaps)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            ++comparisons;
            if (arr[j].form > arr[j + 1].form)
            {
                std::swap(arr[j], arr[j + 1]);
                ++swaps;
            }
        }
    }
}


void runSortAlgorithm(std::span<Person> people_span)
{
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
}

int main()
{
    runExample();

    return 0;
}
