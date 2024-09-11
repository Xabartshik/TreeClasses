#include "BinarySearchTree.h"
// Сделал Ошлаков Dанил, ИВТ-22
/*
   (2)
   / \
  (1) (3)
  /    \
(-7)    (6)





*/
int main() {
    BinarySearchTree<int>::runTests();
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(2);
    bst.insert(8);
    bst.insert(7);
    bst.insert(6);
    bst.insert(12);
    bst.insert(20);

    std::cout << "Число узлов: " << bst.countNodes() << std::endl; // Вывод: 7
    std::cout << "Глубина древа: " << bst.getDepth() << std::endl; // Вывод: 4

    std::cout << bst.succesor(10) << endl;
    bst.printTree(); // Вывод дерева в виде дерева
    cout << endl;
    bst.remove(5);
    cout << endl;
    bst.printTree(); // Вывод дерева в виде дерева
    bst.clear();

    return 0;
}