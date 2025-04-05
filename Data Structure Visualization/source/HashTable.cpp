#include "../header/HashTable.h"
#include "../header/Animation.h"
using namespace std;
vector<CBEdge*> HashTable::Edges;

HashTable::HashTable(int size) : bucketCount(size) {
    buckets.resize(size, nullptr);
    Edges.reserve(100);
}

HashTable::~HashTable() {
    clear();
}

void HashTable::adjustPos(LLNode* head, int bucketIdx) {
    LLNode* prev = nullptr;
    float startX = 100 + bucketIdx * 200;
    float startY = 200;
    while (head) {
        if (!prev) {
            head->setCenter(startX, startY);
        }
        else {
            head->setCenterY(prev->getCenterY() + 150);
            head->setCenterX(startX);
        }
        prev = head;
        head = head->next;
    }
}

void HashTable::insertNode(int x) {
    int idx = hashFunction(x);
    LLNode* newNode = new LLNode(x, 100 + idx * 200, 200);

    if (!buckets[idx]) {
        buckets[idx] = newNode;
    }
    else {
        LLNode* cur = buckets[idx];
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
        CBEdge::addEdge(Edges, cur, newNode);
    }
    adjustPos(buckets[idx], idx);
}

void HashTable::randomInsert(int x) {
    int idx = hashFunction(x);
    LLNode* newNode = new LLNode(x, 100 + idx * 200, 200);

    if (!buckets[idx]) {
        buckets[idx] = newNode;
    }
    else {
        LLNode* cur = buckets[idx];
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
        CBEdge::addEdge(Edges, cur, newNode);
    }
    adjustPos(buckets[idx], idx);
}

bool HashTable::remove(int x) {
    int idx = hashFunction(x);
    return removeFromBucket(x, idx);
}

bool HashTable::removeFromBucket(int x, int bucketIdx) {
    LLNode* cur = buckets[bucketIdx];
    if (!cur) return false;

    if (cur->getNumber() == x) {
        buckets[bucketIdx] = cur->next;
        CBEdge::removeEdge(Edges, cur, cur->next);
        delete cur;
        adjustPos(buckets[bucketIdx], bucketIdx);
        return true;
    }

    while (cur->next) {
        if (cur->next->getNumber() == x) {
            LLNode* temp = cur->next;
            CBEdge::removeEdge(Edges, cur, temp);
            CBEdge::removeEdge(Edges, temp, temp->next);
            cur->next = temp->next;
            CBEdge::addEdge(Edges, cur, cur->next);
            delete temp;
            adjustPos(buckets[bucketIdx], bucketIdx);
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool HashTable::search(int x) {
    int idx = hashFunction(x);
    LLNode* cur = buckets[idx];
    while (cur) {
        if (cur->getNumber() == x) return true;
        cur = cur->next;
    }
    return false;
}

void HashTable::clear() {
    for (int i = 0; i < bucketCount; i++) {
        while (buckets[i]) {
            LLNode* temp = buckets[i];
            buckets[i] = buckets[i]->next;
            delete temp;
        }
    }
    deleteEdges();
}

void HashTable::resize(int newSize) {
    vector<LLNode*> oldBuckets = buckets;
    int oldSize = bucketCount;
    bucketCount = newSize;
    buckets.clear();
    buckets.resize(newSize, nullptr);
    deleteEdges();

    for (int i = 0; i < oldSize; i++) {
        LLNode* cur = oldBuckets[i];
        while (cur) {
            LLNode* next = cur->next;
            cur->next = nullptr;
            insertNode(cur->getNumber());
            cur = next;
        }
    }
    for (int i = 0; i < oldSize; i++) {
        delete oldBuckets[i];
    }
}

void HashTable::deleteEdges() {
    for (auto edge : Edges) {
        delete edge;
    }
    Edges.clear();
}
