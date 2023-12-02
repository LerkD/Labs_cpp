#include "dynamicArray.h"

// Конструктор без параметров (дефолтный capacity)
template <typename T>
DynamicArray<T>::DynamicArray() : DynamicArray(DEFAULT_CAPACITY) {}

// Конструктор с заданным начальным capacity
template <typename T>
DynamicArray<T>::DynamicArray(size_t capacity /* = DEFAULT_CAPACITY */) : buffer(nullptr), length(0), _capacity(capacity) {
    buffer = new T[_capacity];
}


// Деструктор
template <typename T>
DynamicArray<T>::~DynamicArray() {
    destroy();
}

// Конструктор копирования
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : buffer(nullptr), length(0), _capacity(other._capacity) {
    buffer = new T[_capacity];
    for (size_t i = 0; i < other.length; i++) {
        buffer[i] = other.buffer[i];
    }
    length = other.length;
}

// Оператор присваивания
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        ensureCapacity(other._capacity); // Поменяла clear() на ensureCapacity(). Увеличиваем капесити при необходимости, сохраняя текущие данные
        // Наверное, так будет все-таки рациональнее, потому что не нужно полностью освобождать память и создовать новый буфер.
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
    _capacity = other._capacity;
    other.buffer = nullptr;
    other.length = 0;
    other._capacity = 0;
}

// Добавление элемента в массив
template <typename T>
void DynamicArray<T>::add(const T& element) {
    if (length == _capacity) {
        increaseCapacity();
    }
    buffer[length] = element;
    length++;
}


// Метод для увеличения capacity (при необходимости)
template <typename T>
void DynamicArray<T>::increaseCapacity() {
    _capacity =  (_capacity <= 0) ? 1 : _capacity * 2; // Учтем случай, когда capacity равен или меньше 0, в этом случае устанавливаем newCapacity = 1 
    T* newBuffer = new T[_capacity];
    for (size_t i = 0; i < length; i++) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
}

// Очистка памяти
template <typename T>
void DynamicArray<T>::destroy() {
    if (buffer) { // Тут тоже добавила эту проверку, как и в 1 таске, чтобы не было повторного удаления 
        delete[] buffer; 
        length = 0;
    }
}

// Явно инстанцируем класс для int
template class DynamicArray<int>;
