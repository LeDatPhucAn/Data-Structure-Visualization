#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Treap.h" 
#include "Button.h"
#include "UI.h"

class TreapUI : public SceneManager {
private:
    Treap treap;
    TreapNode* root = nullptr;
    vector<Button*>Buttons;
    SceneHandler* sceneHandler;
    static const Vector2 ROOT_POS;
    const int xOffset = UI::screenWidth / 2 - 20;
    const int yOffset = UI::screenHeight / 5;
    void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);
    void drawTreapNode(TreapNode* curr);
    void drawTreapLink(Edge* edge);
    void drawTreap(TreapNode* curr);
    void init();
    void deleteButtons();
public:
    void insert(int key, int priority = rand());
    void remove(int key);
    void search(int key);

    TreapUI(SceneHandler* handler);

    ~TreapUI() {
        deleteButtons();
    }


    void updateScene() override {
        // Implement the update logic for the treap scene
        Button::isCollision = false;
        for (auto button : Buttons) {
            button->update();
        }
        if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    void displayScene() override {
        // Implement the display logic for the treap scene
        for (auto button : Buttons) {
            button->draw();
        }
    }
    void displaySceneInCamera() override {
        // Implement the display logic for the graph scene
        drawTreap(root);
    }

};