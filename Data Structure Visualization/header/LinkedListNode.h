#pragma once
#include "Node.h"

class LLNode : public Node {
public:
    LLNode* next;
    LLNode() : Node(0), next(nullptr) {}
    LLNode(int value) : Node(value), next(nullptr) {}
    ~LLNode() override {

    }
};
