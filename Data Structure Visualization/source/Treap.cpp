#include "../header/Treap.h"
#include "../header/SceneHandler.h"

#include <math.h>

TreapNode* Treap::rotateLeft(TreapNode* root) {
    Edge* oldRightEdge = root->rightEdge;
    if (!oldRightEdge) return root;

    TreapNode* newRoot = static_cast<TreapNode*> (oldRightEdge->to);

    Edge* temp = newRoot->leftEdge;
    root->rightEdge = temp ? new Edge(root, temp->to) : nullptr;

    delete oldRightEdge;
    delete temp;

    newRoot->leftEdge = new Edge(newRoot, root);

    return newRoot;
}

TreapNode* Treap::rotateRight(TreapNode* root) {
    Edge* oldLeftEdge = root->leftEdge;
    if (!oldLeftEdge) return root;

    TreapNode* newRoot = static_cast<TreapNode*> (oldLeftEdge->to);

    Edge* temp = newRoot->rightEdge;

    root->leftEdge = temp ? new Edge(root, temp->to) : nullptr;

    delete temp;
    delete oldLeftEdge;

    newRoot->rightEdge = new Edge(newRoot, root);

    return newRoot;
}

void Treap::clear(TreapNode* root) {
    if (!root) return;

    if (root->leftEdge) clear(static_cast<TreapNode*>(root->leftEdge->to));
    if (root->rightEdge) clear(static_cast<TreapNode*>(root->rightEdge->to));

    delete root;
}

TreapNode* Treap::insert(TreapNode* root, Vector2 pos, int key, int priority) {
    static const int Y_OFFSET = 70;
    if (!root) return new TreapNode(key, priority, pos);

    int treeDepth = log2(getSubtreeWidth(root) + 1) + 1;
    int newXOffset = max(getSubtreeWidth(root) * treeDepth * 10, 30);

    if (root->data > key) {
        TreapNode* newLeftChild = insert(root->leftEdge ? static_cast<TreapNode*> (root->leftEdge->to) : nullptr, { pos.x - newXOffset, pos.y + Y_OFFSET }, key, priority);
        root->leftEdge = new Edge(root, newLeftChild);
        if (newLeftChild->priority > root->priority) root = rotateRight(root);
    }
    else {
        TreapNode* newRightChild = insert(root->rightEdge ? static_cast<TreapNode*>(root->rightEdge->to) : nullptr, { pos.x + newXOffset, pos.y + Y_OFFSET }, key, priority);
        root->rightEdge = new Edge(root, newRightChild);
        if (newRightChild->priority > root->priority) root = rotateLeft(root);
    }

    updateSubtreeWidth(root);
    return root;
}

TreapNode* Treap::search(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (root->data == key) return root;

    if (root->data > key) {
        return search(root->leftEdge ? static_cast<TreapNode*> (root->leftEdge->to) : nullptr, key);
    }

    return search(root->rightEdge ? static_cast<TreapNode*> (root->rightEdge->to) : nullptr, key);
}

TreapNode* Treap::remove(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (root->data > key) {
        if (root->leftEdge) {
            TreapNode* newLeft = remove(static_cast<TreapNode*> (root->leftEdge->to), key);
            if (root->leftEdge) delete root->leftEdge;
            root->leftEdge = newLeft ? new Edge(root, newLeft) : nullptr;
        }
    }
    else if (root->data < key) {
        if (root->rightEdge) {
            TreapNode* newRight = remove(static_cast<TreapNode*>(root->rightEdge->to), key);
            if (root->rightEdge) delete root->rightEdge;
            root->rightEdge = newRight ? new Edge(root, newRight) : nullptr;
        }
    }
    else {
        if (!root->leftEdge && !root->rightEdge) {
            delete root;
            return nullptr;
        }
        else if (!root->rightEdge) {
            TreapNode* temp = static_cast<TreapNode*> (root->leftEdge->to);
            delete root->leftEdge;
            root->leftEdge = nullptr;
            delete root;
            return temp;
        }
        else if (!root->leftEdge) {
            TreapNode* temp = static_cast<TreapNode*> (root->rightEdge->to);
            delete root->rightEdge;
            root->rightEdge = nullptr;
            delete root;
            return temp;
        }

        if (static_cast<TreapNode*> (root->leftEdge->to)->priority > static_cast<TreapNode*> (root->rightEdge->to)->priority) {
            root = rotateRight(root);
            TreapNode* newRight = remove(static_cast<TreapNode*>(root->rightEdge->to), key);
            if (root->rightEdge) delete root->rightEdge;
            root->rightEdge = newRight ? new Edge(root, newRight) : nullptr;
        }
        else {
            root = rotateLeft(root);
            TreapNode* newLeft = remove(static_cast<TreapNode*>(root->leftEdge->to), key);
            if (root->leftEdge) delete root->leftEdge;
            root->leftEdge = newLeft ? new Edge(root, newLeft) : nullptr;
        }
    }

    updateSubtreeWidth(root);
    return root;
}

void Treap::clear() {
    clear(root);
}

int Treap::getSubtreeWidth(TreapNode* curr) {
    if (!curr) return 0;
    return curr->subtreeWidth;
}

void Treap::updateSubtreeWidth(TreapNode* curr) {
    if (curr) {
        if (curr) {
            int leftWidth = curr->leftEdge ? getSubtreeWidth(static_cast<TreapNode*>(curr->leftEdge->to)) : 0;
            int rightWidth = curr->rightEdge ? getSubtreeWidth(static_cast<TreapNode*>(curr->rightEdge->to)) : 0;
            curr->subtreeWidth = 1 + leftWidth + rightWidth;
        }
    }
}

TreapNode* Treap::getRoot() {
    return root;
}

Vector2 TreapNode::getMousePos() const {
    return SceneHandler::mouseWorldPos;
}