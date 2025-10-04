#pragma once

#include <memory>
#include <fstream>
#include <iostream>

#include "node.hpp"

template <typename KeyT>
class RBTree {
private:
    std::unique_ptr<Node<KeyT>> root_ = nullptr;

    void FixTree() {}

public:
    bool Insert(KeyT key) {
        Node<KeyT>* parent = nullptr;
        
        for (Node<KeyT>* current = root_.get(); current != nullptr;) {
            if (current->key == key) {
                return false;
            }

            parent = current;
            current = (key < current->key) ? current->left.get() : current->right.get();
        }

        auto new_node = std::make_unique<Node<KeyT>>(key);
        new_node->parent = parent;

        if (parent == nullptr) {
            new_node->is_red = false;
            root_ = std::move(new_node);
        } else if (new_node->key < parent->key) {
            parent->left = std::move(new_node);
        } else {
            parent->right = std::move(new_node);
        }

        if (parent->parent != nullptr) {
            FixTree();
        }

        return true;
    }

    void Dump(const std::string& file_name) const {
        if (root_ == nullptr) {
            throw std::runtime_error("Empty tree dump");
        }

        std::ofstream file(file_name + ".gv");
        if (!file) {
            throw std::runtime_error("Cannot open file: " + file_name + ".gv");
        }

        file << "digraph\n"
            << "{\n    "
            << "rankdir = TB;\n    "
            << "node [shape=record,style = filled,penwidth = 2.5];\n    "
            << "bgcolor = \"#F8F9FA\";\n\n";

        DefiningGraphNodes(file, root_);
        file << "\n";
        DefiningGraphDependencies(file, root_);

        file << "}\n";

        file.close();
    }

    void DefiningGraphNodes(std::ofstream& file, const std::unique_ptr<Node<KeyT>>& node) const {
        static size_t rank = 0;
        file << "    node_" << node.get()
             << " [rank=" << rank
             << ",label=\" { node: " << node.get()
             << " | key: " << node->key
             << " | { left: " << node->left.get()
             << " | right: " << node->right.get()
             << " }} \", "
             << (node->is_red
                    ? "fontcolor=\"#000000\", fillcolor=\"#FF6B6B\", color = \"#C53030\"];\n"
                    : "fontcolor=\"#FFFFFF\", fillcolor=\"#2D3748\", color = \"#1A202C\"];\n");

        if (node->left) {
            rank++;
            DefiningGraphNodes(file, node->left);
        }
        if (node->right) {
            rank++;
            DefiningGraphNodes(file, node->right);
        }
        rank--;
    }

    void DefiningGraphDependencies(std::ofstream& file, const std::unique_ptr<Node<KeyT>>& node) const {
        static int flag = 0;
        if (node->left) {
            if (flag++) {
                file << "-> node_" << node->left.get() << " ";
            } else {
                file << "    node_" << node.get() << " -> node_" << node->left.get() << " ";
            }
            DefiningGraphDependencies(file, node->left);
        }
        if (node->right) {
            if (flag++) {
                file << "-> node_" << node->right.get() << " ";
            } else {
                file << "    node_" << node.get() << " -> node_" << node->right.get() << " ";
            }
            DefiningGraphDependencies(file, node->right);
        }
        if (flag) {
            file << ";\n";
        }
        flag = 0;
    }
};
