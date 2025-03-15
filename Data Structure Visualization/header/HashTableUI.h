#pragma once
#include "SceneManager.h"
#include "HashTable.h" // Assuming you have this class
class SceneHandler;
class HashTableUI : public SceneManager, public HashTable {
private:
    static constexpr int startX = 100;
    static constexpr int startY = 200;
    static constexpr int Width = 100;
    static constexpr int Height = 80;
    static constexpr int nodeRadius = 30;
    static constexpr int spacing = 20;
protected:
    SceneHandler* scenehandler;
public:
    HashTableUI() {
        // Default constructor
        std::cout << "HashTableUI Scene Created" << std::endl;
    }
    HashTableUI(SceneHandler* handler);
    void init();
    void drawHashTable();
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
