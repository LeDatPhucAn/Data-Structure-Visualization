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

    TreapNode(int key, int priority, Vector2 pos)
        : NumberInputBox(4, pos.x, pos.y),
        Node(key, pos, 0),
        priority(priority % 100),
        leftEdge(nullptr),
        rightEdge(nullptr),
        subtreeWidth(1)
    {
        setNumber(key);

        // Style the key box
        FillColor = LIGHTGRAY;
        TextColor = BLACK;
        OutLineColor = DARKGRAY;

        // Create priority box
        priorityBox = new NumberInputBox(4);
        priorityBox->setNumber(this->priority);
        priorityBox->FillColor = { 173, 216, 230, 255 };
        priorityBox->TextColor = MAROON;
        priorityBox->OutLineColor = DARKGRAY;
        syncPosition();
    }

    ~TreapNode() {
        if (priorityBox) delete priorityBox;
        if (leftEdge) delete leftEdge;
        if (rightEdge) delete rightEdge;
    }

    int getKey() const {
        return getNumber();
    }

    void setKey(int key) {
        setNumber(key);
    }

    int getPriority() const {
        return priorityBox->getNumber();
    }

    void setPriority(int p) {
        priorityBox->setNumber(p);
    }

    void syncPosition() {
        // Shrink this (key) to left half
        rect.width = 60;
        rect.height = 40;

        this->position = {
            rect.x + rect.width / 2,
            rect.y + rect.height / 2
        };

        this->radius = rect.height / 2;

        if (priorityBox) {
            priorityBox->rect.width = 40;
            priorityBox->rect.height = rect.height;
            priorityBox->rect.x = rect.x + rect.width;
            priorityBox->rect.y = rect.y;
        }
    }

    void setVisualPosition(float x, float y) {
        rect.x = x;
        rect.y = y;
        syncPosition();
    }

    void update() override {
        NumberInputBox::update();
        syncPosition();

        // Update priority box
        if (priorityBox) {
            priorityBox->update();

            if (CheckCollisionPointRec(getMousePos(), priorityBox->rect)) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    // deactivate key box input
                    inputHandler->setTexting(false);

                    // activate priority input
                    priorityBox->inputHandler->setTexting(true);
                }
            }

            if (priorityBox->inputHandler->isTexting() && IsKeyPressed(KEY_ENTER)) {
                priorityBox->inputHandler->setTexting(false);
            }
        }

        // Key box input
        if (checkCollision()) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // deactivate priority input
                if (priorityBox) priorityBox->inputHandler->setTexting(false);

                // activate key input
                inputHandler->setTexting(true);
            }
        }
        else {
            OutLineColor = DARKGRAY;
        }

        if (inputHandler->isTexting() && IsKeyPressed(KEY_ENTER)) {
            inputHandler->setTexting(false);
            if (onClick) onClick();
        }
    }


    void draw() override {
        NumberInputBox::draw();
        if (priorityBox) priorityBox->draw();
    }

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
	TreapNode* getRoot();
	int getSubtreeWidth(TreapNode* curr);
	void updateSubtreeWidth(TreapNode* curr);
	TreapNode* insert(TreapNode* root, Vector2 pos, int key, int priority);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);
	void clear();

};