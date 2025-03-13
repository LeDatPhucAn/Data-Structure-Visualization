#pragma once

#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <ctime>

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
	int getSubtreeWidth(TreapNode* curr);
	void updateSubtreeWidth(TreapNode* curr);
private:
	TreapNode* rotateLeft(TreapNode* root);
	TreapNode* rotateRight(TreapNode* root);
	TreapNode* insert(TreapNode* root, int key);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);
public:
	Treap() : root(nullptr) {
		srand(time(nullptr));
	}
	void insert(int key);
	TreapNode* search(int key);
	void remove(int key);
};


