#pragma once

#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <ctime>
#include "Node.h"
class TreapNode : public Node{
public:
	int priority;
	Edge* leftEdge;
	Edge* rightEdge;
	int subtreeWidth;

	TreapNode(int data, Vector2 pos) : Node(data, pos, 0), priority(rand()), leftEdge(nullptr), rightEdge(nullptr), subtreeWidth(1){}

	~TreapNode() {
		delete leftEdge;
		leftEdge = nullptr;
		delete rightEdge;
		rightEdge = nullptr;
	}
};

class Treap {
protected:
	TreapNode* root;
private:
	TreapNode* rotateLeft(TreapNode* root);
	TreapNode* rotateRight(TreapNode* root);
public:
	Treap() : root(nullptr) {
		srand(time(nullptr));
	}
	int getSubtreeWidth(TreapNode* curr);
	void updateSubtreeWidth(TreapNode* curr);
	TreapNode* insert(TreapNode* root, int key, Vector2 pos);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);
};


