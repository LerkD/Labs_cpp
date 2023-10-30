#include "dynamicArray.h"
#include <iostream>
#include <cassert>

DynamicArray createDynamicArrayWithCapacity(int capacity) {
    DynamicArray arr;
    arr.buffer = new int[capacity]; // Выделяем память для буфера (массива) с заданной начальной capacity
    arr.length = 0;
    arr.capacity = capacity;
    return arr;
}

DynamicArray createDynamicArray() {
    return createDynamicArrayWithCapacity(4); // Default capacity of 4
}

void addElementToArray(DynamicArray& arr, int element) {
    if (arr.length == arr.capacity) {
        // Проверяем, заполнен ли буфер
        // Если буфер полный, увеличиваем его вдвое
        int newCapacity = arr.capacity <= 0 ? 1 : arr.capacity * 2; // Учтем случай, когда capacity равен или меньше 0, в этом случае устанавливаем newCapacity = 1 
        int* newBuffer = new int[newCapacity]; // Создаем новый буфер с увеличенной capacity
        for (int i = 0; i < arr.length; i++) {
            newBuffer[i] = arr.buffer[i]; // Копируем существующие элементы в новый буфер
        }
        delete[] arr.buffer;
        arr.buffer = newBuffer;
        arr.capacity = newCapacity;
    }

    arr.buffer[arr.length] = element;
    arr.length++;
}

int getElementAtIndex(const DynamicArray& arr, int index) {
    assert(index >= 0 && index < arr.length);
    return arr.buffer[index];
}

std::span<int> getCurrentSpan(DynamicArray& arr) {
    return { arr.buffer, static_cast<size_t>(arr.length) };
}

void clearDynamicArray(DynamicArray& arr) {
    if (arr.buffer) { // Добавила проверку, чтобы не случилось повторного удаления буфера, если он уже был освобжден.
        delete[] arr.buffer;
        arr.buffer = nullptr; // Или лучше все-таки убрать обнуление вообще, даже не проверяя arr.bufer?
    }
    arr.length = 0;
    arr.capacity = 0;
}
