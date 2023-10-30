#pragma once

#include <cstddef> // Для size_t

template <typename T>
class DynamicArray {
public:
    // Конструктор без параметров (дефолтный capacity)
    DynamicArray();

    // Конструктор с заданным начальным capacity
    DynamicArray(size_t capacity);

    // Деструктор
    ~DynamicArray();

    // Конструктор копирования
    DynamicArray(const DynamicArray& other);

    // Оператор присваивания
    DynamicArray& operator=(const DynamicArray& other);

    // Move-конструктор
    DynamicArray(DynamicArray&& other);

    // Добавление элемента в массив
    void add(const T& element);

    // Доступ к элементу по индексу
    T& operator[](size_t index) { // Определила его здесь, как inline
        assert(index >= 0 && index < length);
        return buffer[index];
    }

    // Методы для чтения полей (read-only properties), тоже определила здесь, как inline
    size_t size() const 
    {
        return length;
    }
    size_t capacity() const
    {
        return _capacity;
    }

private:
    T* buffer;        // Указатель на буфер
    size_t length;    // Текущее количество элементов
    size_t _capacity; // Максимальная capacity (вместимость)

    // Метод для увеличения capacity (при необходимости)
    void increaseCapacity();

};
