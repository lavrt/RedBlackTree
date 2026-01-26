#include <iostream>

#include "tree.hpp"
#include "commands.hpp"
#include "range_query.hpp"

using KeyT = int;

int main() {
    Trees::RBTree<KeyT> tree;

    for (char cmd = 0; std::cin >> cmd;) {
        if (cmd == Commands::kKey) {
            KeyT key = 0;
            std::cin >> key;
            tree.Insert(key);
        } else if (cmd == Commands::kQuery) {
            KeyT first = 0;
            KeyT second = 0;
            std::cin >> first >> second;
            std::cout << RangeQuery::range_query(tree, first, second) << " ";
        } else {
            std::cerr << "Unknown command: " << cmd;
            return 1;
        }
    }
    std::cout << "\n";

    return 0;
}
