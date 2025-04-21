#pragma once
#include "LLNode.h"
#include "Edge.h"
#include <vector>
#include <memory>
#include "AnimationManager.h"
#include <unordered_set>
class LinkedList : public LLNode {
public:
    LLNode* head;
    vector<CBEdge*> Edges;
    LLNode* RemoveFirstNode = nullptr;
    unordered_set<LLNode*> deleteLater;
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

    void restoreAfterInsert(int x, int pos);

    void randominsert(int x, int pos);
    void loadFromFile();


    int remove(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);


    int getListSize();
    bool search(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);
    void printlist();
    void deletelist();
    void deleteEdges();
    void clear();
};

