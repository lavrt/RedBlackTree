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
    itt start = s.LowerBound(fst);
    itt fin = s.UpperBound(snd);
    return s.Distance(start, fin);
}

template <typename KeyT>
int range_query(const std::set<KeyT>& s, KeyT fst, KeyT snd) {
    using itt = typename std::set<KeyT>::iterator;
    itt start = s.lower_bound(fst);
    itt fin = s.upper_bound(snd);
    return std::distance(start, fin);
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
            std::cout << range_query(tree, first, second) << "\n";
            continue;
        }

        std::cerr << "Unknown command: " << c;
        return 1;
    }

    tree.Dump("dump");

    return 0;
}
