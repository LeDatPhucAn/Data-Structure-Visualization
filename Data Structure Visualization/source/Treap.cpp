#include "../header/Treap.h"

TreapNode* Treap::rotateLeft(TreapNode* root) {
    TreapNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    updateSubtreeWidth(root);
    updateSubtreeWidth(newRoot);
    return newRoot;
}

TreapNode* Treap::rotateRight(TreapNode* root) {
    TreapNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    updateSubtreeWidth(root);
    updateSubtreeWidth(newRoot);
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
    updateSubtreeWidth(root);
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
        if (!root->left && !root->right){
            delete root;
            return nullptr;
        }
        else if (!root->right){
            TreapNode* temp = root->left;
            delete root;
            return temp;
        }
        else if (!root->left){
            TreapNode* temp = root->right;
            delete root;
            return temp;
        }

        if (root->left->priority > root->right->priority) {
            root = rotateRight(root);
            root->right = remove(root->right, key);
        }
        else {
            root = rotateLeft(root);
            root->left = remove(root->left, key);
        }
    }

    updateSubtreeWidth(root);
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

int Treap::getSubtreeWidth(TreapNode* curr){
    if(!curr) return 0;
    return curr->subtreeWidth;
}

void Treap::updateSubtreeWidth(TreapNode* curr){
    if(curr){
        curr->subtreeWidth =  1 + getSubtreeWidth(curr->left) + getSubtreeWidth(curr->right);
    }
}