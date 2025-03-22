#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h" // Assuming you have this class

class GraphUI : public SceneManager {

protected:
    vector<Button*> CodeBlocks;
    vector<Button*> buttonsOnGraph;

    Graph* graph = nullptr;
public:
    GraphUI() {
        graph = new Graph();
        init();
    }
    GraphUI(Graph* g) : graph(g) {
        init();
    }

    void init() override;
    void initButtons() override;
    void updateButtonPositions() override {};
    void updateScene() override;
    void resetAnimations() {};

    void displayScene() override;
    void displaySceneInCamera() override;

    void drawGraph();
    //void drawNodeOnGraph(Node* node, Vector2 position);
    ~GraphUI() {
        delete graph;
        for (Button* btn : buttonsOnGraph) delete btn;
        buttonsOnGraph.clear();
        for (Button* codeBlock : CodeBlocks) delete codeBlock;
        CodeBlocks.clear();
    }
    void clear();

};