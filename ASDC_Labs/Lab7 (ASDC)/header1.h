#include <iostream>
#include <string>
#include <array>
#include <span>
#include <chrono>
#include <random>

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


// Функция вывода массива Person
void printPeople(const std::span<Person>& arr)
{
    for (const auto& person : arr)
    {
        std::cout << "Name: " << person.name.data() << ", Form: " << person.form
                  << ", Gender: " << (person.gender == Gender::Boy ? "Boy" : "Girl") << std::endl;
    }
}

// Генерируем рандомных людей 
Person generateRandomPerson(std::mt19937& rng, int index)
{
    // Генерация случайного имени
    std::string name = "Persons" + std::to_string(index);
    std::array<char, 20> nameArray;
    std::copy(name.begin(), name.end(), nameArray.begin());

    // Генерация случайного класса от 1 до 1000 (да, у меня в программe дети ходят в школу 1000 лет :) )
    int form = static_cast<int>(std::uniform_int_distribution<int>(1, 1000)(rng));

    // Генерация случайного пола
    Gender gender = std::uniform_int_distribution<int>(0, 1)(rng) == 0 ? Gender::Boy : Gender::Girl;

    return Person{nameArray, form, gender};
}


void runSortAlgorithm(std::span<Person> people_span);

void runExample()
{
    
    std::random_device rd;
    std::mt19937 rng(rd()); // Использую текущее время в качестве начального значения


    std::array<Person, 5> people = {
        {{"Lera", 12, Gender::Girl},
         {"Anton", 9, Gender::Boy},
         {"Dima", 7, Gender::Boy},
         {"Catea", 8, Gender::Girl},
         {"Asea", 3, Gender::Girl}}};

    runSortAlgorithm(people);

    std::cout << "------------\n" << std::endl;

    // Другая конфигурация 
    std::array<Person, 5> people2 = {
        {{"Anton", 9, Gender::Boy},
         {"Lera", 12, Gender::Girl},
         {"Catea", 8, Gender::Girl},
         {"Asea", 3, Gender::Girl},
         {"Dima", 7, Gender::Boy}}};

    runSortAlgorithm(people2);

    std::cout << "------------\n" << std::endl;

    // Другая конфигурация 
    std::array<Person, 5> people3 = {
        {{"Asea", 3, Gender::Girl},
         {"Anton", 9, Gender::Boy},
         {"Dima", 7, Gender::Boy},
         {"Catea", 8, Gender::Girl},
         {"Lera", 12, Gender::Girl}}};

    runSortAlgorithm(people3);

    std::cout << "------------\n" << std::endl;
    std::cout << "Different size: \n" << std::endl;

    std::array<Person, 1000> people_random;

    for (int i = 0; i < 1000; ++i)
    {
        people_random[i] = generateRandomPerson(rng, i);
    }

    std::cout << "Running sort algorithms for array of size 1000:\n" << std::endl;
    runSortAlgorithm(people_random);
    std::cout << "------------\n" << std::endl;
}
