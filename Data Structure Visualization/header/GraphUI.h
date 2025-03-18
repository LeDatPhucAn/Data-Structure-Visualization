#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h" // Assuming you have this class

class GraphUI : public SceneManager {
protected:
    SceneHandler* scenehandler;
    vector<Button*> buttonsOnGraph;
public:
    GraphUI() {
        init();
        // Default constructor
        std::cout << "GraphUI Scene Created" << std::endl;
    }
    GraphUI(SceneHandler* handler) : scenehandler(handler) {
        init();
    }
    void init();
    void drawEdge();
    void updateScene() override;

    void displayScene() override;
    void displaySceneInCamera() override {
        // Implement the display logic for the graph scene
    }
    ~GraphUI() {}
};