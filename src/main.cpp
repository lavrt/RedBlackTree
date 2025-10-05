#include <iostream>

#include "tree.hpp"

int main() {
    RBTree<int> tree;

    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(7);
    tree.Insert(8);
        tree.Insert(1);
    tree.Insert(2);
    tree.Insert(11);
    tree.Insert(14);
    tree.Insert(15);
    
    tree.Dump("dump");

    return 0;
}
