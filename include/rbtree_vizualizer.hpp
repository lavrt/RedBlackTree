#pragma once

#include <fstream>

#include "tree.hpp"

namespace Trees {

template <typename KeyT>
class RBTreeVizualizer {
public:
    static void Dump(const RBTree<KeyT>& t, const std::string& file_name) {
        std::ofstream file(file_name + ".gv");
        if (!file) {
            throw std::runtime_error("Cannot open file: " + file_name + ".gv");
        }

        file << "digraph\n"
            << "{\n    "
            << "rankdir = TB;\n    "
            << "node [shape=record,style = filled,penwidth = 2.5];\n    "
            << "bgcolor = \"#F8F9FA\";\n\n";

        DefiningGraphNodes(file, t, t.root_);
        file << "\n";
        DefiningGraphDependencies(file, t, t.root_);

        file << "}\n";

        file.close();
    }

private:
    static void DefiningGraphNodes(std::ofstream& file, const RBTree<KeyT>& t, RBTree<KeyT>::Node* node) {
        static size_t rank = 0;
        file << "    node_" << node
             << " [rank=" << rank
             << ",label=\" { parent: " << node->parent
             << " | node: " << node
             << " | key: " << node->key
             << "; size: " << node->size
             << "; rank: " << t.RankLess(node->key)
             << " | { left: " << node->left
             << " | right: " << node->right
             << " }} \", "
             << (node->is_red
                    ? "fontcolor=\"#000000\", fillcolor=\"#FF6B6B\", color = \"#C53030\"];\n"
                    : "fontcolor=\"#FFFFFF\", fillcolor=\"#2D3748\", color = \"#1A202C\"];\n");

        if (node->left != t.nil_) {
            rank++;
            DefiningGraphNodes(file, t, node->left);
        }
        if (node->right != t.nil_) {
            rank++;
            DefiningGraphNodes(file, t, node->right);
        }
        rank--;
    }

    static void DefiningGraphDependencies(std::ofstream& file, const RBTree<KeyT>& t, RBTree<KeyT>::Node* node) {
        static int flag = 0;
        if (node->left != t.nil_) {
            if (flag++) {
                file << "-> node_" << node->left << " ";
            } else {
                file << "    node_" << node << " -> node_" << node->left << " ";
            }
            DefiningGraphDependencies(file, t, node->left);
        }
        if (node->right != t.nil_) {
            if (flag++) {
                file << "-> node_" << node->right << " ";
            } else {
                file << "    node_" << node << " -> node_" << node->right << " ";
            }
            DefiningGraphDependencies(file, t, node->right);
        }
        if (flag) {
            file << ";\n";
        }
        flag = 0;
    }
};

} // namespace Trees
