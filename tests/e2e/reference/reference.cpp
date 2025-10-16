#include <iostream>
#include <set>

#include "commands.hpp"
#include "range_query.hpp"

using KeyT = int;

int main() {
    std::set<KeyT> tree;

    for (char cmd = 0; std::cin >> cmd;) {
        if (cmd == Commands::kKey) {
            KeyT key = 0;
            std::cin >> key;
            tree.insert(key);
        } else if (cmd == Commands::kQuery) {
            KeyT first = 0;
            KeyT second = 0;
            std::cin >> first >> second;
            std::cout << RangeQuery::range_query(tree, first, second) << "\n";
        } else {
            std::cerr << "Unknown command: " << cmd;
            return 1;
        }
    }

    return 0;
}
