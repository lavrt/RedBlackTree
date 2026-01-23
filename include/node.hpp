#pragma once

namespace Nodes {

template <typename KeyT> // TODO внутрь класса
class Node {
public:
    KeyT key;

    Node<KeyT>* parent;
    Node<KeyT>* left;
    Node<KeyT>* right;

    bool is_red;

    Node(KeyT key) : key(key), parent(nullptr), left(nullptr), right(nullptr), is_red(false) {}
    
    Node(KeyT key, Node<KeyT>* parent, Node<KeyT>* left, Node<KeyT>* right, bool is_red)
        : key(key), parent(parent), left(left), right(right), is_red(is_red) {}

    ~Node() = default;
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = default;
    Node& operator=(Node&&) = default;
};

} // namespace Nodes
