#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Button.h"
#include "Graph.h"

class GraphUI : public SceneManager {

protected:
    bool hidden = false;
    vector<RectButton*> CodeBlocks;
    vector<RectButton*> buttonsOnGraph;
    int dijkstraParameters;
    int tableDijkParameters;
	int HighlightTableParameters;
    Graph* graph = nullptr;
public:
	static bool isDijkstra;
	static bool isDijkstraTable;
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
    void cleanUpForOperation() {
        animManager.goToLastStep();
        animManager.clear();
        animManager.resume();
    }
    void replayOperation() override;
    void Dijkstra(int n);
    void DijkstraTable();
    void init() override;

    void clearIndicatesAndHighlights() override {};
    
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