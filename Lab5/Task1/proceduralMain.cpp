#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <span>

// Перечисление для пола
enum class Gender
{
    Boy,
    Girl
};

// Отдельный enum для ошибок
enum class ErrorCode
{
    Success,
    FileOpenError,
    FileReadError,
    FileWriteError,
    SerializationError,
    DeserializationError
};


// Структура данных
struct Person
{
    std::array<char, 20 > name; // Строковое поле- - имя ученика
    int form;                   // Целочисленное поле - класс, в котором находится ученик
    Gender gender;             // Пол - гендер ученика 
};

// Функция сериализации строки
void serializeString(const std::string& str, std::ostream& stream)
{
    stream << str << ','; // Записываем строку с последующей запятой
}

// Функция сериализации целого числа
void serializeInt(int value, std::ostream& stream)
{
    stream << value << ','; // Записываем целое число с последующей запятой
}

// Функция сериализации enum Gender
void serializeGender(Gender gender, std::ostream& stream)
{
    switch (gender)
    {
    case Gender::Boy:
        stream << "B,"; // Записываем "B" для Boy с последующей запятой
        break;
    case Gender::Girl:
        stream << "G,"; // Записываем "G" для Girl с последующей запятой
        break;
    }
}

// Новая структура DeserializationResult для пункта 5
struct DeserializationResult
{
    bool success;
    Person value;
};

// Новый класс для десериализации Person
class PersonDeserializer
{
public:
    std::optional<Person> deserialize(const std::string& line) const // использую optional, т.к. мне кажется, что вместо того чтобы возвращать объект структуры с флагом успешности и значением, 
    // std::optional будет здесь более уместным.
    {
        Person person;
        size_t pos = 0;

        // Десериализация имени ученика
        size_t commaPos = line.find(',', pos);
        if (commaPos == std::string::npos)
            return std::nullopt;
        std::string nameStr = line.substr(pos, commaPos - pos);
        std::copy(nameStr.begin(), nameStr.end(), person.name.begin());
        person.name[nameStr.size()] = '\0'; // Установка нулевого символа в конце строки
        pos = commaPos + 1;

        // Десериализация класса
        commaPos = line.find(',', pos);
        if (commaPos == std::string::npos)
            return std::nullopt;
        person.form = deserializeInt(line.substr(pos, commaPos - pos).c_str());
        pos = commaPos + 1;

        // Десериализация пола
        person.gender = deserializeGender(line.substr(pos).c_str());

        return person;
    }
};

// Функция сериализации объекта Person
void serializePerson(const Person& person, std::ostream& stream)
{
    serializeString(std::string(person.name.data()), stream); // Сериализация строки
    serializeInt(person.form, stream);                          // Сериализация целого числа
    serializeGender(person.gender, stream);                    // Сериализация enum Gender
    stream << '\n';                                           // Переход на новую строку после сериализации одного объекта
}

// Функция десериализации строки
std::string deserializeString(const char* buffer)
{
    return std::string(buffer); // Вроде так правильно будет преобразовать в стринг
}

// Функция десериализации целого числа
int deserializeInt(const char* buffer)
{
    return std::stoi(buffer); // То же самое с целым числом
}

// Функция десериализации enum Gender
Gender deserializeGender(const char* buffer)
{
    if (buffer[0] == 'B')
        return Gender::Boy;   // Значения enum Gender для "B"
    else
        return Gender::Girl; // Значения enum Gender для "G"
}



template <typename Span>
void serializePeople(const Span& people, std::ostream& stream)
{
    for (const auto& person : people)
    {
        serializePerson(person, stream); // Сериализация каждого объекта Person
        std::cout << endl; // Разделяю новой строчкой 
    }
         
}

// Функция для десериализации с использованием DeserializationResult
DeserializationResult deserialize(std::iostream& stream)
{
    PersonDeserializer deserializer;

    std::string line;
    std::getline(stream, line);

    std::optional<Person> deserializedPerson = deserializer.deserialize(line);

    if (deserializedPerson)
    {
        return { true, *deserializedPerson };
    }
    else
    {
        return { false, {} };
    }
}

// Функция для дополнительных проверок на ошибки при чтении файла
ErrorCode checkFileRead(std::istream& file)
{
    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла для чтения." << std::endl;
        return ErrorCode::FileOpenError;
    }

    if (file.fail())
    {
        std::cerr << "Ошибка чтения файла." << std::endl;
        return ErrorCode::FileReadError;
    }

    return ErrorCode::Success;
}

// Функция для дополнительных проверок на ошибки при записи файла
ErrorCode checkFileWrite(std::ostream& file)
{
    if (!file.is_open())
    {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
        return ErrorCode::FileOpenError;
    }

    if (file.fail())
    {
        std::cerr << "Ошибка записи в файл." << std::endl;
        return ErrorCode::FileWriteError;
    }

    return ErrorCode::Success;
}

// Функция для десериализации vector объектов Person
std::vector<Person> deserializePeople(std::iostream& /*хотя коспилятор подсказывал std::istream*/ stream)
{
    std::vector<Person> people;
    std::string line;

    // Читаем строку в потоке 
    while (std::getline(stream, line))
    {
        PersonDeserializer deserializer;
        std::optional<Person> deserializedPerson = deserializer.deserialize(line);

        // Проверяю, удалось ли десериализовать 
        if (deserializedPerson)
        {
            people.push_back(*deserializedPerson);
        }
        else
        {
            // Если десериализация не удалась, выводим сообщение об ошибке в поток ошибок
            std::cerr << "Ошибка десериализации строки: " << line << std::endl;
        }
    }

    return people; // Возврат вектора, содержащего десериализованные объекты Person
}

Person generateRandomPerson() // Лучше функцией, чем отдельной программой
{
    Person person;

    // Генерация случайного имени
    const char* charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (char& c : person.name)
    {
        c = charset[rand() % (sizeof(charset) - 1)];
    }
    person.name[19] = '\0'; // Установка нулевого символа в конце строки

    // Генерация случайного класса (1-12)
    person.form = rand() % 12 + 1;

    // Генерация случайного пола
    person.gender = static_cast<Gender>(rand() % 2);

    return person;
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
    for (int i = 0; i < 5; ++i) // Генерация 5 случайных записей
    {
        Person randomPerson = generateRandomPerson();
        serializePerson(randomPerson, outFile);
    }

    outFile.close();

    std::cout << "Рандомные данные сгенерировались и внесены ы data.csv." << std::endl;


    Person person1 = { "Lera", 10, Gender::Girl };
    Person person2 = { "Vasea", 12, Gender::Boy };

    serializePeople({ person1, person2 }, outFile); // Сериализация объектов и запись в файл

    outFile.close();

    // Чтение из файла, модификация и запись обратно
    std::ifstream inFile("data.csv");
    ErrorCode readError = checkFileRead(inFile);
    if (readError != ErrorCode::Success)
    {
        return static_cast<int>(readError);
    }

    auto people = deserializePeople(inFile); // Десериализация данных из файла

    // Модификация данных
    if (!people.empty())
    {
        people[0].form = 1; // Изменение класса первого ученика
        Person newPerson = { "Petea", 5, Gender::Boy };
        people.push_back(newPerson); // Добавление нового ученика
    }

    inFile.close();

    // Запись обновленных данных в файл
    std::ofstream newData("newData.csv");
    ErrorCode updateError = checkFileWrite(newData);
    if (updateError != ErrorCode::Success)
    {
        return static_cast<int>(updateError);
    }

    serializePeople(people, newData); // Сериализация обновленных данных и запись в новый файл

    newData.close();

    return 0;
}

