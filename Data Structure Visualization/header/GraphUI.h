#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h"

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
    void Dijkstra(int n);
    void DijkstraTable();
    void init() override;
    void clearIndicatesAndHighlights() override {};
    void drawEdge();
    void initButtons() override;
    void updateButtonPositions() override;
    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) override {};
    void resetAnimations() override;
    void displayScene() override;
    void displaySceneInCamera() override;
    void drawGraph();
    //void drawNodeOnGraph(Node* node, Vector2 position);

};