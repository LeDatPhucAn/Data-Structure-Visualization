#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Treap.h" 
#include "Button.h"
#include "UI.h"
#include "tinyfiledialogs.h"
#include "PseudoCode.h"
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

struct TreapStep {
    TreapNode* root; // Root of the treap at this step
    vector<TreapNode*> nodes; // All nodes in the treap at this step
    vector<TreapEdge*> edges; // All edges in the treap at this step
    vector<pair<int, pair<char, vector<Color>>>> highlightedNodes; // Highlighted nodes
    vector<pair<int, int>> highlightedEdges; // Highlighted edges
    vector<int> highlightedCodeLines; // Highlighted lines of code

    // Constructor
    TreapStep(TreapNode* r,
        vector<pair<int, pair<char, vector<Color>>>> n = {},
        vector<pair<int, int>> e = {},
        vector<int> c = {})
        : root(r), highlightedNodes(n), highlightedEdges(e), highlightedCodeLines(c) {
        if (root) {
            collectNodesAndEdges(root);
            applyHighlights();
        }
    }

    // Destructor
    ~TreapStep() {
        clear(root);
        highlightedNodes.clear();
        highlightedEdges.clear();
        for (auto ptr : nodes) delete ptr;
        nodes.clear();
        for (auto ptr : edges) delete ptr;
        edges.clear();
    }

    // Collect all nodes and edges in the tree
    void collectNodesAndEdges(TreapNode* curr) {
        if (!curr) return;

        nodes.push_back(curr);

        if (curr->leftEdge) {
            edges.push_back(curr->leftEdge);
            collectNodesAndEdges(curr->leftEdge->to);
        }

        if (curr->rightEdge) {
            edges.push_back(curr->rightEdge);
            collectNodesAndEdges(curr->rightEdge->to);
        }
    }

    // Apply highlights to nodes and edges
    void applyHighlights() {
        for (auto& p : highlightedNodes) {
            for (auto ptr : nodes) {
                if (ptr->getKey() == p.first) {
                    if (p.second.first == 'k') { // Highlight keyBox
                        ptr->keyBox->FillColor = p.second.second[0];
                        ptr->keyBox->OutLineColor = p.second.second[1];
                        ptr->keyBox->TextColor = p.second.second[2];
                    }
                    else { // Highlight priorityBox
                        ptr->priorityBox->FillColor = p.second.second[0];
                        ptr->priorityBox->OutLineColor = p.second.second[1];
                        ptr->priorityBox->TextColor = p.second.second[2];
                    }
                }
            }
        }

        for (auto& p : highlightedEdges) {
            for (auto ptr : edges) {
                if (ptr->from->getKey() == p.first && ptr->to->getKey() == p.second) {
                    ptr->edgeColor = ORANGE;
                }
            }
        }
    }

    // Clear the tree recursively
    void clear(TreapNode* curr) {
        if (!curr) return;

        if (curr->leftEdge) {
            clear(curr->leftEdge->to);
            delete curr->leftEdge;
        }
        if (curr->rightEdge) {
            clear(curr->rightEdge->to);
            delete curr->rightEdge;
        }

        delete curr;
    }

    // Draw a single node
    void drawTreapNode(TreapNode* curr) {
        if (!curr) return;
        curr->draw();
    }

    // Draw a single edge
    void drawTreapEdge(TreapEdge* edge) {
        if (!edge || !edge->from || !edge->to) return;
        edge->draw();
    }

    // Draw the entire treap
    void drawTreap(TreapNode* curr) {
        if (!curr) return;

        drawTreapNode(curr);

        if (curr->leftEdge) {
            drawTreapEdge(curr->leftEdge);
            drawTreap(curr->leftEdge->to);
        }

        if (curr->rightEdge) {
            drawTreapEdge(curr->rightEdge);
            drawTreap(curr->rightEdge->to);
        }
    }

    void draw() {
        drawTreap(root);
    }
};

class TreapUI : public SceneManager {
private:
    vector<CircleButton*> OverrideButtons;
    vector<RectButton*>Buttons;
    vector<RectButton*>CodeBlocks;
    vector<TreapNode*> trashbin;

    Treap treap;
    TreapNode* root = nullptr;
    vector<TreapStep*> steps;
    int currentStep = 0;
    bool drawInsideTreap = false;
    bool stepByStepAnimation = false;
    static const Vector2 ROOT_POS;
    const int xOffset = UI::screenWidth / 2 - 20;
    const int yOffset = UI::screenHeight / 8;

    TreapNode* rotateLeft(TreapNode* root);
    TreapNode* rotateRight(TreapNode* root);
    TreapNode* search(TreapNode* root, int key);
    TreapNode* searchForNode(int key);
    void clear(TreapNode* root);

    TreapNode* rotateLeftAtSpecificNode(TreapNode* curr, int key);
    TreapNode* rotateRightAtSpecificNode(TreapNode* curr, int key);
    TreapNode* removeSpecificNode(TreapNode* curr, int key);

    TreapNode* insertBST(TreapNode* root, int key, int priority);
    void makeNewNodeAppear(TreapNode* curr, int key, stack<int>& visited);
    void fixViolation(stack<int>& visited);

    void sbs_insertBST(TreapNode* root, int key, int priority, stack<int>& visited);
    void sbs_fixViolation(stack<int>& visited);

    void getNodesToMove(vector<TreapNode*>& res, TreapNode* curr);

    bool searchBeforeRemove(TreapNode* curr, int key);
    void makeNodeDisappear(TreapNode* curr, int key);
    void makeNodeDisappearWithAnimation(TreapNode* curr, int key);

    void insertWithAnimation(int key, int priority);
    void searchWithAnimation(TreapNode* curr, int key); 
    void removeWithAnimation(int key);

    void sbs_insertWithAnimation(int key, int priority);

    int getSubtreeWidth(TreapNode* curr);
    void updateSubtreeWidth(TreapNode* curr);
    void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);

    TreapNode* cloneTree(TreapNode* root);

    void unhighlightAllCodeBlocks();

    void drawTreapNode(TreapNode* curr);
    void drawTreapEdge(TreapEdge* edge);
    void drawTreap(TreapNode* curr);

    void cleanupForOperations();

public:
    void loadFromFile();
    void insert(int key, int priority = rand(), bool isAnimated = true);
    void remove(int key);
    void search(int key);
    void clear();

    void goToNextStep() {
        if (currentStep < steps.size() - 1) {
            currentStep++;
        }
    }

    void goToPreviousStep() {
        if (currentStep > 0) {
            currentStep--;
        }
    }

    TreapUI();
    ~TreapUI() {
        Button::deleteButtons<RectButton>(Buttons);
        Button::deleteButtons<RectButton>(CodeBlocks);
        treap.clear();
        clear();
        for (TreapNode* curr : trashbin) {
            clear(curr);
        }
    }
    void init() override;
    void initButtons() override;
    void updateButtonPositions() override;

    void updateScene() override;
    void updateSceneInCamera(Camera2D cam) {};

    void displayScene() override;
    void resetAnimations() {};
    void clearIndicatesAndHighlights() override {};

    void displaySceneInCamera() override {
        // Implement the display logic for treap in camera scene
        if (drawInsideTreap) treap.drawTreap(treap.root);
        else if (stepByStepAnimation && currentStep < steps.size()) steps[currentStep]->draw();
        else drawTreap(root);
    }
};