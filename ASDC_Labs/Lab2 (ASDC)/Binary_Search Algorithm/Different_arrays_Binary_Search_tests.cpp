#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

// Бинарный поиск
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;  
}

// Генерация массива случайных чисел
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;  
    }
    return arr;
}

// Тестирование бинарного поиска
void testBinarySearch(const std::vector<int>& arr, int target) {
    auto start = std::chrono::high_resolution_clock::now();

    binarySearch(arr, target);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken for binary search: " << duration.count() << " seconds\n";
}

int main() 
{
    srand(time(0));  // генератора случайных чисел

    const int arraySize = 1000000;  
    const int target = rand() % 1000; 

    // Тестирование на разных массивах
    std::vector<int> sortedArray(arraySize);
    std::vector<int> reverseSortedArray(arraySize);
    std::vector<int> randomArray = generateRandomArray(arraySize);  // Случайный порядок элементов, хотя использовать в этом случае бинарный поиск - бессмысленно

    // Заполнение отсортированных массивов
    for (int i = 0; i < arraySize; ++i) {
        sortedArray[i] = i;
        reverseSortedArray[i] = arraySize - i - 1;
    }

    // Тестирование бинарного поиска
    testBinarySearch(sortedArray, target);
    testBinarySearch(reverseSortedArray, target);
    testBinarySearch(randomArray, target);

    return 0;
}
