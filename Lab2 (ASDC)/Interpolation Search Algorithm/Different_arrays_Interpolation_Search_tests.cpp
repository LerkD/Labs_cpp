#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

// Алгоритм интерполяционного поиска
int interpolationSearch(const std::vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // Используем формулу интерполяции для оценки местоположения target
        int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]);

        if (arr[pos] == target) {
            return pos; // Элемент найден
        }

        if (arr[pos] < target) {
            low = pos + 1; // Искомый элемент в правой части
        } else {
            high = pos - 1; // Искомый элемент в левой части
        }
    }
    return -1; // Элемент не найден
}

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;  
    }
    return arr;
}

// Тестирование интерполяционного поиска
void testInterpolationSearch(const std::vector<int>& arr, int target) {
    auto start = std::chrono::high_resolution_clock::now();

    int result = interpolationSearch(arr, target);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    if (result != -1) {
        std::cout << "Элемент " << target << " найден по индексу " << result << std::endl;
    } else {
        std::cout << "Элемент " << target << " не найден в массиве" << std::endl;
    }

    std::cout << "Interpolation Search Time: " << duration.count() << " seconds" << std::endl;
    std::cout << std::endl;
}

int main() {
    srand(time(0)); // генератор случайных чисел

    const int arraySize = 1000000;
    const int target = rand() % 1000; // Элемент, который будем искать

    // Тестирование на разных массивах
    std::vector<int> sortedArray(arraySize);
    std::vector<int> reverseSortedArray(arraySize);
    std::vector<int> randomArray = generateRandomArray(arraySize);

    // Заполнение отсортированных массивов
    for (int i = 0; i < arraySize; ++i) {
        sortedArray[i] = i;
        reverseSortedArray[i] = arraySize - i - 1;
    }

    // Тестирование интерполяционного поиска
    testInterpolationSearch(sortedArray, target);
    testInterpolationSearch(reverseSortedArray, target);
    testInterpolationSearch(randomArray, target);

    return 0;
}
