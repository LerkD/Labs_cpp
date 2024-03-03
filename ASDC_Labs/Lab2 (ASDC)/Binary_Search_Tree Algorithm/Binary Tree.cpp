// Операции с двоичным деревом поиска на C++

#include <iostream>

// Структура представляющая узел бинарного дерева поиска
struct node {
  int key;
  struct node *left, *right;
};

// Создание нового узла
struct node *newNode(int item) {
  struct node *temp = new struct node;
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

// Отсортированный (inorder) обход дерева
void inorder(struct node *root) {
  if (root != NULL) {
    inorder(root->left);
    std::cout << root->key << " -> ";
    inorder(root->right);
  }
}

// Вставка узла в бинарное дерево поиска
struct node *insert(struct node *node, int key) {
  // Если дерево пустое, возвращаем новый узел
  if (node == NULL)
    return newNode(key);

  // В противном случае рекурсивно идем в нужное поддерево
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Поиск узла с минимальным ключом (inorder-преемник)
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Ищем самый левый лист
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Удаление узла с заданным ключом из дерева
struct node *deleteNode(struct node *root, int key) {
  // Возвращаем NULL, если дерево пустое
  if (root == NULL)
    return root;

  // Ищем узел, который нужно удалить
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    // Если у узла один дочерний элемент или его нет
    if (root->left == NULL) {
      struct node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      delete root;
      return temp;
    }

    // Если у узла два дочерних элемента
    struct node *temp = minValueNode(root->right);

    // Помещаем inorder-преемника на место узла, который хотим удалить
    root->key = temp->key;

    // Удаляем inorder-преемника
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// Поиск узла с заданным ключом
struct node *searchNode(struct node *root, int key) {
  // Возвращаем узел, если найден, иначе NULL
  if (root == NULL || root->key == key)
    return root;

  // Рекурсивно идем в нужное поддерево
  if (key < root->key)
    return searchNode(root->left, key);

  return searchNode(root->right, key);
}

// Нахождение высоты бинарного дерева
int treeHeight(struct node *root) {
  if (root == NULL)
    return 0;

  int leftHeight = treeHeight(root->left);
  int rightHeight = treeHeight(root->right);

  return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Печать узлов на конкретном уровне
void printLevels(struct node *root, int level) {
  if (root == NULL)
    return;

  if (level == 1)
    std::cout << root->key << " ";
  else if (level > 1) {
    printLevels(root->left, level - 1);
    printLevels(root->right, level - 1);
  }
}

// Печать дерева по уровням
void printTree(struct node *root) {
  int height = treeHeight(root);
  for (int i = 1; i <= height; ++i) {
    std::cout << "Уровень " << i << ": ";
    printLevels(root, i);
    std::cout << std::endl;
  }
}

// Тестирование функций
int main() {
  // Создаем корень и добавляем узлы
  struct node *root = NULL;
  root = insert(root, 9);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 5);
  root = insert(root, 7);
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 6);

  // Выводим отсортированный обход
  std::cout << "Отсортированный обход: " << std::endl;
  inorder(root);
  std::cout << std::endl;
  
  // Удаляем узел с ключом 10
  
  std::cout << std::endl;
  std::cout <<"После удаления 10" << std::endl;
  root = deleteNode(root, 10);
  
  // Выводим отсортированный обход после удаления
  std::cout << "Отсортированный обход: "<< std::endl;
  inorder(root);
  std::cout << std::endl;
  std::cout << std::endl;

  // Поиск узла с ключом 5
  int searchKey = 5;
  struct node *searchResult = searchNode(root, searchKey);

  if (searchResult != NULL)
    std::cout << "Узел с ключом " << searchKey << " найден." << std::endl;
  else
    std::cout << "Узел с ключом " << searchKey << " не найден." << std::endl;

  std::cout << std::endl;


  // Выводим высоту дерева
  std::cout << "Высота дерева: " << treeHeight(root) << std::endl;
  std::cout << std::endl;

  // Печать дерева по уровням
  std::cout << "Печать дерева по уровням:" << std::endl;
  printTree(root);
  std::cout << std::endl;

  // Освобождение памяти
  delete root;

  return 0;
}