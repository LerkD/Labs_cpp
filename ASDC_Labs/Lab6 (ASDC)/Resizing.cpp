// Скоро добавляю хедер для всех 3 файлов 

#include <iostream>
#include <string_view>
#include <array>
#include <cmath>

// Перечисление для пола
enum class Gender 
{
    Boy,
    Girl
};

// Моя структура данных Person
struct Person 
{
    std::array<char, 20> name;
    int form;
    Gender gender;
};

// Структура для нода в хэш-таблице
struct BucketNode
{
    Person value;
    std::string_view key;
    BucketNode* next;
};

// Структура для хэш bтаблицы
struct HashTable 
{
    std::array<BucketNode*, 10> buckets;
    size_t (*hashFunc)(std::string_view);
    size_t size; // Кол-во элементов сейчас 
    size_t capacity; // Вместиность сейчас 
    const float loadFactor = 0.9f; // Максимально допустимая заполниность 
};

// Функция вычисления индекса для ключа
size_t computeIndex(HashTable* table, std::string_view key) 
{
    size_t hash = table->hashFunc(key);
    size_t index = hash % table->capacity;
    return index;
}

// Функция поиска значения по ключу
Person* find(HashTable* table, std::string_view key) 
{
    size_t index = computeIndex(table, key);
    BucketNode* currentNode = table->buckets[index];
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return &currentNode->value;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

// Resizing таблицы
void resize(HashTable* table) 
{
    size_t newCapacity = table->capacity * 2;
    HashTable newTable;
    newTable.hashFunc = table->hashFunc;
    newTable.capacity = newCapacity;
    newTable.size = 0;
    newTable.buckets.fill(nullptr);

    for (size_t i = 0; i < table->capacity; ++i) {
        BucketNode* currentNode = table->buckets[i];
        while (currentNode != nullptr) {
            BucketNode* nextNode = currentNode->next;
            size_t newIndex = computeIndex(&newTable, currentNode->key);
            currentNode->next = newTable.buckets[newIndex];
            newTable.buckets[newIndex] = currentNode;
            ++newTable.size;
            currentNode = nextNode;
        }
    }

    table->buckets = std::move(newTable.buckets);
    table->capacity = newCapacity;
}

// Функция добавления элемента. Тут же происходит и resizing 
Person* add(HashTable* table, std::string_view key) 
{
    if ((float)(table->size + 1) / table->capacity > table->loadFactor) 
    {
        resize(table);
        std::cout <<"\nResizing was completed. New capacity is " << table ->capacity  << std:: endl;
        std::cout << std::endl;
    }

    size_t index = computeIndex(table, key);
    BucketNode* newNode = new BucketNode{{}, key, nullptr};
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    ++table->size;
    return &(newNode->value);
}

// Функция удаления элемента по ключу
void remove(HashTable* table, std::string_view key) 
{
    size_t index = computeIndex(table, key);
    BucketNode* currentNode = table->buckets[index];
    BucketNode* prevNode = nullptr;
    while (currentNode != nullptr) 
    {
        if (currentNode->key == key) 
        {
            if (prevNode) 
            {
                prevNode->next = currentNode->next;
            } else 
            {
                table->buckets[index] = currentNode->next;
            }
            delete currentNode;
            --table->size;
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

// Функция освобождения памяти
void free(HashTable* table) 
{
    for (size_t i = 0; i < table->capacity; ++i) 
    {
        BucketNode* currentNode = table->buckets[i];
        while (currentNode != nullptr) 
        {
            BucketNode* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }
}

// Функция хэширования: суммирует коды по таблице ASCII символов ключа
size_t hashFunc(std::string_view key) 
{
    size_t hash = 0;
    for (char c : key) 
    {
        hash += static_cast<size_t>(c);
    }
    return hash;
}

// Функция создания хэш-таблицы с заданным capacity и хэш функцией
HashTable createHashTable(size_t capacity, size_t (*hashFunc)(std::string_view)) 
{
    HashTable table;
    table.hashFunc = hashFunc;
    table.capacity = capacity;
    table.size = 0;
    table.buckets.fill(nullptr);
    return table;
}

// Функция вывода информации о человеке
void printPerson(const Person* person) 
{
    std::cout << "Name: " << person->name.data() << ", Form: " << person->form
              << ", Gender: " << (person->gender == Gender::Boy ? "Boy" : "Girl") << std::endl;
}

int main() 
{
    // Создаем хэш таблицы с функцией хэширования и заданным capacity
    HashTable table = createHashTable(1, hashFunc); 

    /* Если первоначальная capacity == 1, а loadFacor = 0.9, значит уже до добовления первого элемента произойдет resizing, 
    так как, без него заполняемость была бы 1. После первого resize, вместимость стала 2, так как удвоилась.
    Затем добавляется 1 элемент, и происходит resizing eще раз, так как опят была бы заполняемость 1, после второго элемента.
    Теперь capacity еще раз удвоилась и стала 4. Затем добавляется 2 и 3 элемент уже без resizing, т.к после второго элемента 
    вместимость 0.5, а после 3 - 0.75, что меньше максимальной. */

    // Добавление элемента "Lera"
    Person* addedLera = add(&table, "Lera");
    // Проверка добавления и вывод информации о добавленном человеке
    *addedLera = Person {"Lera", 10, Gender::Girl};

    if (find(&table, "Lera") != nullptr)
    {
        std::cout << "Added person: ";
        printPerson(addedLera);
    }

    // Добавляем "Catea"
    Person* addedCatea = add(&table, "Catea");
    *addedCatea = Person {"Catea", 8, Gender::Girl};

     if (find(&table, "Catea") != nullptr)
    {
        std::cout << "Added person: ";
        printPerson(addedCatea);
    }

    // Добавляем "Anton"
    Person* addedAnton = add(&table, "Anton");
    *addedAnton = Person {"Anton", 12, Gender::Boy};

     if (find(&table, "Anton") != nullptr)
    {
        std::cout << "Added person: ";
        printPerson(addedAnton);
    }

    Person* notFound = find(&table, "Somebody");
    if (notFound != nullptr)
    {
        printPerson(notFound);
    }
    else 
    {
        std::cout << "\nPerson with key \"Somebody\" isn't found" << std::endl;
    }

    // Удаление Кати из таблицы
    remove(&table, "Catea");

    Person* removedPerson = find(&table, "Catea");
    if (removedPerson != nullptr)
    {
        printPerson(removedPerson);
    }
    else 
    {
        std::cout << "\nAfter removing, person with key \"Catea\" isn't found" << std::endl;
    }

    // Освобождение памяти
    free(&table);

    return 0;
}