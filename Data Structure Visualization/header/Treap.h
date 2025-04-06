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

	TreapNode(int data, int priority, Vector2 pos) : Node(data, pos, 0), NumberInputBox(3, pos.x, pos.y), 
		priority(priority % 100), leftEdge(nullptr), rightEdge(nullptr), subtreeWidth(1) {
		setNumber(data);
		this->position = {
		pos.x + rect.width / 2,
		pos.y + rect.height / 2
		};
		this->radius = rect.height / 2;
	}

	int getData() const{
		return getNumber();
	}

	int setData(int x) {
		setNumber(x);
	}

	// --- Sync visual + logical center position ---
	void syncPosition() {
		this->position = {
			rect.x + rect.width / 2,
			rect.y + rect.height / 2
		};
		this->radius = rect.height / 2; // estimate for drawing edges
	}

	// --- Use this when repositioning ---
	void setVisualPosition(float x, float y) {
		rect.x = x;
		rect.y = y;
		syncPosition();
	}

	// Optional: override update if you want auto-sync
	void update() override {
		NumberInputBox::update(); // handles animation, inputHandler.update, etc.
		syncPosition();

		if (checkCollision()) {
			OutLineColor = RED;

			// Fix: Allow clicking with mouse (instead of only gesture tap)
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				inputHandler->setTexting(true);
			}
		}
		else {
			OutLineColor = DARKGRAY;
		}
	}

	Vector2 getMousePos() const override;

	~TreapNode() {
		if (leftEdge) {
			delete leftEdge;
			leftEdge = nullptr;
		}
		if (rightEdge) {
			delete rightEdge;
			rightEdge = nullptr;
		}
	}
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
	TreapNode* getRoot();
	int getSubtreeWidth(TreapNode* curr);
	void updateSubtreeWidth(TreapNode* curr);
	TreapNode* insert(TreapNode* root, Vector2 pos, int key, int priority);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);
	void clear();

};