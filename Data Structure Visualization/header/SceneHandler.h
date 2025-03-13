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
    int framesCounter;
    string inputText;
    int letterCount = 0;
    int MAX_INPUT_CHARS = 10;
    bool Texting = false;
    static constexpr float TextBoxWidth = 240.0f;
    static constexpr float TextBoxHeight = 80.0f;
protected:
    SceneManager* currentSceneObject;
public:
    Rectangle BacktoMenu;
    Rectangle TextBox;
    Color BacktoMenuColor = LIGHTGRAY;
    Color TextBoxLinesColor = DARKGRAY;
    SceneHandler();
    ~SceneHandler();
    int getCurrentScene();
    void updateCamera();
    void updateCollision();
    void changeScene(Scene newScene);
    void drawButtontoMenu(float X, float Y);
    void updateCurrentScene();
    void displayCurrentScene();
};
