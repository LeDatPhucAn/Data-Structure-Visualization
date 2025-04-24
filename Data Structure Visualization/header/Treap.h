#pragma once

#include "Button.h"
#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <ctime>

class TreapNode : public Node {
public:
    TreapEdge* leftEdge;
    TreapEdge* rightEdge;
    int subtreeWidth;
    bool noDraw = false;
	DelayNumberInputBox* keyBox = nullptr;
    DelayNumberInputBox* priorityBox = nullptr;

    int originalKey;
    int originalPriority;

    TreapNode(int key, int priority, Vector2 pos);
    ~TreapNode();

    int getKey() const;
    void setKey(int key);
    int getPriority() const;
    void setPriority(int p);
    bool isModified() const;
    void updateOriginalValues();

    void syncPosition();
	void setVisualPosition(float x, float y);
    void update();
	void draw();
    Vector2 getMousePos() const;
};

class Treap {
private:
    static const Vector2 ROOT_POS;
    const int xOffset = UI::screenWidth / 2 - 20;
    const int yOffset = UI::screenHeight / 8;
    TreapNode* rotateLeft(TreapNode* root);
    TreapNode* rotateRight(TreapNode* root);
    TreapNode* insert(TreapNode* root, int key, int priority);
    bool search(TreapNode* root, int key);
    TreapNode* remove(TreapNode* root, int key);
    void clear(TreapNode* root);

    TreapNode* insertBST(TreapNode* root, int key, int priority);
    TreapNode* rotateLeftAtSpecificNode(TreapNode* curr, int key);
    TreapNode* rotateRightAtSpecificNode(TreapNode* curr, int key);

    void getAllPositions(unordered_map<int, Vector2>& res, TreapNode* curr);

    int getSubtreeWidth(TreapNode* curr);
    void updateSubtreeWidth(TreapNode* curr);
    //void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);

    void drawTreapNode(TreapNode* curr);
    void drawTreapEdge(TreapEdge* edge);

public:
    Treap() : root(nullptr){}
    ~Treap() {
        clear();
    }
    TreapNode* root = nullptr;
    void insert(int key, int priority);
    bool search(int key);
    void remove(int key);
    void clear();

    void insertBST(int key, int priority);
    void rotateLeftAtSpecificNode(int key);
    void rotateRightAtSpecificNode(int key);

    unordered_map<int, Vector2> getAllPositions();

    void drawTreap(TreapNode* curr);

    void reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset);

    TreapNode* searchForNode(TreapNode* curr, int key);
};
