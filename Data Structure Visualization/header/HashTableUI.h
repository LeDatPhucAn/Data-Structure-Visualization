#pragma once
#include "SceneManager.h"
#include "HashTable.h" // Assuming you have this class

class HashTableUI : public SceneManager, public HashTable {
public:
    HashTableUI() {
        // Default constructor
        std::cout << "HashTableUI Scene Created" << std::endl;
    }
    void updateScene() override {
        // Implement the update logic for the hash table scene
    }

    void displayScene() override {
        // Implement the display logic for the hash table scene
    }
    void displaySceneInCamera() override {
        // Implement the display logic for the graph scene
    }

};