#include <iostream>
#include <vector>
#include <set>

#include "tree.hpp"
#include "commands.hpp"
#include "range_query.hpp"

using KeyT = int;

int main() {
    size_t number_of_queries = 0;

    std::vector<KeyT> data;

    for (char cmd = 0; std::cin >> cmd;) {
        data.push_back(cmd);
        if (cmd == Commands::kKey) {
            KeyT key;
            std::cin >> key;
            data.push_back(key);
        } else if (cmd == Commands::kQuery) {
            ++number_of_queries;
            KeyT fst;
            KeyT snd;
            std::cin >> fst >> snd;
            data.push_back(fst);
            data.push_back(snd);
        } else {
            std::cerr << "Unknown command: " << cmd;
            return 1;
        }
    }

    Trees::RBTree<KeyT> my_tree;
    std::vector<KeyT> answers_of_my_tree;
    answers_of_my_tree.reserve(number_of_queries);

    for (size_t i = 0; i != data.size(); ++i) {
        if (data[i] == Commands::kKey) {
            my_tree.Insert(data[++i]);
        } else if (data[i] == Commands::kQuery) {
            KeyT first = data[++i];
            KeyT second = data[++i];
            answers_of_my_tree.push_back(range_query(my_tree, first, second));
        } else {
            std::cerr << "Unknown command: " << data[i];
            return 1;
        }
    }

    std::set<KeyT> std_tree;
    std::vector<KeyT> answers_of_std_tree;
    answers_of_std_tree.reserve(number_of_queries);

    for (size_t i = 0; i != data.size(); ++i) {
        if (data[i] == Commands::kKey) {
            std_tree.insert(data[++i]);
        } else if (data[i] == Commands::kQuery) {
            KeyT first = data[++i];
            KeyT second = data[++i];
            answers_of_std_tree.push_back(range_query(std_tree, first, second));
        } else {
            std::cerr << "Unknown command: " << data[i];
            return 1;
        }
    }

    return 0;
}
