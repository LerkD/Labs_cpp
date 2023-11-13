#include <iostream>
#include <fstream>
#include <vector>

// Перечисление для пола
enum class Gender
{
    Boy,
    Girl
};

// Отдельный enum для ошибок сериализации
enum class SerializationError
{
    Success,
    CommaInStringField
};

// Отдельный enum для ошибок чтения и записи из файла
enum class ErrorCode
{
    Success,
    FileOpenError,
    FileReadError,
    FileWriteError,
    SerializationError,
    DeserializationError
};

// Класс Person с конструкторами и методами сериализации/десериализации
class Person
{
public:
    // Конструкторы
    Person() = default; // Дефолтный конструктор
    Person(const std::string& name, int form, Gender gender);
    Person(const Person& other); // Конструктор копирования
    Person(Person&& other) noexcept; // Конструктор перемещения
    ~Person() = default; // Деструктор

    // Оператор присваивания
    Person& operator=(const Person& other);

    // Методы сериализации/десериализации
    SerializationError serialize(std::ostream& stream) const;
    static Person deserialize(const std::string& line);

    // friend операторы для операций ввода/вывода (нам почему-то говорили иъ не использовать)
    friend std::ostream& operator<<(std::ostream& stream, const Person& person);
    friend std::istream& operator>>(std::istream& stream, Person& person);

private:
    std::string name;
    int form;
    Gender gender;
};

// Реализация методов класса Person
Person::Person(const std::string& name, int form, Gender gender)
    : name(name), form(form), gender(gender) {}

Person::Person(const Person& other)
    : name(other.name), form(other.form), gender(other.gender) {}

Person::Person(Person&& other) noexcept
    : name(std::move(other.name)), form(other.form), gender(other.gender) {}

Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        name = other.name;
        form = other.form;
        gender = other.gender;
    }
    return *this;
}

SerializationError Person::serialize(std::ostream& stream) const
{
    if (name.find(',') != std::string::npos)
    {
        std::cout << "Ошибка сериализации строки: строковое поле содержит запятую." << std::endl;
        return SerializationError::CommaInStringField;
    }

    stream << name << ',' << form << ',';

    switch (gender)
    {
    case Gender::Boy:
        stream << "B,";
        break;
    case Gender::Girl:
        stream << "G,";
        break;
    }

    return SerializationError::Success;
}

Person Person::deserialize(const std::string& line)
{
    size_t pos = 0;

    size_t commaPos = line.find(',', pos);
    std::string nameStr = line.substr(pos, commaPos - pos);

    pos = commaPos + 1;
    commaPos = line.find(',', pos);
    int form = std::stoi(line.substr(pos, commaPos - pos));

    pos = commaPos + 1;
    Gender gender;
    if (line.substr(pos, 1) == "B")
        gender = Gender::Boy;
    else
        gender = Gender::Girl;

    return Person(nameStr, form, gender);
}

std::ostream& operator<<(std::ostream& stream, const Person& person)
{
    person.serialize(stream);
    return stream;
}

std::istream& operator>>(std::istream& stream, Person& person)
{
    // Ввод в формате "name,form,gender,"
    std::string line;
    std::getline(stream, line);
    person = Person::deserialize(line);
    return stream;
}

// Функция для дополнительных проверок на ошибки при чтении файла
ErrorCode checkFileRead(std::ifstream& file)
{
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла для чтения." << std::endl;
        return ErrorCode::FileOpenError;
    }

    if (file.fail())
    {
        std::cout << "Ошибка чтения файла." << std::endl;
        return ErrorCode::FileReadError;
    }

    return ErrorCode::Success;
}

// Функция для дополнительных проверок на ошибки при записи файла
ErrorCode checkFileWrite(std::ofstream& file)
{
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла для записи." << std::endl;
        return ErrorCode::FileOpenError;
    }

    if (file.fail())
    {
        std::cout << "Ошибка записи в файл." << std::endl;
        return ErrorCode::FileWriteError;
    }

    return ErrorCode::Success;
}

// Функция для десериализации vector объектов Person
std::vector<Person> deserializePeople(std::istream& stream)
{
    std::vector<Person> people;
    Person person;

    while (stream >> person)
    {
        people.push_back(person);
    }

    return people;
}

// Функция для сериализации vector объектов Person
void serializePeople(const std::vector<Person>& people, std::ostream& stream)
{
    for (const auto& person : people)
    {
        stream << person;
        stream << '\n';
    }
}

Person generateRandomPerson()
{
    // Генерация случайного имени
    const char* charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string name;
    for (int i = 0; i < 20; ++i)
    {
        name += charset[rand() % (sizeof(charset) - 1)];
    }

    // Генерация случайного класса (1-12)
    int form = rand() % 12 + 1;

    // Генерация случайного пола
    Gender gender = static_cast<Gender>(rand() % 2);

    return Person(name, form, gender);
}

int main()
{
    // Создание файла с сериализованными объектами
    std::ofstream outFile("data.csv");
    ErrorCode writeError = checkFileWrite(outFile);
    if (writeError != ErrorCode::Success)
    {
        return static_cast<int>(writeError);
    }

    // Генерация случайных данных и запись в файл
    for (int i = 0; i < 5; ++i)
    {
        Person randomPerson = generateRandomPerson();
        outFile << randomPerson<<std::endl;
       
    }

    outFile.close();

    std::cout << "Рандомные данные сгенерировались и внесены в data.csv." << std::endl;

    Person person1("Lera", 10, Gender::Girl);
    Person person2("Vasea", 12, Gender::Boy);

    // Сериализация объектов и запись в файл
    serializePeople({ person1, person2 }, outFile);

    outFile.close();

    // Чтение из файла, модификация и запись обратно
    std::ifstream inFile("data.csv");
    ErrorCode readError = checkFileRead(inFile);
    if (readError != ErrorCode::Success)
    {
        return static_cast<int>(readError);
    }

    auto people = deserializePeople(inFile);

    // Модификация данных
    if (!people.empty())
    {
        people[0] = Person("NewName", 1, Gender::Boy);
        Person newPerson = generateRandomPerson();
        people.push_back(newPerson);
    }

    inFile.close();

    // Запись обновленных данных в файл
    std::ofstream newData("newData.csv");
    ErrorCode updateError = checkFileWrite(newData);
    if (updateError != ErrorCode::Success)
    {
        return static_cast<int>(updateError);
    }

    serializePeople(people, newData);

    newData.close();

    return 0;
}

/*Вот, что получилось 
Имя(Рандомные буквы)  Класс Пол
GBGFDCFAFGAFGGABGAEE	4	B
DGFGFFGBBFBCAEFAEDDE	3	G
FCAEBBEBAEDABEFBDEAB	1	B
DDADGFACDGFAFGBCEEDD	11	B
BCEBAEAGEDEADAFGDEFD	6	B
*/