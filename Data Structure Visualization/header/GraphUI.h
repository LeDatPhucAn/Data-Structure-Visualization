#pragma once
#include "SceneManager.h"
#include "Graph.h" // Assuming you have this class

class GraphUI : public SceneManager {
public:
    GraphUI() {
        // Default constructor
        std::cout << "GraphUI Scene Created" << std::endl;
    }

    
    void init() override;
    void drawEdge();
    void initButtons() override;
    void updateButtonPositions() override {};
    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) {};

    void resetAnimations() {};

    void displayScene() override;
    void displaySceneInCamera() override;

    void updateScene() override {
        // Implement the update logic for the graph scene
    }

    void displayScene() override {
        // Implement the display logic for the graph scene
    }
    void displaySceneInCamera() override {
        // Implement the display logic for the graph scene
    }
    
};