#pragma once
#include "LLNode.h"
#include "Edge.h"
#include <vector>
#include <memory>
#include "AnimationManager.h"
class LinkedList : public LLNode {
public:
    LLNode* head;
    static vector<CBEdge*> Edges;
    AnimationManager animManager;
    LinkedList() : head(nullptr) {
        Edges.reserve(100);
    }
    ~LinkedList() {
        clear();
    }
    void adjustPos(LLNode* head);
    void insertnode(int x, int pos);
    void randominsert(int x, int pos);
    void loadFromFile();
    bool remove(int x);
    bool search(int x);
    void printlist();
    void deletelist();
    void deleteEdges();
    void clear();
};

