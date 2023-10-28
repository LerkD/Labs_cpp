#pragma once
#include "dynamicArray.h"
#include <iostream>
#include <span>


struct DynamicArray {
    int* buffer; //  указатель на буфер, который хранит элементы массива.
    int length; // текущее количество элементов в массиве.
    int capacity; // максимальная длина буфера
};

DynamicArray createDynamicArrayWithCapacity(int capacity); // создаем динамический массив с заданной начальной максимальной длиной (capacity). 
//Она выделяет память для буфера и инициализирует остальные поля структуры.
DynamicArray createDynamicArray(); // создаем динамический массив с дефолтной начальной максимальной длиной (4 элемента). 
// Она просто вызывает createDynamicArrayWithCapacity с аргументом 4.
void addElementToArray(DynamicArray& arr, int element); //  добавляем элемент в конец массива. 
// Если массив полный (длина равна capacity), она удваивает длину массива, выделяет новый буфер и копирует элементы в новый буфер.
int getElementAtIndex(const DynamicArray& arr, int index); // возвращаем элемент по заданному индексу в массиве. 
// Она проверяет, что индекс находится в допустимых пределах.
std::span<int> getCurrentSpan(DynamicArray& arr); // возвращаем std::span<int>, представляющий текущий срез (slice) массива. Этот срез может использоваться для доступа к данным в массиве. О
// Этот срез становится недействительным после добавления элементов.
void clearDynamicArray(DynamicArray& arr); // освобождаем память, выделенную для буфера массива. 
// Ее вызываем, когда массив больше не нужен.
