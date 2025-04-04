#pragma once
#include "SceneManager.h"
#include "HashTable.h"
#include "SceneHandler.h"
#include "Button.h"
#include <vector>

class HashTableUI : public SceneManager, public HashTable {
private:
    static constexpr int startX = 100;
    static constexpr int startY = 200;
    static constexpr int Width = 100;
    static constexpr int Height = 80;
    static constexpr int nodeRadius = 30;
    static constexpr int spacing = 20;

protected:
    std::vector<RectButton*> Buttons;
    std::vector<RectButton*> CodeBlocks;

public:
    HashTableUI() : HashTable(5) {
        init();
    }
    ~HashTableUI() {
        Button::deleteButtons<RectButton>(Buttons);
        Button::deleteButtons<RectButton>(CodeBlocks);
    }

    void init() override;
    void initButtons() override;
    void resetAnimations() override;
    void updateButtonPositions() override;
    void drawHashTable();

    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) override {};
    void displayScene() override;
    void displaySceneInCamera() override;
};