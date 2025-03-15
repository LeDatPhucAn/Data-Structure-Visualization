#pragma once
#include "SceneManager.h"
#include "Treap.h" 

class TreapUI : public SceneManager{
private: 
    Treap treap;
    TreapNode* root = nullptr;
    static const Vector2 ROOT_POS;
    const int xOffset = GetScreenWidth() / 2 - 20;
    const int yOffset = GetScreenHeight() / 5; 
    void drawTreapNode(TreapNode* curr, const Vector2 pos);
    void drawTreapLink(Edge* edge);
    void drawTreap(TreapNode* curr, Vector2 pos, const int xOffset, const int yOffset);
public:
    void insert(int key);
    void remove(int key);
    void search(int key);
    TreapUI();

    void drawTreap();

    void updateScene() override {
        // Implement the update logic for the treap scene
    }

    void displayScene() override {
        drawTreap();
        // Implement the display logic for the treap scene
    }
    void displaySceneInCamera() override {
        // Implement the display logic for the graph scene
    }

};