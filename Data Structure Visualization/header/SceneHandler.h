#pragma once
#include "SceneManager.h"
#include "Menu.h"
#include "HashTableUI.h"
#include "TreapUI.h"
#include "GraphUI.h"
#include "SinglyLinkedListUI.h"
#include "Button.h"
class SceneHandler : public UI {
private:
    SceneManager* scenes[5];
    Camera2D camera = { 0 };
protected:
    SceneManager* currentSceneObject;
public:
    SceneHandler();
    ~SceneHandler();
    int getCurrentScene();
    void updateCamera();
    void changeScene(Scene newScene);
    void updateCurrentScene();
    void displayCurrentScene();
};
