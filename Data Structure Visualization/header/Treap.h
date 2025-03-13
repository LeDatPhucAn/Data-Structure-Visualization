#pragma once

#include <cstdlib>
#include <ctime>
#include "Node.h"
class TreapNode : public Node{
public:
	int priority;
	TreapNode* left;
	TreapNode* right;

	TreapNode(int value, Vector2 pos) : Node(value, pos, 50), priority(rand()), left(nullptr), right(nullptr) {}
	TreapNode(int value, float X, float Y) : Node(value, { X,Y }, 50), priority(rand()) , left(nullptr), right(nullptr) {}
	TreapNode(int value, float X, float Y, int r) : Node(value, { X,Y }, r), priority(rand()) , left(nullptr), right(nullptr) {}
	~TreapNode() {
		delete left;
		left = nullptr;
		delete right;
		right = nullptr;
	}
};

class Treap {
private:
	TreapNode* rotateLeft(TreapNode* root);
	TreapNode* rotateRight(TreapNode* root);

public:
	TreapNode* root;
	TreapNode* insert(TreapNode* root, int key);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);

	Treap() : root(nullptr){
	}
	void insert(int key);
	TreapNode* search(int key);
	void remove(int key);
};


