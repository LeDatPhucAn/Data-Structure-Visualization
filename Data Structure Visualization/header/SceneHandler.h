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
    vector<Button*>SceneButtons;
    vector<RectButton*> rightSideButtons;
    SceneManager* scenes[5];
    Camera2D camera = { 
        {static_cast<float> (UI::screenWidth) / 2, static_cast<float> (UI::screenHeight) / 5},  
        { static_cast<float> (UI::screenWidth) / 2, 0 },
        0.0f,  
        0.0f
    };
protected:
public:
    SceneManager* currentSceneObject;
    static Vector2 mouseWorldPos;
    SceneHandler();
    ~SceneHandler();
    int getCurrentScene();
    void initButtons();
    void updateCamera();
    void changeScene(Scene newScene);
    void updateCurrentScene();
    void displayCurrentScene();
};
