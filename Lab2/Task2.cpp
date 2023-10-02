#include <stdlib.h>
#include <iostream>

struct TwoInts
{
    int a;
    int b;
};

struct StructWithArray
{
    int arr[4];
    int* someNumber;
};

int main()
{
    // Создание экземпляра структуры TwoInts и инициализация его полей
    TwoInts i2 = { };
    i2.a = 5;
    i2.b = 7;

    // Вывод значений полей структуры TwoInts
    std::cout << i2.a << std::endl; // Вывод: 5
    std::cout << i2.b << std::endl; // Вывод: 7

    // Создание экземпляра структуры StructWithArray и инициализация его первого элемента
    StructWithArray s = { };
    s.arr[0] = 10;

    // Создание еще одного экземпляра структуры StructWithArray и инициализация его первого элемента
    StructWithArray s1 = { };
    s1.arr[0] = 15;

    // Создание указателя sPointer, который указывает на структуру s
    StructWithArray* sPointer = &s;
    sPointer->arr[0] = 20;

    // Вывод значения первого элемента массива s через sPointer (теперь 20)
    std::cout << s.arr[0] << std::endl; // Вывод: 20

    // Прямое изменение значения первого элемента массива s (теперь 25)
    s.arr[0] = 25;
    std::cout << s.arr[0] << std::endl; // Вывод: 25

    // Изменение значения первого элемента массива s через sPointer (теперь 30)
    sPointer->arr[0] = 30;
    std::cout << s.arr[0] << std::endl; // Вывод: 30

    // Перенаправление sPointer, чтобы он указывал на структуру s1
    sPointer = &s1;
    sPointer->arr[0] = 35;

    // Вывод значения первого элемента массива s (по-прежнему 30)
    std::cout << s.arr[0] << std::endl; // Вывод: 30

    // Вывод значения первого элемента массива s1 (теперь 35)
    std::cout << s1.arr[0] << std::endl; // Вывод: 35

    // Создание массива из двух структур StructWithArray и инициализация элементов
    StructWithArray structArray[2] = { };
    structArray[0].arr[3] = 77;
    structArray[1].someNumber = &structArray[0].arr[3];

    // Перенаправление sPointer, чтобы он указывал на структуру s
    sPointer = &s;

    // Создание указателя pointer, который указывает на четвертый элемент массива s
    int* pointer = &sPointer->arr[3];

    // Прямое изменение четвертого элемента массива s (теперь 72)
    s.arr[3] = 72;

    // Вывод значения, на которое указывает pointer (теперь 72)
    std::cout << *pointer; // Вывод: 72

    // Создание структуры memory и заполнение ее памяти нулями
    StructWithArray memory;
    memset(&memory, 0, sizeof(StructWithArray));

    return 0;
}
