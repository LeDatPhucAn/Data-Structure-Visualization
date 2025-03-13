#pragma once
#include "SceneManager.h"
#include "Treap.h" // Assuming you have this class

class TreapUI : public SceneManager, public Treap {
private: 
    const Vector2 rootPos = {GetScreenWidth() / 2, 20};
    const int xOffset = GetScreenWidth() / 2 - 20;
    const int yOffset = GetScreenHeight() / 5; 
    void drawTreapNode(TreapNode* curr, const Vector2 pos);
    void drawTreapLink(Vector2 startNodeCenter, Vector2 endNodeCenter, bool isLeftChild);
    void drawTreap(TreapNode* curr, Vector2 pos, const int xOffset, const int yOffset);
public:
    TreapUI() = default;

    void drawTreap();

    void updateScene() override {
        // Implement the update logic for the treap scene
    }

    void displayScene() override {
        // Implement the display logic for the treap scene
    }
};