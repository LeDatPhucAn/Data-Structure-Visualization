#pragma once
#include "Node.h"
#include "Button.h"

class LLNode : public NumberInputCircleInCamera {
public:
    LLNode* next;
    LLNode() : NumberInputCircleInCamera(3), next(nullptr) {}
    LLNode(int value);
    LLNode(int value, Vector2 pos);
    LLNode(int value, Vector2 pos, int r);
    LLNode(int value, float X, float Y);
    LLNode(int value, float X, float Y, int r);
};