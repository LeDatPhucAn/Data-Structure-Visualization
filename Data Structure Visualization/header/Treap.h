#pragma once

#include "Button.h"
#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <ctime>

class TreapNode : public NumberInputBox, public Node {
public:
    int priority;
    Edge* leftEdge;
    Edge* rightEdge;
    int subtreeWidth;
    NumberInputBox* priorityBox = nullptr;

    TreapNode(int key, int priority, Vector2 pos);
    ~TreapNode();

    int getKey() const;
    void setKey(int key);
    int getPriority() const;
    void setPriority(int p);
    void syncPosition();
    void setVisualPosition(float x, float y);
    void update() override;
	void draw() override;
    Vector2 getMousePos() const override;
};

class Treap {
protected:
	TreapNode* root;
private:
	TreapNode* rotateLeft(TreapNode* root);
	TreapNode* rotateRight(TreapNode* root);
	void clear(TreapNode* root);
public:
	Treap() : root(nullptr) {
		srand(time(nullptr));
	}
	~Treap() {
		clear(root);
		root = nullptr;
	}
	int getSubtreeWidth(TreapNode* curr);
	void updateSubtreeWidth(TreapNode* curr);
	TreapNode* insert(TreapNode* root, Vector2 pos, int key, int priority);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);
	void clear();
};