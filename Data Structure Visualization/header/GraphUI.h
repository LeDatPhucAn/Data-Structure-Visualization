#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h" // Assuming you have this class

class GraphUI : public SceneManager, public Graph {
protected:
    vector<Button*> CodeBlocks;
    vector<Button*> buttonsOnGraph;
public:
    GraphUI() : Graph(0) {
        init();
    }

    
    void init() override;
    void drawEdge();
    void initButtons() override;
    void updateButtonPositions() override {};
    void updateScene() override;

    void displayScene() override;
    void displaySceneInCamera() override;

    void drawGraph();
    //void drawNodeOnGraph(Node* node, Vector2 position);
    ~GraphUI() {}

};