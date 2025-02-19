#pragma once
#include "../header/Node.h"

template <typename T>
class LinkedListNode : public Node<T> {
public:
    LinkedListNode<T>* next;

    LinkedListNode(T value) : Node<T>(value), next(nullptr) {}
    ~LinkedListNode() override {
        delete next;dsds
    }
};