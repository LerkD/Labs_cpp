#include "header1.h"

// Heap Sort
void heapify(std::span<Person> arr, int n, int i, int& comparisons, int& swaps)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].form > arr[largest].form)
        largest = left;

    if (right < n && arr[right].form > arr[largest].form)
        largest = right;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        ++swaps;
        heapify(arr, n, largest, comparisons, swaps);
    }

    ++comparisons;
}

void heapSort(std::span<Person> arr, int& comparisons, int& swaps)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comparisons, swaps);

    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        ++swaps;
        heapify(arr, i, 0, comparisons, swaps);
    }
}

void runSortAlgorithm(std::span<Person> people_span)
{
    std::cout << "Initial array:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    int comparisons = 0, swaps = 0;

    // Запускаем и измеряем временя для Heap Sort
    auto start_heap = std::chrono::steady_clock::now();
    heapSort(people_span, comparisons, swaps);
    auto end_heap = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_heap = end_heap - start_heap;

    std::cout << "Array after Heap Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Heap Sort
    std::cout << "Heap Sort Comparisons: " << comparisons << std::endl;
    std::cout << "Heap Sort Swaps: " << swaps << std::endl;
    std::cout << "Heap Sort Time: " << elapsed_seconds_heap.count() << "s\n";
    std::cout << std::endl;
}

int main()
{
    runExample();
    
    return 0;
}
