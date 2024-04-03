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

// Структура для ячейки в хэш-таблице
struct Bucket
{
    bool occupied;
    std::string_view key;
    Person value;
};

// Структура для хэш-таблицы
struct HashTable
{
    std::span<Bucket> buckets; // Диапазон ячеек таблицы
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
    const size_t startIndex = index;
    while (true)
    {
        Bucket* bucket = &table->buckets[index];
        if (!bucket->occupied)
        {
            return nullptr;
        }
        if (bucket->key == key)
        {
            return &bucket->value;
        }

        index++;

        // Остаемся в рамках размера массива 
        index = index % table->buckets.size();

        // Весь массив пройден, нет свободных бакетов 
        if (index == startIndex)
        {
            return nullptr;
        }
    }
}

// Функция добавления элемента
Person* add(HashTable* table, const Person& person, std::string_view key)
{
    size_t index = computeIndex(table, key);
    const size_t startIndex = index;
    while (true)
    {
        Bucket* bucket = &table->buckets[index];
        if (!bucket->occupied)
        {
            bucket->occupied = true;
            bucket->key = key;
            bucket->value = person;
            return &bucket->value;
        }

        index++;
        
        // Остаемся в рамках размера массива
        index = index % table->buckets.size();

        // Весь массив пройден, нет свободных бакетов 
        if (index == startIndex)
        {
            return nullptr;
        }
    }
}

// Функция удаления элемента по ключу
void remove(HashTable* table, std::string_view key)
{
    size_t index = computeIndex(table, key);
    const size_t startIndex = index;
    while (true)
    {
        Bucket* bucket = &table->buckets[index];
        if (bucket->occupied && bucket->key == key)
        {
            bucket->occupied = false;
            return;
        }

        index++;
        // Wrap around the edge.
        index = index % table->buckets.size();

        // Traversed the whole array, didn't find the bucket.
        if (index == startIndex)
        {
            return;
        }
    }
}

// Функция освобождения памяти (не требуется для встроенного списка)
void freeHashTable(HashTable* table)
{
    // Не требуется освобождение памяти, так как используется встроенный список
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

// Функция вывода информации о человеке
void printPerson(const Person* person)
{
    std::cout << "Name: " << person->name.data() << ", Form: " << person->form
              << ", Gender: " << (person->gender == Gender::Boy ? "Boy" : "Girl") << std::endl;
}

int main()
{
    // Создаем хэш-таблицы с функцией хэширования
    std::array<Bucket, 10> buckets; // Массив ячеек таблицы
    HashTable table{buckets, hashFunc};

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

    // Освобождение памяти не нужно для встроенного списка

    return 0;
}
