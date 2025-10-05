#pragma once

#include <memory>
#include <fstream>
#include <iostream>

#include "node.hpp"

template <typename KeyT>
class RBTree {
private:
    Node<KeyT>* root_ = nullptr;
    Node<KeyT>* nil_ = nullptr;

    void DeleteTree(Node<KeyT>* node) {
        if (node != nil_) {
            DeleteTree(node->left);
            DeleteTree(node->right);
            delete node;
        }
    }

    void LeftRotate(Node<KeyT>* x) {
        Node<KeyT>* y = x->right;
        x->right = y->left;
        if (x->right != nil_) {
            x->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil_) {
            root_ = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void RightRotate(Node<KeyT>* y) {
        Node<KeyT>* x = y->left;
        y->left = x->right;
        if (y->left != nil_) {
            y->left->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nil_) {
            root_ = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    void InsertFixup(Node<KeyT>* z) {
        while (z->parent->is_red) {
            if (z->parent == z->parent->parent->left) {
                Node<KeyT>* y = z->parent->parent->right;
                if (y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        LeftRotate(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    RightRotate(z->parent->parent);
                }
            } else {
                Node<KeyT>* y = z->parent->parent->left;
                if (y->is_red) {
                    z->parent->is_red = false;
                    y->is_red = false;
                    z->parent->parent->is_red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->is_red = false;
                    z->parent->parent->is_red = true;
                    LeftRotate(z->parent->parent);
                }
            }
        }
        root_->is_red = false;
    }

public:
    RBTree() {
        nil_ = new Node<KeyT>(0);
        nil_->is_red = false;
        nil_->left = nil_->right = nil_;
        root_ = nil_;
    }

    ~RBTree() {
        DeleteTree(root_);
        delete nil_;
    }

    bool Insert(KeyT key) {
        Node<KeyT>* parent = nil_;
        
        for (Node<KeyT>* current = root_; current != nil_;) {
            if (current->key == key) {
                return false;
            }
            parent = current;
            current = (key < current->key) ? current->left : current->right;
        }

        Node<KeyT>* new_node = new Node<KeyT>(key);
        new_node->parent = parent;
        new_node->left = nil_;
        new_node->right = nil_;

        if (parent == nil_) {
            root_ = new_node;
        } else if (new_node->key < parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        new_node->left = new_node->right = nil_;
        new_node->is_red = true;

        InsertFixup(new_node);

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

    void DefiningGraphNodes(std::ofstream& file, Node<KeyT>* node) const {
        static size_t rank = 0;
        file << "    node_" << node
             << " [rank=" << rank
             << ",label=\" { node: " << node
             << " | key: " << node->key
             << " | { left: " << node->left
             << " | right: " << node->right
             << " }} \", "
             << (node->is_red
                    ? "fontcolor=\"#000000\", fillcolor=\"#FF6B6B\", color = \"#C53030\"];\n"
                    : "fontcolor=\"#FFFFFF\", fillcolor=\"#2D3748\", color = \"#1A202C\"];\n");

        if (node->left != nil_) {
            rank++;
            DefiningGraphNodes(file, node->left);
        }
        if (node->right != nil_) {
            rank++;
            DefiningGraphNodes(file, node->right);
        }
        rank--;
    }

    void DefiningGraphDependencies(std::ofstream& file, Node<KeyT>* node) const {
        static int flag = 0;
        if (node->left != nil_) {
            if (flag++) {
                file << "-> node_" << node->left << " ";
            } else {
                file << "    node_" << node << " -> node_" << node->left << " ";
            }
            DefiningGraphDependencies(file, node->left);
        }
        if (node->right != nil_) {
            if (flag++) {
                file << "-> node_" << node->right << " ";
            } else {
                file << "    node_" << node << " -> node_" << node->right << " ";
            }
            DefiningGraphDependencies(file, node->right);
        }
        if (flag) {
            file << ";\n";
        }
        flag = 0;
    }
};
