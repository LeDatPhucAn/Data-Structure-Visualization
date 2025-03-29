#pragma once
#include "SinglyLinkedList.h"
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"

class SinglyLinkedListUI : public LinkedList, public SceneManager {
private:
    static constexpr int headX = 100;
    static constexpr int headY = 450;
    static constexpr int radius = 50;
protected:
    vector<Button*> Buttons;
    vector<Button*> CodeBlocks;
public:
    SinglyLinkedListUI() {
        init();
    }
    ~SinglyLinkedListUI() {
        Button::deleteButtons(Buttons);
        Button::deleteButtons(CodeBlocks);
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


