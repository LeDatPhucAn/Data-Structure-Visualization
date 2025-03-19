#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Treap.h" 
#include "Button.h"
#include "UI.h"
#include "tinyfiledialogs.h"
#include <fstream>
#include <string>
#include <sstream>

class TreapUI : public SceneManager {
private:
    Treap treap;
    TreapNode* root = nullptr;
    vector<Button*>Buttons;
    vector<Button*>CodeBlocks;
    static const Vector2 ROOT_POS;
    const int xOffset = UI::screenWidth / 2 - 20;
    const int yOffset = UI::screenHeight / 5;
    void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);
    void drawTreapNode(TreapNode* curr);
    void drawTreapLink(Edge* edge);
    void drawTreap(TreapNode* curr);
    void deleteButtons();
public:
    void insert(int key, int priority = rand());
    void loadFromFile();
    void remove(int key);
    void search(int key);
    void clear();

    TreapUI();
    ~TreapUI() {
        Button::deleteButtons(Buttons);
        Button::deleteButtons(CodeBlocks);
    }
    void init() override;
    void initButtons() override;
    void updateButtonPositions() override;

    void updateScene() override;
    void displayScene() override;

    void displaySceneInCamera() override {
        // Implement the display logic for treap in camera scene
        drawTreap(root);
    }

};