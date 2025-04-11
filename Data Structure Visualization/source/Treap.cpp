#include "../header/Treap.h"
#include "../header/SceneHandler.h"
#include <math.h>

TreapNode::TreapNode(int key, int priority, Vector2 pos) : Node(key, pos, 0), leftEdge(nullptr), rightEdge(nullptr), subtreeWidth(1){
    keyBox = new NumberInputBoxInCamera(3);
    keyBox->setNumber(key);
    keyBox->FillColor = LIGHTGRAY;
    keyBox->TextColor = DARKGRAY;
    keyBox->OutLineColor = DARKGRAY;

    priorityBox = new NumberInputBoxInCamera(3);
    priorityBox->setNumber(priority % 100);
    priorityBox->FillColor = { 173, 216, 230, 255 }; // LIGHTBLUE
    priorityBox->TextColor = MAROON;
    priorityBox->OutLineColor = DARKGRAY;

    syncPosition();
}

TreapNode::~TreapNode() {
    if (keyBox) delete keyBox;
    if (priorityBox) delete priorityBox;
    if (leftEdge) delete leftEdge;
    if (rightEdge) delete rightEdge;
}

int TreapNode::getKey() const {
    return keyBox->getNumber();
}

void TreapNode::setKey(int key) {
    keyBox->setNumber(key);
}

int TreapNode::getPriority() const {
    return priorityBox->getNumber();
}

void TreapNode::setPriority(int p) {
    priorityBox->setNumber(p);
}

void TreapNode::syncPosition() {
    keyBox->rect.x = position.x - keyBox->getWidth() / 2;
    keyBox->rect.y = position.y - keyBox->getHeight() / 2;

    priorityBox->rect.x = keyBox->rect.x + keyBox->getWidth();
    priorityBox->rect.y = keyBox->rect.y;
}

void TreapNode::setVisualPosition(float x, float y) {
    position = { x, y };
    syncPosition();
}

void TreapNode::update() {
    keyBox->update();
    priorityBox->update();
    syncPosition();

    if (CheckCollisionPointRec(getMousePos(), keyBox->rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        keyBox->inputHandler->setTexting(true);
        priorityBox->inputHandler->setTexting(false);
    }
    if (CheckCollisionPointRec(getMousePos(), priorityBox->rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        priorityBox->inputHandler->setTexting(true);
        keyBox->inputHandler->setTexting(false);
    }
    if (keyBox->inputHandler->isTexting() && IsKeyPressed(KEY_ENTER)) {
        keyBox->inputHandler->setTexting(false);
    }
    if (priorityBox->inputHandler->isTexting() && IsKeyPressed(KEY_ENTER)) {
        priorityBox->inputHandler->setTexting(false);
    }
}

void TreapNode::draw(){
    keyBox->draw();
    priorityBox->draw();
}

Vector2 TreapNode::getMousePos() const {
    return SceneHandler::mouseWorldPos;
}

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
    static const int Y_OFFSET = 30;
    if (!root) return new TreapNode(key, priority, pos);

    int treeDepth = log2(getSubtreeWidth(root) + 1) + 1;
    int newXOffset = max(getSubtreeWidth(root) * treeDepth * 5, 20);

    if (root->getKey() > key) {
        TreapNode* newLeftChild = insert(root->leftEdge ? static_cast<TreapNode*> (root->leftEdge->to) : nullptr, { pos.x - newXOffset, pos.y + Y_OFFSET }, key, priority);
        root->leftEdge = new Edge(root, newLeftChild);
        if (newLeftChild->getPriority() > root->getPriority()) root = rotateRight(root);
    }
    else if(root->getKey() < key) {
        TreapNode* newRightChild = insert(root->rightEdge ? static_cast<TreapNode*>(root->rightEdge->to) : nullptr, { pos.x + newXOffset, pos.y + Y_OFFSET }, key, priority);
        root->rightEdge = new Edge(root, newRightChild);
        if (newRightChild->getPriority() > root->getPriority()) root = rotateLeft(root);
    }

    updateSubtreeWidth(root);
    return root;
}

TreapNode* Treap::search(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (root->getKey() == key) return root;

    if (root->getKey() > key) {
        return search(root->leftEdge ? static_cast<TreapNode*> (root->leftEdge->to) : nullptr, key);
    }

    return search(root->rightEdge ? static_cast<TreapNode*> (root->rightEdge->to) : nullptr, key);
}

TreapNode* Treap::remove(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (root->getKey() > key) {
        if (root->leftEdge) {
            TreapNode* newLeft = remove(static_cast<TreapNode*> (root->leftEdge->to), key);
            if (root->leftEdge) delete root->leftEdge;
            root->leftEdge = newLeft ? new Edge(root, newLeft) : nullptr;
        }
    }
    else if (root->getKey() < key) {
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

        if (static_cast<TreapNode*> (root->leftEdge->to)->getPriority() > static_cast<TreapNode*> (root->rightEdge->to)->getPriority()) {
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
            int leftWidth = curr->leftEdge ? getSubtreeWidth(static_cast<TreapNode*>(curr->leftEdge->to)) : 0;
            int rightWidth = curr->rightEdge ? getSubtreeWidth(static_cast<TreapNode*>(curr->rightEdge->to)) : 0;
            curr->subtreeWidth = 1 + leftWidth + rightWidth;
        }
}

TreapNode* Treap::getRoot() {
    return root;
}