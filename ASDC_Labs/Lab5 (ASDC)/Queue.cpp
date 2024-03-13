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

// Структура для узла в очереди
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

// Функция для печати очереди
void printQueue(const Queue* queue)
{
   
    QueueNode* current = queue->head;

    while (current)
    {
        std::cout << "Name: " << current->data.name.data() << ", Form: " << current->data.form
                  << ", Gender: " << (current->data.gender == Gender::Boy ? "Boy" : "Girl") << std::endl;

        current = current->next;
    }

    std::cout << std::endl;
}

// Функция для добавления элемента в конец очереди
void enqueue(Queue* queue, const Person& value)
{
    QueueNode* newNode = new QueueNode{value, nullptr};

    if (!queue->head) // Если очередь пуста
    {
        queue->head = newNode;
        queue->tail = newNode;
    }
    else // Добавление в конец очереди
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

// Функция для удаления элемента из начала очереди и возврата его значения
Person dequeue(Queue* queue)
{
    if (!queue->head)
    {
        // Очередь пуста, возвращаем значение по умолчанию
        std::cerr << "Очередь пустая. Возвращем значение по умолчанию." << std::endl;
        return Person{};
    }

    Person value = queue->head->data;
    QueueNode* tempNode = queue->head;

    queue->head = queue->head->next;

    if (!queue->head) // Если после удаления очередь пуста, переношу указатель на конец
        queue->tail = nullptr;

    delete tempNode;

    return value;
}

// Функция для проверки, пустая ли очередь (Как и указано в задание возвращаю true если очередь пуста, иначе false)
bool isEmpty(const Queue* queue)
{
    return queue->head == nullptr;
}

// Функция для освобождения памяти, выделенной под очередь
void cleanupQueue(Queue* queue)
{
    while (!isEmpty(queue))
    {
        dequeue(queue);
    }
}


int main()
{
    // Пример использования для очереди с моей структурой - типом данных Person
    Queue personQueue{nullptr, nullptr};

    // Добавляем учеников в очередь
    enqueue(&personQueue, Person{"Lera", 10, Gender::Girl});
    enqueue(&personQueue, Person{"Catea", 8, Gender::Girl});
    enqueue(&personQueue, Person{"Anton", 12, Gender::Boy});

    // Вывод содержимого очереди
    std::cout << "Исходная очередь:" << std::endl;
    printQueue(&personQueue);

    // Удаление элемента из начала очереди
    Person removedPerson = dequeue(&personQueue);
    std::cout << "Удаленный элемент: " << removedPerson.name.data() << std::endl;

    // Вывод обновленной очереди
    std::cout << "\nОчередь после удаления:" << std::endl;
    printQueue(&personQueue);

    // Очистка памяти
    cleanupQueue(&personQueue);

    return 0;
}