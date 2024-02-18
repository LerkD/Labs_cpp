// Алгоритм интерполяционного поиска.
// Особенно эффективен, когда элементы в массиве равномерно распределены.

#include <iostream>
#include <chrono>

// Функция для интерполяционного поиска
int interpolationSearch(int arr[], int n, int x) {
    int low = 0, high = n - 1;

    while (low <= high && x >= arr[low] && x <= arr[high]) {
        // Используем формулу интерполяции для оценки местоположения x
        int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]);

        if (arr[pos] == x)
            return pos; // Элемент найден

        if (arr[pos] < x)
            low = pos + 1; // Искомый элемент в правой части
        else
            high = pos - 1; // Искомый элемент в левой части
    }
    return -1; // Элемент не найден
}

int main() {

    srand(time(nullptr));

    for (int test = 1; test <= 6; ++test) {
        int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
        int n = sizeof(arr) / sizeof(arr[0]);
        
        int x = rand() % 20; // Рандомное значение для поиска

    // Измерение времени выполнения интерполяционного поиска
    auto start = std::chrono::high_resolution_clock::now();
    int result = interpolationSearch(arr, n, x);
    auto end = std::chrono::high_resolution_clock::now();

    if (result != -1)
    {
        std::cout << "Элемент " << x << " найден по индексу " << result << std::endl;
    }
    else 
    {
        std::cout << "Элемент " << x << " не найден в массиве" << std::endl;
    }

    std::chrono::duration<double> duration = end - start;
    std::cout << "Interpolation Search Time: " << duration.count() << " seconds" <<std::endl;
    std::cout << std::endl;
    }
    return 0;
}
