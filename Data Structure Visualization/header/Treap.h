#pragma once

#include <cstdlib>
#include <ctime>
#include "TreapNode.h"

template <typename T> 
class Treap {
private:
	TreapNode<T>* root;
	TreapNode<T>* rotateLeft(TreapNode<T>* root);
	TreapNode<T>* rotateRight(TreapNode<T>* root);
	TreapNode<T>* insert(TreapNode<T>* root, T key);
	TreapNode<T>* search(TreapNode<T>* root, T key);
	TreapNode<T>* remove(TreapNode<T>* root, T key);

public:
	Treap() : root(nullptr) {
		srand(time(nullptr));
	}
	void insert(T key);
	TreapNode<T>* search(T key);
	void remove(T key);
};