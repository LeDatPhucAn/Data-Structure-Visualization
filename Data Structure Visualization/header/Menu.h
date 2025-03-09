#pragma once
#include "SceneManager.h"

class Menu : public SceneManager {
public:
    Menu() {
        // Default constructor
        std::cout << "Menu Scene Created" << std::endl;
    }
    void updateScene() override {
        // Implement the update logic for the menu
        std::cout << "Updating Menu Scene" << std::endl;
    }

    void displayScene() override;
};