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
#include <functional>

class TreapUI : public SceneManager {
private:
    //Treap treap;
    TreapNode* root = nullptr;
    vector<RectButton*>Buttons;
    vector<RectButton*>CodeBlocks;
    vector<TreapNode*> nodes;
    vector<TreapEdge*> edges;
    static const Vector2 ROOT_POS;
    const int xOffset = UI::screenWidth / 2 - 20;
    const int yOffset = UI::screenHeight / 8;
    TreapNode* rotateLeft(TreapNode* root);
    TreapNode* rotateLeftWithAnimation(TreapNode* root);
    TreapNode* rotateRight(TreapNode* root);
    TreapNode* rotateRightWithAnimation(TreapNode* root);
    int getSubtreeWidth(TreapNode* curr);
    void updateSubtreeWidth(TreapNode* curr);
    TreapNode* insert(TreapNode* root, Vector2 pos, int key, int priority);
    void searchWithAnimation(TreapNode* curr, int key);
    TreapNode* remove(TreapNode* root, int key);
    void clear(TreapNode* root);
    void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);
    void repositionWithAnimation(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);
    void drawTreapNode(TreapNode* curr);
    void drawTreapEdge(TreapEdge* edge);
    void drawTreap(TreapNode* curr);
public:
    void insert(int key, int priority = rand());
    void loadFromFile();
    void remove(int key);
    void search(int key);
    void clear();

    TreapUI();
    ~TreapUI() {
        Button::deleteButtons<RectButton>(Buttons);
        Button::deleteButtons<RectButton>(CodeBlocks);
    }
    void init() override;
    void initButtons() override;
    void updateButtonPositions() override;

    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) {};

    void displayScene() override;

    void displaySceneInCamera() override {
        // Implement the display logic for treap in camera scene
        drawTreap(root);
    }

};