#pragma once

#include <stdexcept>
#include <iostream>
#include <vector>
#include <chrono>
#include <set>

#include "tree.hpp"
#include "commands.hpp"
#include "range_query.hpp"

namespace Comparators {

template <typename KeyT>
class Comparator {
public:
    std::vector<KeyT> data;
    size_t number_of_queries = 0;

    std::vector<KeyT> answers_of_my_tree;
    long long time_of_my_tree;

    std::vector<KeyT> answers_of_std_tree;
    long long time_of_std_tree;

    void ReadData(std::istream& stream) {
        for (char cmd = 0; stream >> cmd;) {
            data.push_back(cmd);
            if (cmd == Commands::kKey) {
                KeyT key;
                stream >> key;
                data.push_back(key);
            } else if (cmd == Commands::kQuery) {
                ++number_of_queries;
                KeyT fst;
                KeyT snd;
                stream >> fst >> snd;
                data.push_back(fst);
                data.push_back(snd);
            } else {
                throw std::runtime_error("Unknown command: " + cmd);
            }
        }
    }

    void Test(Trees::RBTree<KeyT>& tree) {
        answers_of_my_tree.reserve(number_of_queries);

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i != data.size(); ++i) {
            if (data[i] == Commands::kKey) {
                tree.Insert(data[++i]);
            } else if (data[i] == Commands::kQuery) {
                KeyT first = data[++i];
                KeyT second = data[++i];
                answers_of_my_tree.push_back(RangeQuery::range_query(tree, first, second));
            } else {
                throw std::runtime_error("Unknown command: " + data[i]);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        time_of_my_tree = duration.count();
    }

    void Test(std::set<KeyT>& tree) {
        answers_of_std_tree.reserve(number_of_queries);

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i != data.size(); ++i) {
            if (data[i] == Commands::kKey) {
                tree.insert(data[++i]);
            } else if (data[i] == Commands::kQuery) {
                KeyT first = data[++i];
                KeyT second = data[++i];
                answers_of_std_tree.push_back(RangeQuery::range_query(tree, first, second));
            } else {
                throw std::runtime_error("Unknown command: " + data[i]);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        time_of_std_tree = duration.count();
    }
};

} // namespace Comparators
