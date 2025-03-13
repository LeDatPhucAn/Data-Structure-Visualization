#pragma once

#include "Node.h"
#include <cstdlib>
#include <ctime>

class TreapNode{
public:
	int data;
	int priority;
	TreapNode* left;
	TreapNode* right;
	int subtreeWidth;

	TreapNode(int data) : data(data), priority(rand()), left(nullptr), right(nullptr), subtreeWidth(1) {};
	~TreapNode() {
		delete left;
		left = nullptr;
		delete right;
		right = nullptr;
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


