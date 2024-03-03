#include <iostream>
#include <array>
#include <cassert>

// Перечисление для пола
enum class Gender
{
    Boy,
    Girl
};

// Структура ученика
struct Person
{
    std::array<char, 20> name;  
    int form;                   
    Gender gender;            
};

// Структура узла списка
struct Node
{
    Person data;  // Данные узла - объект Person
    Node* next;   // Указатель на следующий узел
};

// Структура связного списка
struct LinkedList
{
    Node* head;    
    Node* tail;    
    size_t size;  
};

// Структура для результата поиска узла
struct FindNodeResultByForm
{
    Node* previous; 
    Node* current;  
};


// Темплейт вставки нового узла после указанного (в начало, если узел nullptr)
template<typename T>
Node* insertAfter(LinkedList* list, Node* node, T value)
{
    Node* newNode = new Node{value, nullptr};

    if (!list->head) // Cписок пуст
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else if (!node) // В начало списка
    {
        newNode->next = list->head;
        list->head = newNode;
    }
    else // После указанного узла
    {
        newNode->next = node->next;
        node->next = newNode;

        if (node == list->tail)
            list->tail = newNode;
    }

    list->size++;
    return newNode;
}

// Функция поиска узла по указанному классу ученика
FindNodeResultByForm find(LinkedList* list, int value)
{
    FindNodeResultByForm result{nullptr, list->head};

    while (result.current && result.current->data.form != value)
    {
        result.previous = result.current;
        result.current = result.current->next;
    }

    return result;
}

// Функция удаления узла после указанного (или первого, если узел nullptr)
void removeAfter(LinkedList* list, Node* node)
{
    if (!list->head || (node && !node->next))
        return; // Нечего удалять

    Node* toRemove;
    
    if (!node) // Удаление первого узла
    {
        toRemove = list->head;
        list->head = toRemove->next;

        if (list->tail == toRemove)
            list->tail = nullptr;
    }
    else // Удаление узла после указанного
    {
        toRemove = node->next;
        node->next = toRemove->next;

        if (list->tail == toRemove)
            list->tail = node;
    }

    delete toRemove;
    list->size--;
}

// Функция проверки отсутствия циклов в связном списке
void assertNoCycles(LinkedList* list)
{
    size_t calculatedSize = 0;
    Node* current = list->head;

    while (current)
    {
        calculatedSize++;
        current = current->next;

        // Если посчитанный размер становится больше хранимого размера, значит, где-тл цикл
        assert(calculatedSize <= list->size);
    }
    if (calculatedSize == list->size)
    {
        std::cout << "Циклов нет, так как посчитаный размер списка равен хранимому размеру списка и равен: " << calculatedSize << std::endl;
    }
}

// Функция печати списка
void printList(const LinkedList* list)
{
    Node* current = list->head;

    while (current)
    {
        std::cout << "Name: " << current->data.name.data() << ", Form: " << current->data.form << ", Gender: "
                  << (current->data.gender == Gender::Boy ? "Boy" : "Girl") << std::endl;

        current = current->next;
    }
    std::cout << std::endl;
}

// Функция освобождения памяти
void cleanupList(LinkedList* list)
{
    Node* current = list->head;
    Node* next;

    while (current)
    {
        next = current->next;
        delete current;
        current = next;
    }

    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

int main()
{
    // Пример использования для LinkedList с моей структурой- типом данных Person
    LinkedList personList{nullptr, nullptr, 0};

    // Вставка узлов
    Node* node1 = insertAfter(&personList, nullptr, Person{"Lera", 10, Gender::Girl});
    Node* node2 = insertAfter(&personList, node1, Person{"Catea", 8, Gender::Girl});
    Node* node3 = insertAfter(&personList, node2, Person{"Anton", 12, Gender::Boy});

    // Печать списка
    std::cout << "Исходный список:" << std::endl;
    printList(&personList);

    // Поиск узла
    FindNodeResultByForm result = find(&personList, 10);
    if (result.current)
        std::cout << "Найденный узел: " << result.current->data.name.data() << std::endl;

    // Удаление узла
    removeAfter(&personList, node1);

    // Печать нового списка
    std::cout << "\nСписок после удаления:" << std::endl;
    printList(&personList);

    // Проверка отсутствия циклов
    assertNoCycles(&personList);

    // Очистка памяти
    cleanupList(&personList);

    return 0;
}