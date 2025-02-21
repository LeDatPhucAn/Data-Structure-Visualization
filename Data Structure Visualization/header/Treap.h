#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>
#include "header/TreapNode.h"

class Treap {
private:
	static constexpr int MIN_VAL = 0;
	static constexpr int MAX_VAL = 999;
	// 
	static constexpr int MAX_SIZE = 20;

	TreapNode* root;
	TreapNode* rotateLeft(TreapNode* root);
	TreapNode* rotateRight(TreapNode* root);
	TreapNode* insert(TreapNode* root, int key);
	TreapNode* search(TreapNode* root, int key);
	TreapNode* remove(TreapNode* root, int key);
	std::vector<TreapNode*> NodesVector;
	int getSize();
	
public:
	Treap() : root(nullptr) {
		srand(time(nullptr));
	}
	void insert(int key);
	TreapNode* search(int key);
	void remove(int key);
};


