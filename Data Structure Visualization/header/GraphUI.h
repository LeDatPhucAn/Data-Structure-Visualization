#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h" // Assuming you have this class

class GraphUI : public SceneManager, public Graph {
protected:
    vector<RectButton*> CodeBlocks;
    vector<RectButton*> buttonsOnGraph;
public:
    GraphUI() : Graph(0) {
        init();
    }
    ~GraphUI() {
        Button::deleteButtons<RectButton>(buttonsOnGraph);
    }
    
    void init() override;
    void clearIndicatesAndHighlights() override {};
    void drawEdge();
    void initButtons() override;
    void updateButtonPositions() override {};
    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) {};

    void resetAnimations() {};

    void displayScene() override;
    void displaySceneInCamera() override;

    void drawGraph();
    //void drawNodeOnGraph(Node* node, Vector2 position);

};