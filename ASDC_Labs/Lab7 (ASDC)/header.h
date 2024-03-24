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

