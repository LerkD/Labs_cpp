#include <iostream>
#include <string>
#include <array>
#include <span>
#include <chrono>

// Перечисление для пола
enum class Gender
{
    Boy,
    Girl
};

// Моя структура данных Person
struct Person
{
    std::array<char, 20> name;
    int form;
    Gender gender;
};

// Функция вывода массива Person
void printPeople(const std::span<Person>& arr)
{
    for (const auto& person : arr)
    {
        std::cout << "Name: " << person.name.data() << ", Form: " << person.form
                  << ", Gender: " << (person.gender == Gender::Boy ? "Boy" : "Girl") << std::endl;
    }
}

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
