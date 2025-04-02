#pragma once
#include "SinglyLinkedList.h"
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"

class SinglyLinkedListUI : public LinkedList, public SceneManager {
private:
protected:
    vector<RectButton*> Buttons;
    vector<RectButton*> CodeBlocks;
    vector<CircleButton*> Circles;
    vector<Animation*> animations;
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

    void init() override;
    void initButtons() override;
	void resetAnimations() override;
    void updateButtonPositions() override;
    void displayScene() override;
    void displaySceneInCamera() override;
    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) override;
};


