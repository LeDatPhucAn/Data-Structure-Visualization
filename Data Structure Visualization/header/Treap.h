#pragma once

#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <ctime>
#include "Node.h"
class TreapNode : public Node {
public:
	int priority;
	Edge* leftEdge;
	Edge* rightEdge;
	int subtreeWidth;

	TreapNode(int data, int priority, Vector2 pos) : Node(data, pos, 0), priority(priority % 100), leftEdge(nullptr), rightEdge(nullptr), subtreeWidth(1) {}

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