#pragma once
#include "Node.h"

class LLNode : public Node {
public:
    LLNode* next;
    LLNode() : Node(0,{0,0},50), next(nullptr) {}
    LLNode(int value) : Node(value,{0,0},50), next(nullptr) {}
    LLNode(int value, Vector2 pos) : Node(value, pos, 50), next(nullptr) {}
    LLNode(int value, float X, float Y) : Node(value, {X,Y}, 50), next(nullptr){}
    LLNode(int value, float X, float Y, int r) : Node(value,{X,Y},r), next(nullptr){}
    ~LLNode() override {

    }
};
