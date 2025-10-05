#include <iostream>
#include <set>

#include "tree.hpp"

namespace {
    const char kKey = 'k';
    const char kQuery = 'q';
} // namespace

template <typename KeyT>
int range_query(const RBTree<KeyT>& s, KeyT fst, KeyT snd) {
    using itt = typename RBTree<KeyT>::Iterator;
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
    RBTree<int> tree;

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
            std::cout << range_query<int>(tree, first, second) << "\n";
            continue;
        }

        std::cerr << "Unknown command: " << c;
        return 1;
    }

    // tree.insert(10);
    // tree.insert(20);
    // tree.insert(30);
    // tree.insert(40);

    // int k = 11;
    // std::cout << "tree.lower_bound(" << k << ")->key=" << tree.lower_bound(k)->key << "\n";
    
    // std::cout << *tree.lower_bound(8) << "\n";
    // std::cout << *tree.lower_bound(31) << "\n";
    // std::cout << tree.distance(tree.lower_bound(8), tree.lower_bound(31)) << "\n";
    // if (itt != tree.end()) {
    //     std::cout << "*itt=" << *itt << "\n";
    // } else {
    //     std::cout << "*itt=tree.end()\n";
    // }

    // std::cout << "*tree.begin()=" << *tree.begin() << "\n";
    
    // for (int it : tree) {
    //     std::cout << it << "\n";
    // }



    tree.Dump("dump");

    return 0;
}
