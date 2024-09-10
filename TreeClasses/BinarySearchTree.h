#pragma once
//Сделал: Ошлаков Данил, ИВТ-22
#include <sstream>
#include <iostream>
#include <cassert>
#include <functional>
#include <vector>
#include <stack>

using namespace std;
// Класс Node представляет собой узел двусвязного списка.
template<typename T>
class TreeNode {
public:
    // Данные, хранящиеся в узле.
    T n_data;

    // Указатель на предыдущий узел в списке.
    TreeNode<T>* n_left;

    // Указатель на следующий узел в списке.
    TreeNode<T>* n_right;

    // Конструктор по умолчанию.
    TreeNode() : n_data(T()), n_left(nullptr), n_right(nullptr) {}

    // Конструктор, принимающий данные.
    TreeNode(const T& data) : n_data(data), n_left(nullptr), n_right(nullptr) {}

    // Конструктор, принимающий данные и указатели на предыдущий и следующий узлы.
    TreeNode(const T& data, TreeNode<T>* prev, TreeNode<T>* next) : n_data(data), n_left(prev), n_right(next) {}
    //Деструктор:
    ~TreeNode() {
        // Удаляем указатели на предыдущий и следующий узлы
        if (n_left != nullptr)
            n_left = nullptr;
        if (n_right != nullptr)
            n_right = nullptr;
    }
    //Конструктор копирования :

    TreeNode(const TreeNode& other) : n_data(other.n_data), n_left(nullptr), n_right(nullptr) {
        // Копируем указатели на предыдущий и следующий узлы
        if (other.n_left != nullptr) {
            n_left = new TreeNode(other.n_left->n_data);
        }
        if (other.n_right != nullptr) {
            n_right = new TreeNode(other.n_right->n_data);
        }
    }


    //Конструктор перемещения :

    TreeNode(TreeNode&& other) : n_data(other.n_data), n_left(other.n_left), n_right(other.n_right) {
        // Перемещаем указатели на предыдущий и следующий узлы
        other.n_left = nullptr;
        other.n_right = nullptr;
    }


    //Оператор копирования :

    TreeNode& operator=(const TreeNode& other) {
        // Проверяем самоприсваивание
        if (this == &other) {
            return *this;
        }

        // Удаляем текущие указатели на предыдущий и следующий узлы
        delete n_left;
        delete n_right;

        // Копируем данные и указатели из другого узла
        n_data = other.n_data;
        if (other.n_left != nullptr) {
            n_left = new TreeNode(other.n_left->n_data);
        }
        if (other.n_right != nullptr) {
            n_right = new TreeNode(other.n_right->n_data);
        }

        return *this;
    }


    //Оператор перемещения :

    TreeNode& operator=(TreeNode&& other) {
        // Проверяем самоприсваивание
        if (this == &other) {
            return *this;
        }

        // Перемещаем данные и указатели из другого узла
        n_data = other.n_data;
        n_left = other.n_left;
        n_right = other.n_right;

        // Очищаем указатели в перемещаемом узле
        other.n_left = nullptr;
        other.n_right = nullptr;

        return *this;
    }
};
template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // Поиск следующего наибольшего элемента, возвращает узел, иначе нуллптр
    TreeNode<T>* searchSucc(TreeNode<T>* node, const T& value) {
        TreeNode<T>* prev = nullptr;
        TreeNode<T>* current = root;

        // Найдем узел с заданным значением и сохраним путь в стек
        while (current != nullptr) {
            if (current->n_data == value) {
                break;
            }
            else if (value < current->n_data) {
                prev = current;
                current = current->n_left;
            }
            else {
                prev = current;
                current = current->n_right;
            }
        }
        if (current == nullptr) {
            return nullptr; // Значение не найдено
        }
        // Если у текущего узла есть правый потомок, то следующий наибольший элемент - это наименьший элемент в правом поддереве
        if (current->n_right != nullptr) {
            current = current->n_right;
            while (current->n_left != nullptr) {
                current = current->n_left;
            }
            return current;
        }
        // Иначе ищем следующий наибольший элемент, поднимаясь вверх по дереву
        if (prev)
            return prev;
        else
            return nullptr;
    }

    void deleteNodeRecursive(TreeNode<T>** node, const T& value) {
        if (*node == nullptr) {
            return; // Узел не найден
        }

        // Если значение меньше, чем значение в текущем узле, идем влево
        if (value < (*node)->n_data) {
            deleteNodeRecursive(&(*node)->n_left, value);
        }
        // Если значение больше, чем значение в текущем узле, идем вправо
        else if (value > (*node)->n_data) {
            deleteNodeRecursive(&(*node)->n_right, value);
        }
        // Найден узел для удаления
        else {
            TreeNode<T>* nodeToDelete = *node;

            // Если у узла нет дочерних узлов, просто удаляем его
            if ((*node)->n_left == nullptr && (*node)->n_right == nullptr) {
                *node = nullptr;
                delete nodeToDelete;
            }
            // Если у узла есть только левый дочерний узел, присоединяем его к родителю
            else if ((*node)->n_left != nullptr && (*node)->n_right == nullptr) {
                *node = (*node)->n_left;
                nodeToDelete->n_left = nullptr;
                delete nodeToDelete;
            }
            // Если у узла есть только правый дочерний узел, присоединяем его к родителю
            else if ((*node)->n_left == nullptr && (*node)->n_right != nullptr) {
                *node = (*node)->n_right;
                nodeToDelete->n_right = nullptr;
                delete nodeToDelete;
            }
            // Если у узла есть оба дочерних узла, ищем следующий наибольший элемент и меняем местами
            else {
                TreeNode<T>* nextLargest = searchSucc(*node, (*node)->n_data);
                (*node)->n_data = nextLargest->n_data;
                deleteNodeRecursive(&(*node)->n_right, nextLargest->n_data);
            }
        }
    }


public:

    BinarySearchTree() :root(nullptr) {}
    BinarySearchTree(T value) {
        root = new TreeNode<T>(value);
    }
    ~BinarySearchTree() {
        deleteTree(root);
    }
    /*
    enum OrderType {
        PREORDER, // NLR
        INORDER,  // LNR
        POSTORDER // LRN
    };
    */
    // Копировать древо. Возвращает древо
    BinarySearchTree copy()
    {
        BinarySearchTree tree;
        copyTreeRecursive(root, tree);
        return tree;
    }
    // Очистка древа
    void clear() {
        deleteTree(root);   // Очищаем дерево
        root = nullptr; // Обнуляем корень дерева
    }
    // Применить функцию к элементам древа
    void apply(const function<void(T&)>& func) {
        applyFunction(root, func);
    }
    // Добавить значение к узлу в виде нового узла
    static void addNode(TreeNode<T>* node, T value) {
        if (value < node->n_data) {
            if (node->n_left) {
                addNode(node->n_left, value);
            }
            else
            {
                node->n_left = new TreeNode<T>(value);
            }
        }
        else
        {
            if (node->n_right) {
                addNode(node->n_right, value);
            }
            else
            {
                node->n_right = new TreeNode<T>(value);
            }
        }
    }
    // Добавить значение дереву
    void insert(const T& value) {
        if (!root) {
            root = new TreeNode<T>(value);
        }
        else
        {
            addNode(root, value);
        }
    }
    // Вывести значение узла на экран
    void printNode(TreeNode<T>* node) const {
        if (node) {
            cout << node->n_data << endl;
        }
        else {
            cout << "Пусто" << endl;
        }
    }

    // Создание массива на основе препорядкового обхода (NLR)
    vector<T> toArrayPreOrder() const {
        vector<T> result;
        preorder(root, result);
        return result;
    }

    // Создание массива на основе инордерного обхода (LNR)
    vector<T> toArrayInOrder() const {
        vector<T> result;
        inorder(root, result);
        return result;
    }

    // Создание массива на основе постпорядкового обхода (LRN)
    vector<T> toArrayPostOrder() const {
        vector<T> result;
        postorder(root, result);
        return result;
    }
    // Печать дерева NLR
    void printPreOrder() const {
        vector<T> result = toArrayPreOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Вывод содержимого узлов дерева в порядке LNR
    void printInOrder() const {
        vector<T> result = toArrayInOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Вывод содержимого узлов дерева в порядке LRN
    void printPostOrder() const {
        vector<T> result = toArrayPostOrder();
        for (const T& val : result) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Функция печати дерева в виде дерева
    void printTree() const {
        printTreeRecursive(root, 0);
    }
    void remove(T value)
    {
        deleteNodeRecursive(&root, value);
    }

    // Функция определения глубины дерева
    int getDepth() const {
        return getDepthRecursive(root);
    }
    // Функция подсчета числа узлов
    size_t countNodes() const {
        return countNodesRecursive(root);
    }
    // Проверка на пустоту дерева
    bool isEmpty() const {
        if (root != nullptr)
            return false;
        else
            return true;
    }

    // Поиск следующего наибольшего элемента, возвращает значение, иначе бросает исключение
    T succesor(const T& value) {
        TreeNode<T>* nextNode = searchSucc(root, value);
        if (nextNode == nullptr) {
            throw std::out_of_range("Значение не найдено в дереве");
        }
        return nextNode->n_data;
    }





    // Метод для поиска узла по значению
    TreeNode<T>* search(const T& value) const {
        return searchRecursive(root, value); // Запускаем поиск с корневого узла
    }
    // Получить указатель на корень
    TreeNode<T>* get_root() const {
        return root;
    }



    // Функция тестирования
    static void runTests() {
        // Тест для обычного дерева
        BinarySearchTree<int> normalTree;
        normalTree.insert(10);
        normalTree.insert(5);
        normalTree.insert(15);
        normalTree.insert(2);
        normalTree.insert(7);
        normalTree.insert(12);
        normalTree.insert(20);

        assert(normalTree.countNodes() == 7);
        assert(normalTree.getDepth() == 2);

        normalTree.clear();
        assert(normalTree.countNodes() == 0);
        assert(normalTree.getDepth() == -1);

        // Тест для вырожденного дерева (слева)
        BinarySearchTree<int> leftSkewedTree;
        leftSkewedTree.insert(10);
        leftSkewedTree.insert(5);
        leftSkewedTree.insert(2);
        assert(leftSkewedTree.countNodes() == 3);
        assert(leftSkewedTree.getDepth() == 2);

        leftSkewedTree.clear();
        assert(leftSkewedTree.countNodes() == 0);
        assert(leftSkewedTree.getDepth() == -1);

        // Тест для вырожденного дерева (справа)
        BinarySearchTree<int> rightSkewedTree;
        rightSkewedTree.insert(10);
        rightSkewedTree.insert(15);
        rightSkewedTree.insert(20);

        assert(rightSkewedTree.countNodes() == 3);
        assert(rightSkewedTree.getDepth() == 2);

        rightSkewedTree.clear();
        assert(rightSkewedTree.countNodes() == 0);
        assert(rightSkewedTree.getDepth() == -1);

        // Тест для пустого дерева
        BinarySearchTree<int> emptyTree;
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);

        emptyTree.clear();
        assert(emptyTree.countNodes() == 0);
        assert(emptyTree.getDepth() == -1);

        // Тест для дерева из одного узла
        BinarySearchTree<int> singleNodeTree;
        singleNodeTree.insert(10);
        assert(singleNodeTree.countNodes() == 1);
        assert(singleNodeTree.getDepth() == 0);

        singleNodeTree.clear();
        assert(singleNodeTree.countNodes() == 0);
        assert(singleNodeTree.getDepth() == -1);

        // Тест для создания массива на основе обхода
        BinarySearchTree<int> arrayTree;
        arrayTree.insert(10);
        arrayTree.insert(5);
        arrayTree.insert(15);
        arrayTree.insert(2);
        arrayTree.insert(7);
        arrayTree.insert(12);
        arrayTree.insert(20);

        vector<int> inorderArray = arrayTree.toArrayInOrder();
        vector<int> expectedInorderArray = { 2, 5, 7, 10, 12, 15, 20 };
        assert(inorderArray == expectedInorderArray);

        vector<int> preorderArray = arrayTree.toArrayPreOrder();
        vector<int> expectedPreorderArray = { 10, 5, 2, 7, 15, 12, 20 };
        assert(preorderArray == expectedPreorderArray);

        vector<int> postorderArray = arrayTree.toArrayPostOrder();
        vector<int> expectedPostorderArray = { 2, 7, 5, 12, 20, 15, 10 };
        assert(postorderArray == expectedPostorderArray);

        // Тест для применения функции к узлам дерева
        arrayTree.apply([](int& val) { val *= 2; });

        vector<int> updatedInorderArray = arrayTree.toArrayInOrder();
        vector<int> expectedUpdatedInorderArray = { 4, 10, 14, 20, 24, 30, 40 };
        assert(updatedInorderArray == expectedUpdatedInorderArray);


        // Тест для применения функции к узлам дерева
        arrayTree.apply([](int& val) { val *= 2; });
        // Тест для вырожденного дерева

        BinarySearchTree<int> degenerateTree;
        degenerateTree.insert(10);
        degenerateTree.insert(9);
        degenerateTree.insert(8);
        degenerateTree.insert(7);

        degenerateTree.apply([](int& val) { val *= 2; });

        vector<int> updatedDegenerateArray = degenerateTree.toArrayInOrder();
        vector<int> expectedUpdatedDegenerateArray = { 14, 16, 18, 20 };
        assert(updatedDegenerateArray == expectedUpdatedDegenerateArray);

        degenerateTree.clear();

        // Тест для пустого дерева
        emptyTree.apply([](int& val) { val *= 2; });

        vector<int> emptyArray = emptyTree.toArrayInOrder();
        vector<int> expectedEmptyArray = {};
        assert(emptyArray == expectedEmptyArray);

        emptyTree.clear();

        // Тест для дерева с одним узлом
        singleNodeTree.insert(10);

        singleNodeTree.apply([](int& val) { val *= 2; });

        vector<int> singleNodeArray = singleNodeTree.toArrayInOrder();
        vector<int> expectedSingleNodeArray = { 20 };
        assert(singleNodeArray == expectedSingleNodeArray);

        singleNodeTree.clear();
        cout << "Тесты пройдены" << endl;
    }

};
template<typename T>
// Рекурсивная функция подсчета узлов (препорядковый обход)
size_t countNodesRecursive(const TreeNode<T>* node) {
    if (node == nullptr) return 0;
    //Возвращаем количество узлов слева и справа + сам узел
    return 1 + countNodesRecursive(node->n_left) + countNodesRecursive(node->n_right);
}
template<typename T>
// Рекурсивная функция определения глубины (инордерный обход)
int getDepthRecursive(const TreeNode<T>* node) {
    if (node == nullptr) return -1;
    int leftDepth = getDepthRecursive(node->n_left);
    int rightDepth = getDepthRecursive(node->n_right);
    return 1 + max(leftDepth, rightDepth);
}
template<typename T>
// Рекурсивный вывод дерева
void printTreeRecursive(const TreeNode<T>* node, int level) {
    if (node == nullptr) return;

    // Печать правого поддерева
    printTreeRecursive(node->n_right, level + 1);

    // Печать текущего узла. Число пропусков определяется уровнем
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << node->n_data << endl;

    // Печать левого поддерева
    printTreeRecursive(node->n_left, level + 1);
}
template<typename T>
void deleteTree(TreeNode<T>* node) {
    if (node) {
        deleteTree(node->n_left);
        deleteTree(node->n_right);
        delete node;
    }
}

// Сделать функциями все рекурсивные методы
template<typename T>
// Глубокое копирование дерева NLR
void copyTreeRecursive(TreeNode<T>* node, BinarySearchTree<T>& tree)
{
    if (node != nullptr)
    {
        tree.insert(node->n_data);
        copyTreeRecursive(node->n_left, tree);
        copyTreeRecursive(node->n_right, tree);
    }
}
template<typename T>
// Вспомогательный метод для рекурсивного поиска узла
TreeNode<T>* searchRecursive(TreeNode<T>* node, const T& value) {
    if (node == nullptr) {
        return nullptr; // Значение не найдено
    }

    if (node->n_data == value) {
        return node; // Значение найдено, возвращаем узел
    }
    else if (value < node->n_data) {
        return searchRecursive(node->n_left, value); // Ищем в левом поддереве
    }
    else {
        return searchRecursive(node->n_right, value); // Ищем в правом поддереве
    }
}
template<typename T>
// Препорядковый обход (Near, Left, Right)
void preorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    result.push_back(node->n_data);
    preorder(node->n_left, result);
    preorder(node->n_right, result);
}
template<typename T>
// Инордерный обход (left, Near, Right)
void inorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    inorder(node->n_left, result);
    result.push_back(node->n_data);
    inorder(node->n_right, result);
}
template<typename T>
// Постпорядковый обход (Left, Right, Near)
void postorder(TreeNode<T>* node, vector<T>& result) {
    if (node == nullptr) return;
    postorder(node->n_left, result);
    postorder(node->n_right, result);
    result.push_back(node->n_data);
}
template<typename T>
// Применение функции к каждому узлу NLR
void applyFunction(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    func(node->n_data);
    applyFunction(node->n_left, func);
    applyFunction(node->n_right, func);
}
template<typename T>
// Препорядковое применение функции
void applyPreorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    func(node->n_data);
    applyPreorder(node->n_left, func);
    applyPreorder(node->n_right, func);
}
template<typename T>
// Инордерное применение функции
void applyInorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    applyInorder(node->n_left, func);
    func(node->n_data);
    applyInorder(node->n_right, func);
}
template<typename T>
// Постпорядковое применение функции
void applyPostorder(TreeNode<T>* node, const function<void(T&)>& func) {
    if (node == nullptr) return;
    applyPostorder(node->n_left, func);
    applyPostorder(node->n_right, func);
    func(node->n_data);
}
