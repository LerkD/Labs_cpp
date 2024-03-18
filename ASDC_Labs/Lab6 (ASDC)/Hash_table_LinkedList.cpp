#include <iostream>
#include <string_view>
#include <array>
#include <span>

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
    std::array<BucketNode*, 10> buckets; // Фиксированный размер массива бакетов
    size_t (*hashFunc)(std::string_view); // Указатель на функцию хэширования
};

// Функция вычисления индекса для ключа
size_t computeIndex(HashTable* table, std::string_view key)
{
    size_t hash = table->hashFunc(key);
    size_t index = hash % table->buckets.size();
    return index;
}

// Функция поиска значения по ключу
Person* find(HashTable* table, std::string_view key)
{
    size_t index = computeIndex(table, key);
    BucketNode* currentNode = table->buckets[index];
    while (currentNode != nullptr)
    {
        if (currentNode->key == key)
        {
            return &currentNode->value;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

// Функция добавления элемента
Person* add(HashTable* table, const Person& person, std::string_view key)
{
    size_t index = computeIndex(table, key);
    BucketNode* newNode = new BucketNode{person, key, nullptr}; // Создаем новый нод
    newNode->next = table->buckets[index]; // Добавляем его в начало соответствующего bucket
    table->buckets[index] = newNode;
    return &(newNode->value); // Возвращаем адрес значения из нового узла
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
            if (prevNode) {
                prevNode->next = currentNode->next;
            } else {
                table->buckets[index] = currentNode->next;
            }
            delete currentNode;
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

// Функция освобождения памяти
void free(HashTable* table)
{
    for (size_t i = 0; i < table->buckets.size(); ++i)
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

// Функция хэширования: суммирует коды по таблице АСХИ символов ключа
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
    // Создаем хэш таблицы с функцией хэширования
    HashTable table = createHashTable(10, hashFunc);

    // Добавление элемента "Lera"
    Person* addedLera = add(&table, {"Lera", 10, Gender::Girl}, "Lera");
    // Проверка добавления и вывод информации о добавленном человеке
    if (addedLera != nullptr)
    {
        std::cout << "Added person: ";
        printPerson(addedLera);
    }

    // Добавляем "Catea"
    Person* addedCatea = add(&table, {"Catea", 8, Gender::Girl}, "Catea");
    if (addedCatea != nullptr)
    {
        std::cout << "Added person: ";
        printPerson(addedCatea);
    }

    // Добавляем "Anton"
    Person* addedAnton = add(&table, {"Anton", 12, Gender::Boy}, "Anton");
    if (addedAnton != nullptr)
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