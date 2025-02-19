#pragma once
#include "Node.h"

template <typename T>
class TreapNode : public Node<T> {
public:
    int priority;
    TreapNode<T>* left;
    TreapNode<T>* right;

    TreapNode(T value) : Node<T>(value), priority(rand()), left(nullptr), right(nullptr) {}
    ~TreapNode() override {
        delete left;
        delete right;
    }
};
