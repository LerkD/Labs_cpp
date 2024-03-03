#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

// Линейный поиск
int linearSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;  // Элемент не найден
}

// Генерация массива случайных чисел
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;  
    }
    return arr;
}

// Тестирование линейного поиска
void testLinearSearch(const std::vector<int>& arr, int target) {
    auto start = std::chrono::high_resolution_clock::now();

    linearSearch(arr, target);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken for linear search: " << duration.count() << " seconds\n";
}

int main() 
{
     srand(time(0));  //  генератора случайных чисел

    const int arraySize = 1000000;  
    const int target = rand() % 1000;  // Элемент, который будем искать

    // Тестирование на разных массивах
    std::vector<int> sortedArray(arraySize);
    std::vector<int> reverseSortedArray(arraySize);
    std::vector<int> randomArray = generateRandomArray(arraySize);  

    // Заполнение отсортированных массивов
    for (int i = 0; i < arraySize; ++i) {
        sortedArray[i] = i;
        reverseSortedArray[i] = arraySize - i - 1;
    }

    // Тестирование линейного поиска
    testLinearSearch(sortedArray, target);
    testLinearSearch(reverseSortedArray, target);
    testLinearSearch(randomArray, target);

    return 0;
}
