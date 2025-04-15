#pragma once
#include "LLNode.h"
#include "Edge.h"
#include <vector>
#include "AnimationManager.h"
using namespace std;

class HashTable {
public:
    vector<LLNode*> buckets;
    static vector<CBEdge*> Edges;
    AnimationManager animManager;
    int bucketCount;

    HashTable(int size = 5);
    ~HashTable();

    void adjustPos(LLNode* head, int bucketIdx);
    void adjustPosWithAnim(AnimationManager& animManager, LLNode* head, int bucketIdx);
    void insertNode(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);
    void randomInsert(int x);
    bool remove(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);
    bool removeFromBucket(int x, int bucketIdx);
    bool search(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);
    void clear();
    void clearIndicates();
    void resize(int newSize);
    void loadFromFile(vector<RectButton*>& CodeBlocks, AnimationManager& animManager);
    int hashFunction(int x) { return x % bucketCount; }
    void deleteEdges();
};
