#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>


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

// Определяем типа функции обработчика (воспользовалась using std::function, как у вас в примере)
template<typename Payload>
using EventHandlerFunc = std::function<void(EventInfo<Payload>*)>;

// Структура EventSystem
template<typename Payload>
class EventSystem {
private:
    std::unordered_map<size_t, std::vector<EventHandler<Payload>>> eventHandlers; // Тут мы используем ключ-значение, правильно?
    size_t nextHandleId = 0; // Следующий идентификатор обработчика

public:
    // Создаем новое событие, получем идентификатор 
    EventHandle createEvent() {
        EventHandle handle;
        handle.id = nextHandleId++;

        // Пустой вектор для нового события
        eventHandlers[handle.id] = std::vector<EventHandler<Payload>>();

        return handle;
    }

    // Функуия, чтобы подписываться 
    size_t subscribe(EventHandle eventId, EventHandlerFunc<Payload>&& func) {
        if (eventHandlers.find(eventId.id) == eventHandlers.end()) {
            throw std::invalid_argument("Event with given ID does not exist.");
        }

        auto& handlers = eventHandlers[eventId.id];
        handlers.push_back({nextHandleId++, std::move(func)});
        
        return nextHandleId - 1;
    }

    // Функция для отписки 
    bool unsubscribe(EventHandle eventId, size_t handleId) {
        auto it = eventHandlers.find(eventId.id);
        if (it != eventHandlers.end()) {
            auto& handlers = it->second;

            auto handler = std::find_if(handlers.begin(), handlers.end(),
                [handleId](const EventHandler<Payload>& h) { return h.id == handleId; });

            if (handler != handlers.end()) {
                handlers.erase(handler);
                return true; // Нашли и удалили обработчик
            }
        }
        return false; // Обработчик не найден
    }

    // Функция для вызова обработчиков события
    void dispatch(EventHandle eventId, EventInfo<Payload>* event) {
        auto& handlers = eventHandlers[eventId.id];

        for (auto& handler : handlers) {
            handler.func(event);
        }
    }
};

int main() { // В мэйне создаю два события с разными типами payload, подписываюсь на них, вызываю, обрабатываю, чтобы проверить правильность.
   
    // Создаем две системы событий
    EventSystem<int> eventSystemInt;
    EventSystem<std::string> eventSystemString;

    // Создаем событий с различными payload
    EventHandle eventInt = eventSystemInt.createEvent();
    EventHandle eventString = eventSystemString.createEvent();

    // Подписываемся на каждое из событий с разными обработчиками
    size_t handlerIdInt = eventSystemInt.subscribe(eventInt, [](EventInfo<int>* event) {
        std::cout << "Event received with int payload: " << event->payload << std::endl;
    });

    size_t handlerIdString = eventSystemString.subscribe(eventString, [](EventInfo<std::string>* event) {
        std::cout << "Event received with string payload: " << event->payload << std::endl;
    });

    // Добавляем данные для событий 
    EventInfo<int> eventDataInt{ 10 };
    EventInfo<std::string> eventDataString{ "Hello, world!" };

    // Вызываем событий
    eventSystemInt.dispatch(eventInt, &eventDataInt);
    eventSystemString.dispatch(eventString, &eventDataString);

    // Отписываемся от обработчиков (насколько я поняла, это не обязательно)
    eventSystemInt.unsubscribe(eventInt, handlerIdInt);
    eventSystemString.unsubscribe(eventString, handlerIdString);

    return 0;
}

/* Программа выводит, как и ожидалось: Event received with int payload: 10
Event received with string payload: Hello, world!*/