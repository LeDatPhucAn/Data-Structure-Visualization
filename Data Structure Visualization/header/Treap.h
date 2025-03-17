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

	TreapNode(int data, int priority, Vector2 pos) : Node(data, pos, 0), priority(priority % 100), leftEdge(nullptr), rightEdge(nullptr), subtreeWidth(1){}

	~TreapNode() {
		if (leftEdge) {
			delete static_cast<TreapNode*>(leftEdge->to);
			delete leftEdge;
		}
		if (rightEdge) {
			delete static_cast<TreapNode*>(rightEdge->to);
			delete rightEdge;
		}
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
	~Treap(){
		delete root;
	}
	int getSubtreeWidth(TreapNode* curr);
	void updateSubtreeWidth(TreapNode* curr);
	TreapNode* insert(TreapNode* root, Vector2 pos, int key, int priority);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);

};

