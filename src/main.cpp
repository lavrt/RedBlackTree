#include <iostream>
#include <set>

#include "tree.hpp"

namespace {
    const char kKey = 'k';
    const char kQuery = 'q';
} // namespace

template <typename KeyT>
int range_query(const Trees::RBTree<KeyT>& s, KeyT fst, KeyT snd) {
    using itt = typename Trees::RBTree<KeyT>::Iterator;
    itt start = s.UpperBound(fst);
    itt fin = s.LowerBound(snd);
    return s.Distance(start, fin) + 1;
}

template <typename KeyT>
int range_query(const std::set<KeyT>& s, KeyT fst, KeyT snd) {
    using itt = typename std::set<KeyT>::iterator;
    itt start = s.upper_bound(fst);
    itt fin = s.lower_bound(snd);
    return std::distance(start, fin) + 1;
}

int main() {
    Trees::RBTree<int> tree;

    char c = 0;
    while (std::cin >> c) {
        if (c == kKey) {
            int k = 0;
            std::cin >> k;
            tree.Insert(k);
            continue;
        }

        if (c == kQuery) {
            int first = 0;
            int second = 0;
            std::cin >> first >> second;
            std::cout << (second > first ? range_query(tree, first, second) : 0) << "\n";
            continue;
        }

        std::cerr << "Unknown command: " << c;
        return 1;
    }

    tree.Dump("dump1");

    Trees::RBTree<int> new_tree(tree);
    new_tree.Dump("dump2");

    tree = new_tree;
    tree.Dump("dump3");

    return 0;
}
