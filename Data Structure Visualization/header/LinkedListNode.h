#pragma once
#include "../header/Node.h"

template <typename T>
class LLNode : public Node<T> {
public:
    LLNode<T>* next;
    LLNode() : Node<T>(T()), next(nullptr) {}
    LLNode(T value) : Node<T>(value), next(nullptr) {}
    ~LLNode() override {

    }
};