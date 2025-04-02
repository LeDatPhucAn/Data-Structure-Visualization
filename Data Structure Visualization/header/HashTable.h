#pragma once
#include <vector>
#include <iostream>
#include "Node.h"
#include "Edge.h"
#include "Button.h"

class HashTable {
protected:
    std::vector<std::vector<Node*>> data;
    int size;
    static std::vector<Edge*> Edges;

public:
    HashTable() {
        std::cout << "HashTable Created" << std::endl;
    }
    HashTable(int s) : size(s) {
        data.resize(size);
        Edges.reserve(100);
    }
    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            for (auto node : data[i]) {
                delete node;
            }
            data[i].clear();
        }
        for (auto edge : Edges) {
            delete edge;
        }
        Edges.clear();
    }

    void insertHashTable(int value);
    bool findHashTable(int value);
    void deleteHashTable(int value);
    void display();
    void adjustPos(int bucketIndex);
    void deleteEdges();
};
