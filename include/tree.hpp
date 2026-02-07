#pragma once

namespace Trees {

template <typename KeyT>
class RBTree {
    class Node;

#ifdef RBTREE_DEBUG
    template <typename> friend class RBTreeVisualizer;
#endif

public:
    RBTree() : nil_(new Node(0)) {
        nil_->is_red = false;
        nil_->size = 0;
        root_ = nil_->parent = nil_->left = nil_->right = nil_;
    }

    ~RBTree() {
        for (Node* current = root_; current != nil_;) {
            if (current->left != nil_) {
                current = current->left;
            } else if (current->right != nil_) {
                current = current->right;
            } else {
                Node* parent = current->parent;
                
                if (parent != nil_) {
                    if (current == parent->left) {
                        parent->left = nil_;
                    } else {
                        parent->right = nil_;
                    }
                }
                
                delete current;
                current = parent;
            }
        }

        delete nil_;
    }

    RBTree(const RBTree<KeyT>& other) : nil_(new Node(0)) {
        nil_->is_red = false;
        nil_->size = 0;
        nil_->parent = nil_->left = nil_->right = nil_;
        root_ = CopySubtree(other.root_, other.nil_);
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

        Iterator& operator++() {
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
        
        Node* new_node = new Node(key);
        new_node->parent = parent;
        new_node->left = new_node->right = nil_;
        new_node->is_red = true;

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

    Iterator LowerBound(KeyT key) const {
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

    Iterator UpperBound(KeyT key) const {
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

    size_t Distance(Iterator first, Iterator second) const {
        size_t a = RankIter(first);
        size_t b = RankIter(second);
        return (b > a) ? (b - a) : 0;
    }

private:
    Node* nil_;
    Node* root_;

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

    size_t RankIter(const Iterator& it) const {
        return (it == end()) ? root_->size : RankLess(*it);
    }

    Node* CopySubtree(Node* other_root, Node* other_nil) const {
        if (other_root == other_nil) {
            return nil_;
        }

        Node* new_root = new Node(other_root->key);
        new_root->parent = new_root->left = new_root->right = nil_;
        new_root->is_red = other_root->is_red;
        new_root->size = other_root->size;

        Node* old_current = other_root;
        Node* new_current = new_root;

        while (true) {
            if (old_current->left != other_nil && new_current->left == nil_) {
                Node* l = new Node(old_current->left->key);
                l->parent = new_current;
                l->is_red = old_current->left->is_red;
                l->size = old_current->left->size;
                l->left = l->right = nil_;
                new_current->left = l;

                old_current = old_current->left;
                new_current = l;

                continue;
            }

            if (old_current->right != other_nil && new_current->right == nil_) {
                Node* r = new Node(old_current->right->key);
                r->parent = new_current;
                r->is_red = old_current->right->is_red;
                r->size = old_current->right->size;
                r->left = r->right = nil_;
                new_current->right = r;

                old_current = old_current->right;
                new_current = r;

                continue;
            }

            if (old_current == other_root) {
                break;
            }

            old_current = old_current->parent;
            new_current = new_current->parent;
        }

        return new_root;
    }

    class Node {
    public:
        KeyT key;

        Node* parent;
        Node* left;
        Node* right;

        bool is_red;
        size_t size;

        Node(const KeyT& key) : key(key), parent(nullptr), left(nullptr), right(nullptr), is_red(false), size(1) {}

        ~Node() = default;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&) = delete;
        Node& operator=(Node&&) = delete;
    }; // class Node
}; // class RBTree

} // namespace Trees
