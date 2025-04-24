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
    vector<RectButton*>Buttons;
    vector<RectButton*>CodeBlocks;
    vector<TreapNode*> trashbin;

    Treap treap;
    TreapNode* root = nullptr;
    bool drawInsideTreap = false;
    static const Vector2 ROOT_POS;
    const int xOffset = UI::screenWidth / 2 - 20;
    const int yOffset = UI::screenHeight / 8;

    TreapNode* rotateLeft(TreapNode* root);
    TreapNode* rotateRight(TreapNode* root);
    TreapNode* search(TreapNode* root, int key);
    TreapNode* searchForNode(int key);
    void clear(TreapNode* root);

    TreapNode* rotateLeftAtSpecificNode(TreapNode* curr, int key);
    TreapNode* rotateRightAtSpecificNode(TreapNode* curr, int key);
    TreapNode* removeSpecificNode(TreapNode* curr, int key);

    TreapNode* insertBST(TreapNode* root, int key, int priority);
    void makeNewNodeAppear(TreapNode* curr, int key, stack<int>& visited);
    void fixViolation(stack<int>& visited);

    void getNodesToMove(vector<TreapNode*>& res, TreapNode* curr);

    bool searchBeforeRemove(TreapNode* curr, int key);
    void makeNodeDisappear(TreapNode* curr, int key);
    void makeNodeDisappearWithAnimation(TreapNode* curr, int key);

    void insertWithAnimation(int key, int priority);
    void searchWithAnimation(TreapNode* curr, int key); 
    void removeWithAnimation(int key);

    int getSubtreeWidth(TreapNode* curr);
    void updateSubtreeWidth(TreapNode* curr);
    void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);

    TreapNode* cloneTree(TreapNode* root);

    void unhighlightAllCodeBlocks();

    void drawTreapNode(TreapNode* curr);
    void drawTreapEdge(TreapEdge* edge);
    void drawTreap(TreapNode* curr);

    void cleanupForOperations();

public:
    void loadFromFile();
    void insert(int key, int priority = rand(), bool isAnimated = true);
    void remove(int key);
    void search(int key);
    void clear();

    TreapUI();
    ~TreapUI() {
        Button::deleteButtons<RectButton>(Buttons);
        Button::deleteButtons<RectButton>(CodeBlocks);
        treap.clear();
        clear();
        for (TreapNode* curr : trashbin) {
            clear(curr);
        }
    }
    void init() override;
    void initButtons() override;
    void updateButtonPositions() override;

    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) {};

    void displayScene() override;
    void resetAnimations() {};
    void clearIndicatesAndHighlights() override {};

    void displaySceneInCamera() override {
        // Implement the display logic for treap in camera scene
        if(drawInsideTreap) treap.drawTreap(treap.root);
        else drawTreap(root);
    }

};