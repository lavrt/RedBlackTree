#include <iostream>

#include "tree.hpp"

namespace {
    const char kKey = 'k';
    const char kQuery = 'q';
} // namespace

template <typename It>
size_t mydistance(It first, It second) {
    size_t count = 0;

    for (It iter = first; iter != second; ++iter) {
        ++count;
    }

    return count;
}

template <typename C, typename T>
int range_query(const C& s, T fst, T snd) {
    using itt = typename C::iterator;
    itt start = s.lower_bound(fst);
    itt fin = s.upper_bound(snd);
    return mydistance(start, fin);
}

int main() {
    RBTree<int> tree;

    char c = 0;
    while (std::cin >> c) {
        if (c == kKey) {
            int k = 0;
            std::cin >> k;
            tree.insert(k);
            continue;
        }

        if (c == kQuery) {
            int first = 0;
            int second = 0;
            std::cin >> first >> second;
            std::cout << range_query<RBTree<int>, int>(tree, first, second) << "\n";
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
