#pragma once
#include "Node.h"
#include "Button.h"
#include <queue>
#include <stack>
class LLNode : public NumberInputCircleInCamera {
public:
    LLNode* next;
    queue<Animation*> animQueue;
    stack<Animation*> animStack;
    ~LLNode() {
        while (!animQueue.empty()) {
            delete animQueue.front();
            animQueue.pop();
        }
        while (!animStack.empty()) {
            delete animStack.top();
            animQueue.pop();
        }
    }
    LLNode() : NumberInputCircleInCamera(3), next(nullptr) {}
    LLNode(int value);
    LLNode(int value, Vector2 pos);
    LLNode(int value, Vector2 pos, int r);
    LLNode(int value, float X, float Y);
    LLNode(int value, float X, float Y, int r);
};