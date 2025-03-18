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
    Camera2D camera = { 
        .offset = {static_cast<float> (UI::screenWidth) / 2, static_cast<float> (UI::screenHeight) / 5},  
        .target = { static_cast<float> (UI::screenWidth) / 2, 0 },
        .rotation = 0.0f,  
        .zoom = 0.0f
    };
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
