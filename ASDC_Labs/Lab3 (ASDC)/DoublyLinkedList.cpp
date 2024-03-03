#include <iostream>
#include <array>

// Перечисление для пола
enum class Gender
{
    Boy,
    Girl
};

// Структура данных
struct Person
{
    std::array<char, 20> name; 
    int form;                   
    Gender gender;             
};

// Структура для двусвязного узла
struct Node
{
    Person data;   
    Node* next;    
    Node* prev;    // Добавляем езе указатель на предыдущий узел, так как теперь двусвязный список
};

// Структура для двусвязного списка
struct LinkedList
{
    Node* head; 
    Node* tail; 
    size_t size; 
};

// Структура для хранения результата поиска нода и его предшественника
struct FindNodeResult
{
    Node* previous;  
    Node* current;   
};

// Функция для печати списка
void printList(const LinkedList* list)
{
    const Node* current = list->head;

    while (current)
    {
        std::cout << "Name: " << current->data.name.data() << ", Form: " << current->data.form
                  << ", Gender: " << (current->data.gender == Gender::Boy ? "Boy" : "Girl") << std::endl;

        current = current->next;
    }

    std::cout << std::endl;
}

// Функция вставки нового узла после указанного узла(в начало, если узел nullptr)
Node* insertAfter(LinkedList* list, Node* node, const Person& value)
{
    Node* newNode = new Node{value, nullptr, nullptr};

    if (!list->head) // Пустой список
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else if (!node) // Вставка в начало списка
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    else // Вставка после указанного узла
    {
        newNode->next = node->next;
        newNode->prev = node;
        node->next = newNode;

        if (node == list->tail)
            list->tail = newNode;
        else
            newNode->next->prev = newNode;
    }

    list->size++;
    return newNode;
}

// Функция вставки нового узла перед указанным узлом (в конец, если узел nullptr)
Node* insertBefore(LinkedList* list, Node* node, const Person& value)
{
    Node* newNode = new Node{value, nullptr, nullptr};

    if (!list->head) // Если список пуст
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else if (!node) // Вставка в конец списка
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    else // Вставка перед указанным узлом
    {
        newNode->prev = node->prev;
        newNode->next = node;
        node->prev = newNode;

        if (node == list->head)
            list->head = newNode;
        else
            newNode->prev->next = newNode;
    }

    list->size++;
    return newNode;
}

// Функция поиска узла. В этот раз сделал с указанным полом ученика
Node* findByGender(const LinkedList* list, Gender gender)
{
    Node* current = list->head;

    while (current)
    {
        if (current->data.gender == gender)
            return current;

        current = current->next;
    }

    return nullptr; // Узел не найден
}

// Функция удаления указанного узла из списка по заданному ноду
void remove(LinkedList* list, Node* node)
{
    if (!node)
        return;

    if (node == list->head)
        list->head = node->next;
    else
        node->prev->next = node->next;

    if (node == list->tail)
        list->tail = node->prev;
    else
        node->next->prev = node->prev;

    delete node;
    list->size--;
}

// Функция для проверки отсутствия циклов в списке
void assertNoCycles(const LinkedList* list)
{
    Node* current = list->head;
    Node* nextJump = list->head;

    while (nextJump != nullptr && nextJump->next != nullptr)
    {
        current = current->next;
        nextJump = nextJump->next->next;

        if (current == nextJump)
        {
            std::cerr << "Ошибка! Где-то цикл, так как медленный указатель (current) встретился с быстрым, который перепригивает (nextJump)" << std::endl;
            return;
        }
    }

    std::cout << "Циклов нет, так как медленный указатель (current) не встретился с быстрым (nextJump)" << std::endl;
}

// Функция для освобождения памяти, выделенной под список
void cleanupList(LinkedList* list)
{
    Node* current = list->head;

    while (current)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }

    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

int main()
{
    // Пример использования для двусвязного списка с моей структурой - типом данных Person
    LinkedList personList{nullptr, nullptr, 0};

    // Вставка узлов
    Node* node1 = insertAfter(&personList, nullptr, Person{"Lera", 10, Gender::Girl});
    Node* node2 = insertAfter(&personList, node1, Person{"Catea", 8, Gender::Girl});
    Node* node3 = insertBefore(&personList, node2, Person{"Anton", 12, Gender::Boy}); // Теперь Антон перед Катей 

    // Печать списка
    std::cout << "Исходный двусвязный список:" << std::endl;
    printList(&personList);

    // Поиск узла по полу
    Node* genderNode = findByGender(&personList, Gender::Boy);
    if (genderNode)
        std::cout << "Найденный узел по полу: " << genderNode->data.name.data() << std::endl;

    // Удаление узла
    remove(&personList, node2);

    // Печать измененного списка
    std::cout << "\nДвусвязный список после удаления:" << std::endl;
    printList(&personList);

    // Проверка отсутствия циклов
    assertNoCycles(&personList);

    // Очистка памяти
    cleanupList(&personList);

    return 0;
}