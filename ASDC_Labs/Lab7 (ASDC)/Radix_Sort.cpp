#include "header1.h"

// Radix Sort - Поразрядная сортировка 
void radixSort(std::span<Person> arr, int& comparisons, int& swaps)
{
    // Находим максимальное значение класса для определения количества цифр
    int max = arr[0].form;
    for (const auto& person : arr)
    {
        if (person.form > max)
            max = person.form;
    }

    // Применяем сортировку подсчетом для каждой цифры в числе
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        std::array<std::vector<Person>, 10> buckets;

        // Распределяем элементы в бакеты исходя ищ цифры в числе
        for (const auto& person : arr)
        {
            int bucketIndex = (person.form / exp) % 10;
            buckets[bucketIndex].push_back(person);
        }

        // Обновляем исходный массив, перенося элементы из бакетов
        int index = 0;
        for (auto& bucket : buckets)
        {
            for (const auto& person : bucket)
            {
                arr[index++] = person;
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

    // Запускаем и измеряем время для Radix Sort
    auto start_radix = std::chrono::steady_clock::now();
    radixSort(people_span, comparisons, swaps);
    auto end_radix = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_radix = end_radix - start_radix;

    std::cout << "Array after Radix Sort:" << std::endl;
    printPeople(people_span);
    std::cout << std::endl;

    // Вывод всей информации для Radix Sort
    std::cout << "Radix Sort Comparisons: " << comparisons /*Будет 0*/ << std::endl; // По сути не нужно, так как алгоритм Radix Sort не зависит от сравнений элементов.
    std::cout << "Radix Sort Swaps: " << swaps << std::endl;
    std::cout << "Radix Sort Time: " << elapsed_seconds_radix.count() << "s\n";
    std::cout << std::endl;
}
int main()
{
   runExample();

    return 0;
}
