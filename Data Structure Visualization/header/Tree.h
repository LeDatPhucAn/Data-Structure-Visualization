#pragma once

#include <cstdlib>
#include <ctime>

struct Node {
	int data;
	int priority;
	Node* left;
	Node* right;
	Node(int data) {
		this->data = data;
		this->priority = rand();
		this->left = nullptr;
		this->right = nullptr;
	}
};

class Treap {
private:
	Node* root;
	Node* rotationLeft(Node* root);
	Node* rotationRight(Node* root);

public:
	Treap() : root(nullptr) {
		srand(time(nullptr));
	}

	void insert(int key);
	Node* search(int key);
	void remove(int key);
};