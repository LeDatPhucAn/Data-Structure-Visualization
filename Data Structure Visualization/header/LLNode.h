#pragma once
#include "Node.h"
#include "Button.h"

class LLNode : public Node {
public:
    LLNode* next;
    NumberInputCircleInCamera* clickBox;

    LLNode();
    LLNode(int value);
    LLNode(int value, Vector2 pos);
    LLNode(int value, float X, float Y);
    LLNode(int value, float X, float Y, int r);
    ~LLNode() override;
};