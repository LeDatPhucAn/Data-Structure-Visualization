#pragma once
#include "SinglyLinkedList.h"
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"

class SinglyLinkedListUI : public SceneManager {
private:
protected:
    LinkedList linkedlist;
    vector<RectButton*> Buttons;
    vector<RectButton*> CodeBlocks;
    vector<CircleButton*> Circles;
public:
    SinglyLinkedListUI() {
        init();
    }
    ~SinglyLinkedListUI() {
        Button::deleteButtons<RectButton>(Buttons);
        Button::deleteButtons<RectButton>(CodeBlocks);
        Button::deleteButtons<CircleButton>(Circles);
    }


    void drawlinkedlist();
    void insert(int x, int pos);
    void remove(int x);
    bool search(int x);
    void init() override;
    void initButtons() override;
	void resetAnimations() override;
    void updateButtonPositions() override;
    void displayScene() override;
    void displaySceneInCamera() override;
    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) override;
};


