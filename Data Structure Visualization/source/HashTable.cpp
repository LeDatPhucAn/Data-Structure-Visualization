#include "HashTable.h"
#include <iostream>
using namespace std;
HashTable::HashTable(int s) {
    size = s;
    data.resize(size);
}

void HashTable::insertHashTable(int value) {
    int index = value % size;
    data[index].push_back(value);
}

bool HashTable::findHashTable(int value) {
    int index = value % size;
    for (int i = 0; i < data[index].size(); ++i) {
        if (data[index][i] == value) {
            return true;
        }
    }
    return false;
}

void HashTable::deleteHashTable(int value) {
    int index = value % size;
    for (auto it = data[index].begin(); it != data[index].end(); ++it) {
        if (*it == value) {
            data[index].erase(it);
            return;
        }
    }
}

void HashTable::display() {
    for (int i = 0; i < data.size(); ++i) {
        cout << "Bucket " << i << ": ";
        for (int j = 0; j < data[i].size(); ++j) {
            cout << data[i][j] << " ";
        }
        cout << std::endl;
    }
}
