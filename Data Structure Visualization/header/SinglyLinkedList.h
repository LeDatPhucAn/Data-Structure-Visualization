#pragma once
#include "LinkedListNode.h"
#include "Edge.h"
#include <vector>

class LinkedList : public LLNode {
public:
    LLNode* head;
    static std::vector<Edge*> Edges;
    LinkedList() : head(nullptr) {
        Edges.reserve(100);
    }
    ~LinkedList() {
        deletelist();
        deleteEdges();
    }
    void adjustPos(LLNode* head);
    void insertnode(int x, int pos);
    bool remove(int x);
    bool search(int x);
    void printlist();
    void deletelist();
    void deleteEdges();
};

