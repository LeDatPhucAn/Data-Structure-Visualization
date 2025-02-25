#pragma once

#include <cstdlib>

class TreapNode {
public:
    int data;
    int priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int data) : data(data), priority(rand()), left(nullptr), right(nullptr) {};
    ~TreapNode() {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }
private:
    void detachLeft();
    void detachRight();
    void attachLeft(TreapNode* node);
    void attachRight(TreapNode* node);
public:
    void drawNode(TreapNode* node, int x, int y, int xOffset, int yOffset);
};


