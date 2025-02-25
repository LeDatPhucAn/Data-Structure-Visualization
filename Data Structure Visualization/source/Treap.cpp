#include "header/Treap.h"

#include "raylib.h" 

int Treap::getSize(){
    return NodesVector.size();
}

TreapNode* Treap::rotateLeft(TreapNode* root) {
    TreapNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

TreapNode* Treap::rotateRight(TreapNode* root) {
    TreapNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

TreapNode* Treap::insert(TreapNode* root, int key) {
    if (!root) return new TreapNode(key);
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

TreapNode* Treap::search(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (root->data == key) return root;

    if (root->data > key) return search(root->left, key);

    return search(root->right, key);
}

TreapNode* Treap::remove(TreapNode* root, int key) {
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

TreapNode* Treap::search(int key) {
    return search(root, key);
}

void Treap::remove(int key) {
    root = remove(root, key);
}

void Treap::drawTreap(){
    if(root) root->drawNode(root, GetScreenWidth() / 2, 20, 30, 30);
}