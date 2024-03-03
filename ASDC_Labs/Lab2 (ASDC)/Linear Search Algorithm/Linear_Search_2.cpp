// Более наглядное применение алгоритма линейного поиска на примере задачи

/*Представим, что есть электронные адресные книги с информацией о контактах. 
Каждый контакт представлен в виде структуры с именем и номером телефона. 
Необходимо реализовать программу, которая использует алгоритм линейного поиска для нахождения контакта по имени.*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

struct Contact {
    std::string name;
    std::string phoneNumber;
};

// Линейный поиск контакта по имени
int linearSearchContact(const std::vector<Contact>& addressBook, const std::string& name) {
    for (int i = 0; i < addressBook.size(); ++i) {
        if (addressBook[i].name == name) {
            return i;  // Возвращаю индекс контакта, если найден
        }
    }
    return -1; // Возвращаем -1, если контакт не найден
}

int main() {
    std::vector<Contact> addressBook = {
        {"Lera", "123-456-7890"},
        {"Mark", "234-567-8901"},
        {"Andrei", "345-678-9012"},
        {"Catea", "456-789-0123"}
    };

    std::string searchName;
    std::cout << "Enter contact's name: "; 
    std::cin >> searchName;
    std:: cout << std::endl;

    int result = linearSearchContact(addressBook, searchName);

    if (result != -1) {
        std::cout << "Contact " << searchName << " was found. His number is " << addressBook[result].phoneNumber << std::endl;
    } else {
        std::cout << "Contact " << searchName << " wasn't found." << std::endl;
    }

    std:: cout << std::endl;

    // Измерения времени линейного поиска 
    auto start = std::chrono::high_resolution_clock::now();
    int resultAbsent = linearSearchContact(addressBook, "NonExistentName");
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Linear Search Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
