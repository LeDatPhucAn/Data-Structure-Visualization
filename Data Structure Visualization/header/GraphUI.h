#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h" // Assuming you have this class

class GraphUI : public SceneManager {

protected:
    bool hidden = false;
    vector<RectButton*> CodeBlocks;
    vector<RectButton*> buttonsOnGraph;

    Graph* graph = nullptr;
public:
    GraphUI() {
        graph = new Graph();
        init();
    }
    GraphUI(Graph* g) : graph(g) {
        init();
    }
    ~GraphUI() {
        
        Button::deleteButtons<RectButton>(buttonsOnGraph);
        delete graph;
        for (Button* btn : buttonsOnGraph) delete btn;
        buttonsOnGraph.clear();
        for (Button* codeBlock : CodeBlocks) delete codeBlock;
        CodeBlocks.clear();
    }
    void Dijkstra(int n);
    void DijkstraTable();
    void init() override;

    void clearIndicatesAndHighlights() override {};
    void drawEdge() {};

    void initButtons() override;
    void updateButtonPositions() override;
    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) override {};
    void resetAnimations() override;
    void displayScene() override;
    void displaySceneInCamera() override;
    void drawGraph();
    //void drawNodeOnGraph(Node* node, Vector2 position);
   
    void setHidden();
    void clear();


};