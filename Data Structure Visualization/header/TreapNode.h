#pragma once

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
};

