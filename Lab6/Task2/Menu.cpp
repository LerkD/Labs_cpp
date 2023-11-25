#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <stdexcept>

// Объявление EventHandle
struct EventHandle {
    size_t id;
};

// Структура EventInfo
template<typename Payload>
struct EventInfo {
    Payload payload;
    // ... some more generic info
};

// Структура EventHandler
template<typename Payload>
struct EventHandler {
    size_t id;
    std::function<void(EventInfo<Payload>*)> func;
};

// Определяем тип функции обработчика (воспользовался using std::function, как у вас в примере)
template<typename Payload>
using EventHandlerFunc = std::function<void(EventInfo<Payload>*)>;

// Структура EventSystem
template<typename Payload>
class EventSystem {
private:
    std::unordered_map<size_t, std::vector<EventHandler<Payload>>> eventHandlers;
    size_t nextHandleId = 0;

public:
    EventHandle createEvent() {
        EventHandle handle;
        handle.id = nextHandleId++;
        eventHandlers[handle.id] = std::vector<EventHandler<Payload>>();
        return handle;
    }

    size_t subscribe(EventHandle eventId, EventHandlerFunc<Payload>&& func) {
        
        auto& handlers = eventHandlers[eventId.id];
        handlers.push_back({nextHandleId++, std::move(func)});
        return nextHandleId - 1;
    }

    bool unsubscribe(EventHandle eventId, size_t handleId) {
        auto it = eventHandlers.find(eventId.id);
        if (it != eventHandlers.end()) {
            auto& handlers = it->second;
            auto handler = std::find_if(handlers.begin(), handlers.end(),
                [handleId](const EventHandler<Payload>& h) { return h.id == handleId; });
            if (handler != handlers.end()) {
                handlers.erase(handler);
                return true;
            }
        }
        return false;
    }

    void dispatch(EventHandle eventId, EventInfo<Payload>* event) {
        auto& handlers = eventHandlers[eventId.id];
        for (auto& handler : handlers) {
            handler.func(event);
        }
    }

    // Отдельный метод для печати идентификаторов всех событий и обработчиков
    void printEventHandlers() const {
        for (const auto& pair : eventHandlers) {
            std::cout << "Событие ID: " << pair.first << std::endl;
            for (const auto& handler : pair.second) {
                std::cout << "  Обработчик ID: " << handler.id << std::endl;
            }
        }
    }
};


int main() {
    setlocale(LC_ALL, "Russian");
    EventSystem<int> eventSystemInt;
    EventSystem<std::string> eventSystemString;

    int choice;
    bool running = true;

    while (running) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Создать новое событие" << std::endl;
        std::cout << "2. Подписать обработчик на событие" << std::endl;
        std::cout << "3. Отписать обработчик от события" << std::endl;
        std::cout << "4. Вывести все события и обработчики" << std::endl;
        std::cout << "5. Вызвать событие" << std::endl;
        std::cout << "6. Выход" << std::endl;

        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Создание нового события
                EventHandle newEvent = eventSystemInt.createEvent();
                std::cout << "Создано новое событие с ID: " << newEvent.id << std::endl;
                break;
            }
            case 2: {
                // Подписка обработчика на событие
                std::cout << "Введите ID события для подписки:" << std::endl;
                size_t eventId;
                std::cin >> eventId;

                std::cout << "Выберите функцию обработчика:" << std::endl;
                std::cout << "1. Добавить 10" << std::endl;
                std::cout << "2. Добавить 20" << std::endl;
                std::cout << "3. Умножить на 2" << std::endl;
                std::cout << "4. Умножить на 3" << std::endl;
                std::cout << "5. Возвести в квадрат" << std::endl;
                std::cout << "6. Возвести в куб" << std::endl;

                int handlerChoice;
                std::cin >> handlerChoice;

                EventHandlerFunc<int> eventHandler;
                switch (handlerChoice) {
                    case 1: {
                        eventHandler = [](EventInfo<int>* event) {
                            event->payload += 10;
                            std::cout << "Обработано. Результат: " << event->payload << std::endl;
                        };
                        break;
                    }
                    case 2: {
                        eventHandler = [](EventInfo<int>* event) {
                            event->payload += 20;
                            std::cout << "Обработано. Результат: " << event->payload << std::endl;
                        };
                        break;
                    }
                    case 3: {
                        eventHandler = [](EventInfo<int>* event) {
                            event->payload *= 2;
                            std::cout << "Обработано. Результат: " << event->payload << std::endl;
                        };
                        break;
                    }
                    case 4: {
                        eventHandler = [](EventInfo<int>* event) {
                            event->payload *= 3;
                            std::cout << "Обработано. Результат: " << event->payload << std::endl;
                        };
                        break;
                    }
                    case 5: {
                        eventHandler = [](EventInfo<int>* event) {
                            event->payload *= event->payload;
                            std::cout << "Обработано. Результат: " << event->payload << std::endl;
                        };
                        break;
                    }
                    case 6: {
                        eventHandler = [](EventInfo<int>* event) {
                            event->payload *= event->payload * event->payload;
                            std::cout << "Обработано. Результат: " << event->payload << std::endl;
                        };
                        break;
                    }
                    default: {
                        std::cout << "Некорректный ввод!" << std::endl;
                        break;
                    }
                }

                size_t handlerId = eventSystemInt.subscribe(EventHandle{eventId}, std::move(eventHandler));
                std::cout << "Обработчик подписан с ID: " << handlerId << std::endl;

                break;
            }
            case 3: {
                // Отписка обработчика от события
                std::cout << "Введите ID события для отписки:" << std::endl;
                size_t unsubscribeEventId;
                std::cin >> unsubscribeEventId;

                std::cout << "Введите ID обработчика для отписки:" << std::endl;
                size_t unsubscribeHandlerId;
                std::cin >> unsubscribeHandlerId;

                bool result = eventSystemInt.unsubscribe(EventHandle{unsubscribeEventId}, unsubscribeHandlerId);
                if (result) {
                    std::cout << "Обработчик отписан успешно." << std::endl;
                } else {
                    std::cout << "Обработчик не найден." << std::endl;
                }
                break;
            }

            case 4: {
                // Вывод всех идентификаторов событий и их обработчиков
                std::cout << "ID всех событий и их обработчиков:" << std::endl;
                eventSystemInt.printEventHandlers();
                break;
            }

            case 5: {
                std::cout << "Введите ID события для вызова:" << std::endl;
                size_t eventId;
                std::cin >> eventId;

                // Создаем данные для обработчиков (число)
                int eventDataValue;
                std::cout << "Введите данные для обработчиков:" << std::endl;
                std::cin >> eventDataValue;

                // Передаю данные в EventInfo
                EventInfo<int> eventData{ eventDataValue };

                // Вызываю событие, передав его ID и данные для обработчиков
                eventSystemInt.dispatch(EventHandle{ eventId }, &eventData);
                break;
            }

            case 6: {
                running = false;
                break;
            }
            default: {
                std::cout << "Некорректный ввод!" << std::endl;
                break;
            }
        }
    }

    return 0;
}
