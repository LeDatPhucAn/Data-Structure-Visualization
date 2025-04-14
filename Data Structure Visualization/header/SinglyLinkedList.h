#pragma once
#include "LLNode.h"
#include "Edge.h"
#include <vector>
#include <memory>
#include "AnimationManager.h"

class LinkedList : public LLNode {
public:
    LLNode* head;
    vector<CBEdge*> Edges;
    LinkedList() : head(nullptr) {
        Edges.reserve(100);
    }
    ~LinkedList() {
        clear();
    }
    void clearIndicates();
    void adjustPos(LLNode* head);
    void adjustPosWithAnim(AnimationManager& animManager, LLNode* head);
    void adjustPosWithAnim2(AnimationManager& animManager, LLNode* head);
    void insertnode(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x, int pos);
    void randominsert(int x, int pos);
    void loadFromFile();
    bool remove(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);
    int getListSize();
    bool randomremove(AnimationManager &animManager, int x, int pos);
    bool search(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);
    void printlist();
    void deletelist();
    void deleteEdges();
    void clear();
};

