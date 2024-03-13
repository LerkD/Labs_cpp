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
bool isEmpty(const Stack* stack)
{
    return stack->top == nullptr;
}

// Добавление элемента на вершину стека
void push(Stack* stack, const Person& value)
{
    StackNode* newNode = new StackNode{value, stack->top};
    stack->top = newNode;
    stack->size++;
}

// Получаем указатель на вершину стека (без удаления)
StackNode* getLastElement(Stack* stack)
{
    return stack->top;
}

// Удаляем элемент на вершине стека
void pop(Stack* stack)
{
    if (isEmpty(stack))
    {
        std::cerr << "Ошибка: стек пуст!" << std::endl;
        return;
    }

    StackNode* temp = stack->top;
    stack->top = temp->next;
    delete temp;
    stack->size--;
}

// Очищаем память
void cleanupStack(Stack* stack)
{
    while (!isEmpty(stack))
    {
        pop(stack);
    }
}

// Печатаем стек
void printStack(const Stack* stack)
{
    const StackNode* current = stack->top;

    while (current)
    {
        std::cout << "Name: " << current->data.name.data() << ", Form: " << current->data.form
                  << ", Gender: " << (current->data.gender == Gender::Boy ? "Boy" : "Girl") << std::endl;

        current = current->next;
    }

    std::cout << std::endl;
}

int main()
{
    // Пример использования для стека с моей структурой - типом данных Person
    Stack personStack{nullptr, 0};

    // Добавляем элементы в стек
    push(&personStack, Person{"Lera", 10, Gender::Girl});
    push(&personStack, Person{"Catea", 8, Gender::Girl});
    push(&personStack, Person{"Anton", 12, Gender::Boy}); // Пришел последний, уйдет первый, По принципу LIFO

    // Вывод содержимого стека
    std::cout << "Исходный стек:" << std::endl;
    printStack(&personStack);


    // Получаем указатель на вершину стека
    StackNode* topElement = getLastElement(&personStack);
    if (topElement)
    {
        std::cout << "Вершина стека до удаления: " << topElement->data.name.data() << std::endl;
    }

    // Удаление элемента с вершины стека
    pop(&personStack);
    std::cout << std::endl;

    StackNode* top1Element = getLastElement(&personStack);
    if (topElement)
    {
        std::cout << "Вершина стека после удаления: " << top1Element->data.name.data() << std::endl;
    }

    // Вывод содержимого стека после удаления верхнего элемента
    std::cout << "\nОбновленный стек:" << std::endl;
    printStack(&personStack);

    // Очистка памяти
    cleanupStack(&personStack);

    return 0;
}
