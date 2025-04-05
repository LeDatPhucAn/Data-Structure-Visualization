#pragma once
#include "HashTable.h"
#include "SceneManager.h"
#include "Button.h"
using namespace std;
class HashTableUI : public SceneManager {
private:
    HashTable hashtable;
    vector<RectButton*> Buttons;
    vector<RectButton*> CodeBlocks;
    HashTableNode* selectedNode = nullptr;
    int selectedBucketIdx = -1;

protected:
    void drawHashTable();

public:
    HashTableUI() { init(); }
    ~HashTableUI() {
        Button::deleteButtons<RectButton>(Buttons);
        Button::deleteButtons<RectButton>(CodeBlocks);
    }

    void insert(int x);
    void remove(int x);
    bool search(int x);
    void resize(int newSize);

    void init() override;
    void initButtons() override;
    void resetAnimations() override;
    void updateButtonPositions() override;
    void displayScene() override;
    void displaySceneInCamera() override;
    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) override;
};
