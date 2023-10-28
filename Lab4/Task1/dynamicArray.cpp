#include "dynamicArray.h"
#include <iostream>
#include <cassert>

DynamicArray createDynamicArrayWithCapacity(int capacity) {
    DynamicArray arr;
    arr.buffer = new int[capacity]; // 
    arr.length = 0;
    arr.capacity = capacity;
    return arr;
}

DynamicArray createDynamicArray() {
    return createDynamicArrayWithCapacity(4); // Default capacity of 4
}

void addElementToArray(DynamicArray& arr, int element) {
    if (arr.length == arr.capacity) {
        // Double the capacity and reallocate the buffer
        int newCapacity = arr.capacity * 2;
        int* newBuffer = new int[newCapacity];
        for (int i = 0; i < arr.length; i++) {
            newBuffer[i] = arr.buffer[i];
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
    delete[] arr.buffer;
    arr.buffer = nullptr;
    arr.length = 0;
    arr.capacity = 0;
}
