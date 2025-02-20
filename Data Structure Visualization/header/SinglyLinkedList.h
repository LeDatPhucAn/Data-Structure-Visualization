#pragma once
#include "LinkedListNode.h"

class LinkedList : public LLNode {
public:
    LLNode* head;
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        deletelist();
    }
    bool remove(int x);
    void printlist();
    void deletelist();
    void insertnode(int x, int pos);
};

