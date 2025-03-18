#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h" // Assuming you have this class

class GraphUI : public SceneManager {
protected:
   
    vector<Button*> buttonsOnGraph;
public:
    GraphUI() {
       
    }

    
    void init() override;
    void drawEdge();
    void initButtons() override {};
    void updateButtonPositions() override {};
    void updateScene() override;

    void displayScene() override;
    void displaySceneInCamera() override {
        // Implement the display logic for the graph scene
    }
    ~GraphUI() {}

};