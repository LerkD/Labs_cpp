#include "header1.h"

// Shell Sort, здесь я делю расстояние на 2 (Если на 1, то это все равно, что Insertion Sort)
void shellSort(std::span<Person> arr, int& comparisons, int& swaps)
{
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            Person temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].form > temp.form; j -= gap)
            {
                ++comparisons;
                arr[j] = arr[j - gap];
                ++swaps;
            }
            arr[j] = temp;
        }
    }
}

void runSortAlgorithm(std::span<Person> people_span)
{
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
}

int main()
{
    runExample();
    
    return 0;
}
