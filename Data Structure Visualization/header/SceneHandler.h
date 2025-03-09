#pragma once
#include "SceneManager.h"
#include "Menu.h"
#include "HashTableUI.h"
#include "TreapUI.h"
#include "GraphUI.h"
#include "SinglyLinkedListUI.h"

class SceneHandler {
private:
    SceneManager* scenes[5];
public:
    SceneManager* currentSceneObject;
    SceneHandler() {
        scenes[MENU] = new Menu();
        scenes[LINKEDLIST] = new SinglyLinkedListUI();
        scenes[HASHTABLE] = new HashTableUI();
        scenes[TREAP] = new TreapUI();
        scenes[GRAPH] = new GraphUI();
        // Initialize other scenes as needed
        currentSceneObject = nullptr;
    }

    ~SceneHandler() {
        for (int i = 0; i < 5; ++i) {
            delete scenes[i];
        }
    }

    int getCurrentScene() {
        return currentSceneObject->CurrentScene;
    }
    void changeScene(Scene newScene) {
        currentSceneObject = scenes[newScene];
        if (currentSceneObject) {
            currentSceneObject->CurrentScene = newScene;
        }
    }

    void updateCurrentScene() {
        if (currentSceneObject) {
            currentSceneObject->updateScene();
        }
    }

    void displayCurrentScene() {
        if (currentSceneObject) {
            currentSceneObject->displayScene();
        }
    }
};