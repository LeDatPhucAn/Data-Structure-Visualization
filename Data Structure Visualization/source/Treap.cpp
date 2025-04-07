#include "../header/Treap.h"
#include "../header/SceneHandler.h"
#include <math.h>

TreapNode::TreapNode(int key, int priority, Vector2 pos) : NumberInputBox(4, pos.x, pos.y), Node(key, pos, 0), priority(priority % 100), leftEdge(nullptr), rightEdge(nullptr), subtreeWidth(1){
    setNumber(key);

    // Style the key box
    FillColor = LIGHTGRAY;
    TextColor = BLACK;
    OutLineColor = DARKGRAY;

    // Create priority box
    priorityBox = new NumberInputBox(4);
    priorityBox->setNumber(this->priority);
    priorityBox->FillColor = { 173, 216, 230, 255 };
    priorityBox->TextColor = MAROON;
    priorityBox->OutLineColor = DARKGRAY;
    syncPosition();
}

TreapNode::~TreapNode() {
    if (priorityBox) delete priorityBox;
    if (leftEdge) delete leftEdge;
    if (rightEdge) delete rightEdge;
}

int TreapNode::getKey() const {
    return getNumber();
}

void TreapNode::setKey(int key) {
    setNumber(key);
    this->data = getKey();
}

int TreapNode::getPriority() const {
    return priorityBox->getNumber();
}

void TreapNode::setPriority(int p) {
    priorityBox->setNumber(p);
    this->priority = priorityBox->getNumber();
}

void TreapNode::syncPosition() {
    // Shrink this (key) to left half
    rect.width = 60;
    rect.height = 40;

    this->position = {
        rect.x + rect.width / 2,
        rect.y + rect.height / 2
    };

    this->radius = rect.height / 2;

    if (priorityBox) {
        priorityBox->rect.width = 40;
        priorityBox->rect.height = rect.height;
        priorityBox->rect.x = rect.x + rect.width;
        priorityBox->rect.y = rect.y;
    }
}

void TreapNode::setVisualPosition(float x, float y) {
    rect.x = x;
    rect.y = y;
    syncPosition();
}

void TreapNode::update() {
    NumberInputBox::update();
    syncPosition();

    // Update priority box
    if (priorityBox) {
        priorityBox->update();

        if (CheckCollisionPointRec(getMousePos(), priorityBox->rect)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // deactivate key box input
                inputHandler->setTexting(false);

                // activate priority input
                priorityBox->inputHandler->setTexting(true);
            }
        }

        if (priorityBox->inputHandler->isTexting() && IsKeyPressed(KEY_ENTER)) {
            priorityBox->inputHandler->setTexting(false);
        }
    }

    // Key box input
    if (checkCollision()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // deactivate priority input
            if (priorityBox) priorityBox->inputHandler->setTexting(false);

            // activate key input
            inputHandler->setTexting(true);
        }
    }
    else {
        OutLineColor = DARKGRAY;
    }

    if (inputHandler->isTexting() && IsKeyPressed(KEY_ENTER)) {
        inputHandler->setTexting(false);
        if (onClick) onClick();
    }
}

void TreapNode::draw(){
    NumberInputBox::draw();
    if (priorityBox) priorityBox->draw();
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