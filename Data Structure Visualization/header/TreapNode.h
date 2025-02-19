#pragma once
#include "Node.h"

template <typename T>
class TreeNode : public Node<T> {
public:
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T value) : Node<T>(value), left(nullptr), right(nullptr) {}
    ~TreeNode() override {
        delete left;
        delete right;
    }
};
