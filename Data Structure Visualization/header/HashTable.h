#pragma once
#include <vector>
class HashTable {
private:
    std::vector<std::vector<int>> data;
    int size;

public:
    HashTable(int s);
    void insertHashTable(int value);
    bool findHashTable(int value);
    void deleteHashTable(int value);
    void display();
};
