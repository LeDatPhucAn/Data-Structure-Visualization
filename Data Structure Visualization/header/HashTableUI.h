#pragma once
#include "SceneManager.h"
#include "HashTable.h" // Assuming you have this class
#include "SceneHandler.h"
#include "Button.h"
#include <vector>
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
    std::vector<Button*> Buttons;
    std::vector<Button*> CodeBlocks;
public:
    HashTableUI() : HashTable(5) {  // Initial size: 5
        init();
    }
    ~HashTableUI() {
        Button::deleteButtons(Buttons);
        Button::deleteButtons(CodeBlocks);
    }
    void init() override;
    void initButtons() override;
    void updateButtonPositions() override;
    void drawHashTable();

    void updateScene() override;

    void displayScene() override;
    void displaySceneInCamera() override;

};
