#include <iostream>
#include <vector>
#include <queue>
#include <set>

// Задание 1: Определяю структуры нода графа
struct GraphNode {
    int value;
    std::vector<GraphNode*> neighbors; // Не использую буфер. Мне кажется, лучше просто стандартный вектор указателей на соседние узлы

    GraphNode(int val) : value(val) {}
};

// Задание 4: Функция, которая считает сумму значений соседних нодов заданного нода
int sumOfNeighborsValues(GraphNode* node) {
    int sum = 0;
    for (GraphNode* neighbor : node->neighbors) {
        sum += neighbor->value;
    }
    return sum;

}

// То же задание 4, выпод результата вынесу в отдельную функцию
void printSumOfNeighbors(GraphNode* node) {
    std::cout << "Sum of neighbors for node " << node->value << ": " << sumOfNeighborsValues(node) << std::endl;
}


// Задание 5: Алгоритм DFS - поиск в глубину
void dfs(GraphNode* start, std::set<GraphNode*>& already_checked) {
    if (!start /*!start: Проверяет, существует ли узел.*/ || already_checked.count(start) > 0 /*Проверяет, был ли узел уже посещен. Если узе*/) { 
        return;
    }

    std::cout << start->value << " ";
    already_checked.insert(start);

    for (GraphNode* neighbor : start->neighbors) {
        dfs(neighbor, already_checked);
    }
}

// Задание 5: Алгоритм BFS - поиск в ширину 
void bfs(GraphNode* start) {
    if (!start) {
        return;
    }

    std::queue<GraphNode*> q; //Обьявляю очередь для обхода узлов в порядке FIFO.
    std::set<GraphNode*> already_checked; // Множество уже посещенных узлов

    q.push(start);
    already_checked.insert(start);

    while (!q.empty()) {
        GraphNode* current = q.front();
        q.pop();

        std::cout << current->value << " ";

        for (GraphNode* neighbor : current->neighbors) {
            if (already_checked.count(neighbor) == 0) {
                q.push(neighbor);
                already_checked.insert(neighbor);
            }
        }
    }
}

// Также добавила отдельную функцию для очистки памяти 
void deleteGraph(std::vector<GraphNode*>&& nodes) {
    for (GraphNode* node : nodes) {
        delete node;
    }
}

int main() {
    // Задание 2: Создание графа
    GraphNode* A = new GraphNode(1);
    GraphNode* B = new GraphNode(2);
    GraphNode* C = new GraphNode(3);
    GraphNode* D = new GraphNode(4);

    // Конфигурация первого графа из тех двух, которые были даны в задании

    A->neighbors.push_back(B);
    A->neighbors.push_back(C);
    A->neighbors.push_back(D);
    B->neighbors.push_back(C);
    C->neighbors.push_back(D);
    D->neighbors.push_back(A);


    // Задание 4: Печать суммы значений соседних нодов заданного нода
    printSumOfNeighbors(A);
    printSumOfNeighbors(B);
    printSumOfNeighbors(C);
    printSumOfNeighbors(D);

    // Задание 5: Печать результатов DFS и BFS
    std::set<GraphNode*> already_checked;

    std::cout << "\nDFS traversal: ";
    dfs(A, already_checked);
    std::cout << std::endl;
    

    // Сбрасываем посещенные узлы для BFS
    already_checked.clear();

    std::cout << "\nBFS traversal: ";
    bfs(A);
    std::cout << std::endl;

    // Очистка памяти
    deleteGraph({A, B, C, D});

    return 0;
}
