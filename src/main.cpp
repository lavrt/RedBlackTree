#include <iostream>

#include "tree.hpp"

int main() {
    RBTree<int> tree;

    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(12);
    tree.Insert(18);
    
    tree.Dump("dump");

    return 0;
}
