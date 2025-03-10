#pragma once
#include "SceneManager.h"
#include "Treap.h" // Assuming you have this class

class TreapUI : public SceneManager, public Treap {
public:
    TreapUI() {
        // Default constructor
        std::cout << "TreapUI Scene Created" << std::endl;
    }
    void updateScene() override {
        // Implement the update logic for the treap scene
    }

    void displayScene() override {
        // Implement the display logic for the treap scene
    }
};