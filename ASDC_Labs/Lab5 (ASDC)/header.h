#pragma once // Один раз при кампиляции подключаем 

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





