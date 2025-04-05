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
    void insertNode(int x);
    void randomInsert(int x);
    bool remove(int x);
    bool removeFromBucket(int x, int bucketIdx);
    bool search(int x);
    void clear();
    void resize(int newSize);
    int hashFunction(int x) { return x % bucketCount; }
    void deleteEdges();
};
