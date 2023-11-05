#include "dynamicArray.h"
#include <iostream>
#include <cassert>

int main() {
    // Тест 1: Создаем DynamicArray с дефолтным capacity (4)
    {
        DynamicArray<int> arr1;
        assert(arr1.capacity() = DynamicArray<int>::DEFAULT_CAPACITY); 
    }

    // Тест 2: Добавляем элемент и проверяем длину
    {
        DynamicArray<int> arr1;
        arr1.add(15);
        assert(arr1.size() == 1); // Проверяем длину после добавления элемента
    }

    // Тест 3: Проверяем увеличение capacity при добавлении элементов
    {
        DynamicArray<int> arr2(1);
        arr2.add(10);
        assert(arr2.capacity() == 1);
        arr2.add(20);
        assert(arr2.capacity() == 2);
        arr2.add(40);
        assert(arr2.capacity() == 4); // Проверяем увеличение capacity
    }

    // Тест 4: Доступ к элементу по индексу
    {
        DynamicArray<int> arr2(1);
        arr2.add(15);
        assert(arr2[0] == 15); // Проверяем доступ к элементу по индексу
    }

    // Тест 5: Итерация через foreach
    {
        DynamicArray<int> arr3;
        arr3.add(15);
        arr3.add(16);
        arr3.add(17);

        int expected[] = {15, 16, 17};
        int i = 0;

        for (int element : arr3) {
            assert(element == expected[i]); // Добавила еще проверку элементов в цикле
            i++;
        }
    }

    // Тест 6: Очистка массива и добавление элементов после очистки
    {
        DynamicArray<int> arr4;
        arr4.add(10);
        arr4.add(20);
        assert(arr4.size() == 2);
        arr4.clear(); // Очистила массив
        assert(arr4.size() == 0);
        arr4.add(30); // Добавила элементы после очистки
        arr4.add(40);
        assert(arr4.size() == 2); // Проверяю, что элементы добавились 
    }

    std::cout << "Все тесты пройдены!" << std::endl;
}
