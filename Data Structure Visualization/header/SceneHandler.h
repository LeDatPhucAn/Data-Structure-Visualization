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
        {static_cast<float> (UI::screenWidth) / 2, static_cast<float> (UI::screenHeight) / 5},  
        { static_cast<float> (UI::screenWidth) / 2, 0 },
        0.0f,  
        0.0f
    };
protected:
    SceneManager* currentSceneObject;
public:
    static Vector2 mouseWorldPos;
    static RectButton* MenuButton;
    SceneHandler();
    ~SceneHandler();
    int getCurrentScene();
    void updateCamera();
    void changeScene(Scene newScene);
    void updateCurrentScene();
    void displayCurrentScene();
};
