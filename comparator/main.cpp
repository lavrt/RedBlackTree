#include <iostream>
#include <set>

#include "comparator.hpp"

using KeyT = int;

int main() {
    Comparators::Comparator<KeyT> c;

    c.ReadData(std::cin);

    Trees::RBTree<KeyT> my_tree;
    c.Test(my_tree);

    std::set<KeyT> std_tree;
    c.Test(std_tree);

    std::cout << "Trees::RBTree Time: " << c.time_of_my_tree << " microseconds\n";
    std::cout << "std::set Time: " << c.time_of_std_tree << " microseconds\n";

    return 0;
}
