#include "../header/Tree.h"

Node* Treap::rotateLeft(Node* root) {
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	return newRoot;
}

Node* Treap::rotateRight(Node* root) {
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	return newRoot;
}

Node* Treap::insert(Node* root, int key) {
	if (!root) return new Node(key);
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

Node* Treap::search(Node* root, int key) {
	if (!root) return nullptr;

	if (root->data == key) return root;

	if (root->data > key) return search(root->left, key);

	return search(root->right, key);
}

Node* Treap::remove(Node* root, int key) {
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

void Treap::insert(int key) {
	root = insert(root, key);
}

Node* Treap::search(int key) {
	return search(root, key);
}

void Treap::remove(int key) {
	root = remove(root, key);
}