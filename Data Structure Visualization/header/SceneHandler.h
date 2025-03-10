#pragma once
#include "SceneManager.h"
#include "Menu.h"
#include "HashTableUI.h"
#include "TreapUI.h"
#include "GraphUI.h"
#include "SinglyLinkedListUI.h"

class SceneHandler : public UI {
private:
    SceneManager* scenes[5];
    Camera2D camera = { 0 };
protected:
    SceneManager* currentSceneObject;
public:
    Rectangle BacktoMenu;
    Color BacktoMenuColor = LIGHTGRAY;
    SceneHandler();
    ~SceneHandler();
    int getCurrentScene();
    void changeScene(Scene newScene);
    void drawButtontoMenu(float X, float Y);
    void updateCurrentScene();
    void displayCurrentScene();
};
