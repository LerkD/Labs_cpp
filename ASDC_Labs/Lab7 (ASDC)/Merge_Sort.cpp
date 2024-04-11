#include "header1.h"

// Merge Sort
void merge(std::span<Person> arr, int l, int m, int r, int& comparisons, int& swaps)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<Person> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        ++comparisons;
        if (L[i].form <= R[j].form)
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++swaps;
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::span<Person> arr, int l, int r, int& comparisons, int& swaps)
{
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, comparisons, swaps);
    mergeSort(arr, m + 1, r, comparisons, swaps);
    merge(arr, l, m, r, comparisons, swaps);
}


void runSortAlgorithm(std::span<Person> people_span)
{
    std::cout << "Initial array:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    int comparisons = 0, swaps = 0;

    // Запускаем и измеряем время для Merge Sort
    auto start_merge = std::chrono::steady_clock::now();
    mergeSort(people_span, 0, people_span.size() - 1, comparisons, swaps);
    auto end_merge = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_merge = end_merge - start_merge;

    std::cout << "Array after Merge Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Merge Sort
    std::cout << "Merge Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Merge Sort Swaps: " << swaps << std::endl;
    std::cout << "Merge Sort Time: " << elapsed_seconds_merge.count() << "s\n";
    std::cout << std::endl;
}

int main()
{
    runExample();

    return 0;
}
