#pragma once

#include <memory>

template <typename KeyT>
class Node {
public:
    KeyT key;

    Node* parent;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    bool is_red;

    Node(KeyT key) : key(key), parent(nullptr), left(nullptr), right(nullptr), is_red(false) {}
};
