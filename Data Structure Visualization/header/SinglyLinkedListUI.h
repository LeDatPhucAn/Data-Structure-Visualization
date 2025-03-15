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
    SceneHandler* scenehandler;
    vector<Button*> Buttons;
public:
    SinglyLinkedListUI() {
        init();
    }
    SinglyLinkedListUI(SceneHandler* handler) : scenehandler(handler) {
        init();
    }
    ~SinglyLinkedListUI() {
        deleteButtons();
    }
    void init();
    void deleteButtons();
    void drawlinkedlist();
    void displayScene() override;
    void displaySceneInCamera() override;
    void updateScene() override;
};


