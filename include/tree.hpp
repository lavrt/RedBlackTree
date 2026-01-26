#pragma once

#include <fstream>

namespace Trees {

template <typename KeyT>
class RBTree {
    class Node;

public:
    RBTree() : nil_(new Node(0)) {
        nil_->is_red = false;
        nil_->size = 0;
        root_ = nil_->parent = nil_->left = nil_->right = nil_;
    }

    ~RBTree() {
        DeleteTree(root_);
        delete nil_;
    }

    RBTree(const RBTree<KeyT>& other) : nil_(new Node(0)) {
        nil_->is_red = false;
        nil_->size = 0;
        nil_->parent = nil_->left = nil_->right = nil_;
        root_ = CopySubtree(other.root_, nil_, other.nil_);
    }

    RBTree& operator=(const RBTree<KeyT>& other) {
        RBTree<KeyT> temp(other);
        std::swap(root_, temp.root_);
        std::swap(nil_, temp.nil_);
        return *this;
    }

    RBTree(RBTree&& other) noexcept : nil_(nullptr), root_(nullptr) {
        std::swap(nil_, other.nil_);
        std::swap(root_, other.root_);
    }

    RBTree& operator=(RBTree<KeyT>&& other) noexcept {
        std::swap(nil_, other.nil_);
        std::swap(root_, other.root_);
        return *this;
    }

    class Iterator {
    private:
        Node* current_;
        Node* nil_;

    public:
        Iterator(Node* node = nullptr, Node* nil = nullptr)
            : current_(node), nil_(nil) {}

        const KeyT& operator*() const {
            return current_->key;
        }

        Iterator& operator++() { // TODO хранить дерево в векторе, чтобы удобнее оптимизировать
            if (current_->right != nil_) {
                current_ = current_->right;
                while (current_->left != nil_) {
                    current_ = current_->left;
                }
            } else {
                Node* parent = current_->parent;
                while (current_ != nil_ && parent->right == current_) {
                    current_ = parent;
                    parent = current_->parent;
                }
                current_ = parent;
            }
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    }; // class Iterator

    Iterator begin() const {
        if (root_ == nil_) {
            return end();
        }

        Node* current = root_;
        while (current->left != nil_) {
            current = current->left;
        }

        return Iterator(current, nil_);
    }

    Iterator end() const {
        return Iterator(nil_, nil_);
    }

    bool Insert(KeyT key) {
        Node* parent = nil_;
        
        for (Node* current = root_; current != nil_;) {
            if (current->key == key) {
                return false;
            }
            parent = current;
            current = (key < current->key) ? current->left : current->right;
        }
        
        Node* new_node = new Node(key, parent, nil_, nil_, true); 

        if (parent == nil_) {
            root_ = new_node;
        } else if (new_node->key < parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        for (Node* current = parent; current != nil_;) {
            current->size++;
            current = current->parent;
        }

        InsertFixup(new_node);

        return true;
    }

    RBTree<KeyT>::Iterator LowerBound(KeyT key) const {
        Node* candidate = nil_;

        for (Node* current = root_; current != nil_;) {
            if (current->key >= key) {
                candidate = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return Iterator(candidate, nil_);
    }

    RBTree<KeyT>::Iterator UpperBound(KeyT key) const {
        Node* candidate = nil_;

        for (Node* current = root_; current != nil_;) {
            if (current->key > key) {
                candidate = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return Iterator(candidate, nil_);
    }

    size_t Distance(RBTree<KeyT>::Iterator first, RBTree<KeyT>::Iterator second) const {
        return RankIter(second) - RankIter(first);
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

private:
    Node* nil_;
    Node* root_;

    void DeleteTree(Node* node) {
        if (node != nil_) {
            DeleteTree(node->left);
            DeleteTree(node->right);
            delete node;
        }
    }

    void LeftRotate(Node* x) {
        Node* y = x->right;
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
        y->size = x->size;
        x->size = x->left->size + x->right->size + 1;
    }

    void RightRotate(Node* y) {
        Node* x = y->left;
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
        x->size = y->size;
        y->size = y->left->size + y->right->size + 1;
    }

    void InsertFixup(Node* z) {
        while (z->parent->is_red) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
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
                Node* y = z->parent->parent->left;
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

    size_t RankLess(KeyT target) const {
        size_t r = 0;

        for (Node* current = root_; current != nil_;) {
            if (target <= current->key) {
                current = current->left;
            } else {
                r += current->left->size + 1;
                current = current->right;
            }
        }

        return r;
    }

    size_t RankIter(const RBTree<KeyT>::Iterator& it) const {
        return (it == end()) ? root_->size : RankLess(*it);
    }

    Node* CopySubtree(Node* other_node, Node* parent,
        Node* other_nil_node) const
    {
        if (other_node == other_nil_node) {
            return nil_;
        }

        Node* node = new Node(other_node->key);
        node->parent = parent;
        node->is_red = other_node->is_red;
        node->size = other_node->size;
        
        node->left = CopySubtree(other_node->left, node, other_nil_node);
        node->right = CopySubtree(other_node->right, node, other_nil_node);

        return node;
    }

    void DefiningGraphNodes(std::ofstream& file, Node* node) const {
        static size_t rank = 0;
        file << "    node_" << node
             << " [rank=" << rank
             << ",label=\" { parent: " << node->parent
             << " | node: " << node
             << " | key: " << node->key
             << "; size: " << node->size
             << "; rank: " << RankLess(node->key)
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

    void DefiningGraphDependencies(std::ofstream& file, Node* node) const {
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

    class Node {
    public:
        KeyT key;

        Node* parent;
        Node* left;
        Node* right;

        bool is_red;
        size_t size;

        Node(KeyT key) : key(key), parent(nullptr), left(nullptr), right(nullptr), is_red(false), size(1) {}
        
        Node(KeyT key, Node* parent, Node* left, Node* right, bool is_red)
            : key(key), parent(parent), left(left), right(right), is_red(is_red), size(left->size + right->size + 1) {}

        ~Node() = default;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&) = default;
        Node& operator=(Node&&) = default;
    };
};

} // namespace Trees
