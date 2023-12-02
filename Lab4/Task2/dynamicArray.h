#pragma once
#include <cassert>
#include <cstddef> // Для size_t

template <typename T>
class DynamicArray {
public:
    inline static const size_t DEFAULT_CAPACITY = 4;

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
    void clear();
   
    

    // Доступ к элементу по индексу
   inline T& operator[](size_t index) { // Определила его здесь, как inline
        assert(index >= 0 && index < length);
        return buffer[index];
    }

    // Методы для чтения полей (read-only properties), тоже определила здесь, как inline
    inline size_t size() const 
    {
        return length;
    }
    inline size_t capacity() const
    {
        return _capacity;
    }

private:
    T* buffer;        // Указатель на буфер
    size_t length;    // Текущее количество элементов
    size_t _capacity; // Максимальная capacity (вместимость)

    // Метод для увеличения capacity (при необходимости)
    void increaseCapacity();
    void destroy();

};
