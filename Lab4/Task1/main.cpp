#include "dynamicArray.h"
#include <iostream>
#include <cassert>

void static test1() {
    DynamicArray arr = createDynamicArrayWithCapacity(10);
    assert(arr.capacity == 10);
}

void static test2() {
     // Тест 2: Создаем динамический массив с дефолтной capacity (4) и добавляем элемент
    DynamicArray arr = createDynamicArray();
    assert(arr.length == 0); // массив пустой
    addElementToArray(&arr, 10); // добавляем элемент 
    assert(arr.length == 1); // Проверяем, что длина массива увеличилась на 1
}

void static test3() {
    // Тест 3: Создаем динамический массив с начальной capacity 1 и добавляем элементы
    DynamicArray arr = createDynamicArrayWithCapacity(1);
    addElementToArray(&arr, 10);
    assert(arr.capacity == 1);
    addElementToArray(&arr, 20);
    assert(arr.capacity == 2);
    addElementToArray(&arr, 40);
    assert(arr.capacity == 4);
}

void static test4() {
    DynamicArray arr = createDynamicArray();
    addElementToArray(&arr, 5);
    int el = getElementAtIndex(&arr, 0);
    assert(el == 5); // Проверяем, что полученный элемент равен 5
}

void static test5() {
    DynamicArray arr{};
    addElementToArray(&arr, 15);
    addElementToArray(&arr, 16);
    addElementToArray(&arr, 17);

    std::span<int> span = getCurrentSpan(arr);

    assert(span.size() == 3);
    assert(span[0] == 15);
    assert(span[1] == 16);
    assert(span[2] == 17);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
