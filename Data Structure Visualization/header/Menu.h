#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
typedef enum selected {
    NONE = -1,
    MENU_LINKEDLIST,
    MENU_HASHTABLE,
    MENU_TREAP,
    MENU_GRAPH
} Selected;
class SceneHandler;
class Menu : public SceneManager {
protected:
    static constexpr int spacing = 100;
    SceneHandler* sceneHandler = nullptr;
public:
    Selected selected;
    Rectangle sourceRec;
    Rectangle linkedlist;
    Rectangle hashtable;
    Rectangle treap;
    Rectangle graph;
    Rectangle rectangles[4];
    Menu() {
        selected = NONE;
    }
    Menu(SceneHandler* handler) : sceneHandler(handler) {
        selected = NONE;
    }
    void init() {};
    void initButtons() {};
    void updateButtonPositions() {};

    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) {};
    void clearIndicatesAndHighlights() override {} ;
    void displayScene() override;

    void resetAnimations() {};
    void displaySceneInCamera() {}
};