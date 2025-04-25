#pragma once
#include "LLNode.h"
#include "Edge.h"
#include <vector>
#include "AnimationManager.h"
#include <unordered_set>
using namespace std;

class HashTable {
public:
    vector<LLNode*> buckets;
    static vector<CBEdge*> Edges;
    int bucketCount;
    unordered_set<LLNode*> deleteLater;

    HashTable(int size = 5);
    ~HashTable();

    void adjustPos(LLNode* head, int bucketIdx);
    void adjustPosWithAnim(AnimationManager& animManager, LLNode* head, int bucketIdx);
    void insertNode(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x, int& pos);
    void randomInsert(int x, int pos);
    bool remove(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x,int& pos);
    bool removeFromBucket(int x, int bucketIdx);
    bool search(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x);
    void clear();
    void clearIndicates();
    void resize(int newSize);
    void loadFromFile(vector<RectButton*>& CodeBlocks, AnimationManager& animManager);
    int hashFunction(int x) { return x % bucketCount; }
    void deleteEdges();
    void restoreAfterInsert(int x, int pos);
    vector<int> collectValues();
};
