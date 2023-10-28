#include "dynamicArray.h"

// Конструктор без параметров (дефолтный capacity)
template <typename T>
DynamicArray<T>::DynamicArray() : buffer(nullptr), length(0), maxCapacity(4) {
    buffer = new T[maxCapacity];
}

// Конструктор с заданным начальным capacity
template <typename T>
DynamicArray<T>::DynamicArray(size_t capacity) : buffer(nullptr), length(0), maxCapacity(capacity) {
    buffer = new T[maxCapacity];
}

// Деструктор
template <typename T>
DynamicArray<T>::~DynamicArray() {
    clear();
}

// Конструктор копирования
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : buffer(nullptr), length(0), maxCapacity(other.maxCapacity) {
    buffer = new T[maxCapacity];
    for (size_t i = 0; i < other.length; i++) {
        buffer[i] = other.buffer[i];
    }
    length = other.length;
}

// Оператор присваивания
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        clear();
        maxCapacity = other.maxCapacity;
        buffer = new T[maxCapacity];
        for (size_t i = 0; i < other.length; i++) {
            buffer[i] = other.buffer[i];
        }
        length = other.length;
    }
    return *this;
}

// Move-конструктор
template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) {
    buffer = other.buffer;
    length = other.length;
    maxCapacity = other.maxCapacity;
    other.buffer = nullptr;
    other.length = 0;
    other.maxCapacity = 0;
}

// Добавление элемента в массив
template <typename T>
void DynamicArray<T>::add(const T& element) {
    if (length == maxCapacity) {
        increaseCapacity();
    }
    buffer[length] = element;
    length++;
}

// Доступ к элементу по индексу
template <typename T>
T& DynamicArray<T>::operator[](size_t index) {
    assert(index >= 0 && index < length);
    return buffer[index];
}

// Методы для чтения полей (read-only properties)
template <typename T>
size_t DynamicArray<T>::size() const {
    return length;
}

template <typename T>
size_t DynamicArray<T>::capacity() const {
    return maxCapacity;
}

// Метод для увеличения capacity (при необходимости)
template <typename T>
void DynamicArray<T>::increaseCapacity() {
    maxCapacity *= 2;
    T* newBuffer = new T[maxCapacity];
    for (size_t i = 0; i < length; i++) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
}

// Очистка памяти
template <typename T>
void DynamicArray<T>::clear() {
    delete[] buffer;
    buffer = nullptr;
    length = 0;
    maxCapacity = 0;
}

// Явно инстанцируем класс для int
template class DynamicArray<int>;
