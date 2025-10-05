#pragma once

#include <memory>

template <typename KeyT>
class Node {
public:
    KeyT key;

    Node<KeyT>* parent;
    Node<KeyT>* left;
    Node<KeyT>* right;

    bool is_red;

    Node(KeyT key) : key(key), parent(nullptr), left(nullptr), right(nullptr), is_red(false) {}
};
