#include <vector>
#include <fstream>
#include <iostream>

#include "tree.hpp"
#include "commands.hpp"
#include "range_query.hpp"

using KeyT = int;

int main(int argc, char** argv) {
    std::vector<std::string> args(argv, argv + argc);

    std::string data_filename;
    std::string answers_filename;
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i] == "--data") {
            data_filename = args[++i];
        } else if (args[i] == "--answers") {
            answers_filename = args[++i];
        }
    }

    std::ifstream answers_file("./tests/e2e/test_data/" + answers_filename);
    if (!answers_file.is_open()) {
        throw std::runtime_error("File opening error");
    }

    std::vector<size_t> answers;
    for (size_t answer = 0; answers_file >> answer;) {
        answers.push_back(answer);
    }

    std::ifstream data_file("./tests/e2e/test_data/" + data_filename);
    if (!data_file.is_open()) {
        throw std::runtime_error("File opening error");
    }

    auto answer = answers.begin();
    Trees::RBTree<KeyT> tree;
    for (char cmd = 0; data_file >> cmd;) {
        if (cmd == Commands::kKey) {
            KeyT key = 0;
            data_file >> key;
            tree.Insert(key);
        } else if (cmd == Commands::kQuery) {
            KeyT first = 0;
            KeyT second = 0;
            data_file >> first >> second;
            if (RangeQuery::range_query(tree, first, second) != *answer++) {
                std::cerr << "Test failed: " << data_filename << "\n";
                return 1;
            }
        } else {
            std::cerr << "Unknown command: " << cmd;
            return 1;
        }
    }

    return 0;
}
