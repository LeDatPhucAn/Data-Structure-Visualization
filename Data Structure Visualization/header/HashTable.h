#pragma once
#include <vector>
#include <iostream>
class HashTable {
protected:
    std::vector<std::vector<int>> data;
    int size;

public:
    HashTable() {
        // Default constructor
        std::cout << "HashTable Created" << std::endl;
    };
    HashTable(int s);
    void insertHashTable(int value);
    bool findHashTable(int value);
    void deleteHashTable(int value);
    void display();
};