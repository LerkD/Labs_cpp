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
    T& operator[](size_t index);

    // Методы для чтения полей (read-only properties)
    size_t size() const;
    size_t capacity() const;

private:
    T* buffer;        // Указатель на буфер
    size_t length;    // Текущее количество элементов
    size_t maxCapacity; // Максимальная capacity (вместимость)

    // Метод для увеличения capacity (при необходимости)
    void increaseCapacity();

    // Очистка памяти
    void clear();
};
