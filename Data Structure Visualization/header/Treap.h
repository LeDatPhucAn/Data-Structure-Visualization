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

	TreapNode(int value, Vector2 pos) : Node(value, pos, 50), priority(rand()), left(nullptr), right(nullptr) {}
	TreapNode(int value, float X, float Y) : Node(value, { X,Y }, 50), priority(rand()) , left(nullptr), right(nullptr) {}
	TreapNode(int value, float X, float Y, int r) : Node(value, { X,Y }, r), priority(rand()) , left(nullptr), right(nullptr) {}
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
public:
	Treap() : root(nullptr) {
		srand(time(nullptr));
	}
	TreapNode* insert(TreapNode* root, int key, Vector2 pos);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);
};


