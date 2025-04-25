#pragma once
#include "SceneManager.h"
#include "SceneHandler.h"
#include "Treap.h" 
#include "Button.h"
#include "UI.h"
#include "tinyfiledialogs.h"
#include <fstream>
#include <string>
#include <sstream>
#include <functional>

struct TreapStep {
    TreapNode* root;
    vector<TreapNode*> highlightedNodes;
    vector<TreapEdge*> highlightedEdges;
    vector<int> highlightedCodeLines;
    
    TreapStep(TreapNode* root = nullptr) : root(root){}

    ~TreapStep() {
        if (root) {
            clear(root);
        }
    }

    void clear(TreapNode* curr) {
        if (!curr) return;

        if (curr->leftEdge) {
            clear(curr->leftEdge->to);
            delete curr->leftEdge;
            curr->leftEdge = nullptr;
        }
        if (curr->rightEdge) {
            clear(curr->rightEdge->to);
            delete curr->rightEdge;
            curr->rightEdge = nullptr;
        }

        delete curr;
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
    vector<TreapStep> steps;
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

    void getNodesToMove(vector<TreapNode*>& res, TreapNode* curr);

    bool searchBeforeRemove(TreapNode* curr, int key);
    void makeNodeDisappear(TreapNode* curr, int key);
    void makeNodeDisappearWithAnimation(TreapNode* curr, int key);

    void insertWithAnimation(int key, int priority);
    void searchWithAnimation(TreapNode* curr, int key); 
    void removeWithAnimation(int key);

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

    void addStep(TreapNode* root, const vector<TreapNode*>& highlightedNodes, const vector<TreapEdge*>& highlightedEdges, const vector<int>& highlightedCodeLines) {
        TreapStep step(cloneTree(root)); // Clone the current tree
        step.highlightedNodes = highlightedNodes;
        step.highlightedEdges = highlightedEdges;
        step.highlightedCodeLines = highlightedCodeLines;
        steps.push_back(step);
    }

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
        if(drawInsideTreap) treap.drawTreap(treap.root);
        else drawTreap(root);
    }

};