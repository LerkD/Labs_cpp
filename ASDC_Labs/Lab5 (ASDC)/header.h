#pragma once // Один раз при кампиляции подключаем 

#include <iostream>
#include <array>

// Перечисление для пола
enum class Gender
{
    Boy,
    Girl
};

// Структура для данных
struct Person
{
    std::array<char, 20> name;
    int form;
    Gender gender;
};

// Структура для узла стека
struct StackNode
{
    Person data;
    StackNode* next;
};

// Структура для стека
struct Stack
{
    StackNode* top;
    size_t size;
};

// Является ли стек пустым
bool isEmpty(const Stack* stack);

// Добавление элемента на вершину стека
void push(Stack* stack, const Person& value);

// Получаем указатель на вершину стека (без удаления)
StackNode* getLastElement(Stack* stack);

// Удаляем элемент на вершине стека
void pop(Stack* stack);

// Очищаем память стека
void cleanupStack(Stack* stack);

// Печатаем стек
void printStack(const Stack* stack);

// Структура для узла очереди
struct QueueNode
{
    Person data;
    QueueNode* next;
};

// Структура для очереди
struct Queue
{
    QueueNode* head;
    QueueNode* tail;
};

// Добавление элемента в конец очереди
void enqueue(Queue* queue, const Person& value);

// Удаление элемента из начала очереди и возврат его значения
Person dequeue(Queue* queue);

// Проверка, пуста ли очередь
bool isEmpty(const Queue* queue);

// Очищаем память очереди
void cleanupQueue(Queue* queue);

// Печатаем очередь
void printQueue(const Queue* queue);
