#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Treap.h" 
#include "Button.h"

class TreapUI : public SceneManager {
private:
    Treap treap;
    TreapNode* root = nullptr;

    SceneHandler* sceneHandler;
    static const Vector2 ROOT_POS;
    const int xOffset = GetScreenWidth() / 2 - 20;
    const int yOffset = GetScreenHeight() / 5;
    void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);
    void drawTreapNode(TreapNode* curr);
    void drawTreapLink(Edge* edge);
    void drawTreap(TreapNode* curr);
    void init();
public:
    void insert(int key);
    void remove(int key);
    void search(int key);
    TreapUI(SceneHandler* handler);
    ~TreapUI(){
        delete root;
    }

    void updateScene() override {
        // Implement the update logic for the treap scene
    }

    void displayScene() override {
        // insert(10);
        // insert(20);
        // insert(30);
        // insert(55);
        // insert(77);
        //drawTreap(root, ROOT_POS, xOffset, yOffset);
        // Implement the display logic for the treap scene
    }
    void displaySceneInCamera() override {
        // Implement the display logic for the graph scene
        //drawTreap(root, ROOT_POS, xOffset, yOffset);
        drawTreap(root);
    }

};