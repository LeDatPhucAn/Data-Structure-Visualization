#pragma once
#include "LinkedListNode.h"
//#include "Edge.h"
#include <vector>
class Edge;
class LinkedList : public LLNode {
public:
    LLNode* head;
    std::vector<Edge> Edges;
    LinkedList() : head(nullptr) {
        Edges.reserve(100);
    }
    ~LinkedList() {
        deletelist();
    }
    void addEdge(LLNode* from, LLNode* to);
    void removeEdge(LLNode* from, LLNode* to);
    void adjustPos(LLNode* head);
    bool remove(int x);
    void printlist();
    void deletelist();
    void insertnode(int x, int pos);
};

