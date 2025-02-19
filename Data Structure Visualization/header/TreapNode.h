#pragma once
#include "Node.h"

template <typename T>
class TreapNode : public Node<T> {
public:
    int priority;
    TreapNode<T>* left;
    TreapNode<T>* right;

    TreapNode(T value) : Node<T>(value), priority(rand()), left(nullptr), right(nullptr) {}
    ~TreapNode() override {
        delete left;
        delete right;
    }
};

template <typename T>
TreapNode<T>* Treap<T>::rotateLeft(TreapNode<T>* root) {
	TreapNode<T>* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	return newRoot;
}

template <typename T>
TreapNode<T>* Treap<T>::rotateRight(TreapNode<T>* root) {
	TreapNode<T>* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	return newRoot;
}

template <typename T>
TreapNode<T>* Treap<T>::insert(TreapNode<T>* root, T key) {
	if (!root) return new TreapNode<T>(key);
	if (root->data == key) return root;

	if (key < root->data) {
		root->left = insert(root->left, key);
		if (root->left->priority > root->priority) {
			root = rotateRight(root);
		}
	}
	else {
		root->right = insert(root->right, key);
		if (root->right->priority > root->priority) {
			root = rotateLeft(root);
		}
	}

	return root;
}

template <typename T>
TreapNode<T>* Treap<T>::search(TreapNode<T>* root, T key) {
	if (!root) return nullptr;

	if (root->data == key) return root;

	if (root->data > key) return search(root->left, key);

	return search(root->right, key);
}

template <typename T>
TreapNode<T>* Treap<T>::remove(TreapNode<T>* root, T key) {
	if (!root) return nullptr;

	if (root->data > key) {
		root->left = remove(root->left, key);
	}
	else if (root->data < key) {
		root->right = remove(root->right, key);
	}
	else {
		if (!root->left && !root->right) return nullptr;

		else if (!root->right) return root->left;

		else if (!root->left) return root->right;

		if (root->left->priority > root->right->priority) {
			root = rotateRight(root);
			root->right = remove(root->right, key);
		}
		else {
			root = rotateLeft(root);
			root->left = remove(root->left, key);
		}
	}

	return root;
}

template <typename T>
void Treap<T>::insert(T key) {
	root = insert(root, key);
}

template <typename T>
TreapNode<T>* Treap<T>::search(T key) {
	return search(root, key);
}

template <typename T>
void Treap<T>::remove(T key) {
	root = remove(root, key);
}