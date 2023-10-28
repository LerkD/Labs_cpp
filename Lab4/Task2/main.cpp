
#include "dynamicArray.h"
#include <iostream>
#include <cassert>

int main() {
    // Тест 1: Создаем DynamicArray с дефолтным capacity (4)
    DynamicArray<int> arr1;
    assert(arr1.capacity() == 4);

    // Тест 2: Добавляем элемент и проверяем длину
    arr1.add(15);
    assert(arr1.size() == 1);

    // Тест 3: Проверяем увеличение capacity при добавлении элементов
    DynamicArray<int> arr2(1);
    arr2.add(10);
    assert(arr2.capacity() == 1);
    arr2.add(20);
    assert(arr2.capacity() == 2);
    arr2.add(40);
    assert(arr2.capacity() == 4);

    // Тест 4: Доступ к элементу по индексу
    assert(arr2[0] == 15);

    // Тест 5: Итерация через foreach
    DynamicArray<int> arr3;
    arr3.add(15);
    arr3.add(16);
    arr3.add(17);

    for (int element : arr3) {
        std::cout << element << " ";
    }
    std::cout << std::endl
}