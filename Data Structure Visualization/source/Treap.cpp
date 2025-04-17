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
    keyBox->rect.x = position.x - keyBox->getWidth();
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
    if (noDraw) return;
    keyBox->draw();
    priorityBox->draw();
}

Vector2 TreapNode::getMousePos() const {
    return SceneHandler::mouseWorldPos;
}


const Vector2 Treap::ROOT_POS = { static_cast<float> (UI::screenWidth) / 2, 0 };

TreapNode* Treap::rotateLeft(TreapNode* root) {
    TreapEdge* oldRightEdge = root->rightEdge;
    if (!oldRightEdge) return root;

    TreapNode* newRoot = oldRightEdge->to;

    TreapEdge* temp = newRoot->leftEdge;
    root->rightEdge = temp ? new TreapEdge(root, temp->to) : nullptr;

    delete oldRightEdge;
    delete temp;

    newRoot->leftEdge = new TreapEdge(newRoot, root);

    return newRoot;
}

TreapNode* Treap::rotateRight(TreapNode* root) {
    TreapEdge* oldLeftEdge = root->leftEdge;
    if (!oldLeftEdge) return root;

    TreapNode* newRoot = oldLeftEdge->to;

    TreapEdge* temp = newRoot->rightEdge;

    root->leftEdge = temp ? new TreapEdge(root, temp->to) : nullptr;

    delete temp;
    delete oldLeftEdge;

    newRoot->rightEdge = new TreapEdge(newRoot, root);

    return newRoot;
}

TreapNode* Treap::insert(TreapNode* root, int key, int priority) {
    if (!root) {
        TreapNode* newNode = new TreapNode(key, priority, ROOT_POS);
        return newNode;
    }

    if (root->getKey() > key) {
        TreapNode* newLeftChild = insert(root->leftEdge ? root->leftEdge->to : nullptr, key, priority);
        root->leftEdge = new TreapEdge(root, newLeftChild);
        if (newLeftChild->getPriority() > root->getPriority()) root = rotateRight(root);
    }
    else if (root->getKey() < key) {
        TreapNode* newRightChild = insert(root->rightEdge ? root->rightEdge->to : nullptr, key, priority);
        root->rightEdge = new TreapEdge(root, newRightChild);
        if (newRightChild->getPriority() > root->getPriority()) root = rotateLeft(root);
    }

    updateSubtreeWidth(root);
    return root;
}

bool Treap::search(TreapNode* root, int key) {
    if (!root) return false;
    if (root->getKey() == key) return true;
    else if (root->getKey() > key) {
        return search(root->leftEdge ? root->leftEdge->to : nullptr, key);
    }
    return search(root->rightEdge ? root->rightEdge->to : nullptr, key);
}

TreapNode* Treap::remove(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (root->getKey() > key) {
        if (root->leftEdge) {
            TreapNode* newLeft = remove(static_cast<TreapNode*> (root->leftEdge->to), key);
            if (root->leftEdge) delete root->leftEdge;
            root->leftEdge = newLeft ? new TreapEdge(root, newLeft) : nullptr;
        }
    }
    else if (root->getKey() < key) {
        if (root->rightEdge) {
            TreapNode* newRight = remove(static_cast<TreapNode*>(root->rightEdge->to), key);
            if (root->rightEdge) delete root->rightEdge;
            root->rightEdge = newRight ? new TreapEdge(root, newRight) : nullptr;
        }
    }
    else {
        if (!root->leftEdge && !root->rightEdge) {
            delete root;
            return nullptr;
        }
        else if (!root->rightEdge) {
            TreapNode* temp = root->leftEdge->to;
            delete root->leftEdge;
            root->leftEdge = nullptr;
            delete root;
            return temp;
        }
        else if (!root->leftEdge) {
            TreapNode* temp = root->rightEdge->to;
            delete root->rightEdge;
            root->rightEdge = nullptr;
            delete root;
            return temp;
        }

        if (root->leftEdge->to->getPriority() > root->rightEdge->to->getPriority()) {
            root = rotateRight(root);
            TreapNode* newRight = remove(root->rightEdge->to, key);
            if (root->rightEdge) delete root->rightEdge;
            root->rightEdge = newRight ? new TreapEdge(root, newRight) : nullptr;
        }
        else {
            root = rotateLeft(root);
            TreapNode* newLeft = remove(root->leftEdge->to, key);
            if (root->leftEdge) delete root->leftEdge;
            root->leftEdge = newLeft ? new TreapEdge(root, newLeft) : nullptr;
        }
    }

    updateSubtreeWidth(root);
    return root;
}

void Treap::clear(TreapNode* curr) {
    if (!curr) return;

    if (curr->leftEdge) {
        clear(curr->leftEdge->to);
        delete curr->leftEdge;
        curr->leftEdge = nullptr;
    }
    if (curr->rightEdge) {
        clear(curr->rightEdge->to);
        delete curr->rightEdge;
        curr->rightEdge = nullptr;
    }

    delete curr;
}

TreapNode* Treap::insertBST(TreapNode* root, int key, int priority) {
    if (!root) return new TreapNode(key, priority, ROOT_POS);

    if (root->getKey() == key) return root;
    else if (root->getKey() > key) {
        root->leftEdge = new TreapEdge(root, insertBST(root->leftEdge ? root->leftEdge->to : nullptr, key, priority));
    }
    else {
        root->rightEdge = new TreapEdge(root, insertBST(root->rightEdge ? root->rightEdge->to : nullptr, key, priority));
    }

    updateSubtreeWidth(root);
    return root;
}

int Treap::getSubtreeWidth(TreapNode* curr) {
    if (!curr) return 0;
    return curr->subtreeWidth;
}

void Treap::updateSubtreeWidth(TreapNode* curr) {
    if (curr) {
        int leftWidth = curr->leftEdge ? getSubtreeWidth(curr->leftEdge->to) : 0;
        int rightWidth = curr->rightEdge ? getSubtreeWidth(curr->rightEdge->to) : 0;
        curr->subtreeWidth = 1 + leftWidth + rightWidth;
    }
}

void Treap::reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset) {
    if (!root) return;

    // Position the visual button correctly by setting top-left corner
    float rectX = pos.x - root->keyBox->getWidth() / 2;
    float rectY = pos.y - root->keyBox->getHeight() / 2;
    root->position = { rectX, rectY };
    root->syncPosition();

    int leftWidth = getSubtreeWidth(root->leftEdge ? root->leftEdge->to : nullptr);
    int rightWidth = getSubtreeWidth(root->rightEdge ? root->rightEdge->to : nullptr);
    int newXOffset = max((leftWidth + rightWidth + 1) * 40, 80);

    if (root->leftEdge) {
        Vector2 leftPos = { pos.x - newXOffset, pos.y + yOffset };
        reposition(root->leftEdge->to, leftPos, newXOffset, yOffset);
    }

    if (root->rightEdge) {
        Vector2 rightPos = { pos.x + newXOffset, pos.y + yOffset };
        reposition(root->rightEdge->to, rightPos, newXOffset, yOffset);
    }
}

void Treap::insert(int key, int priority) {
    root = insert(root, key, priority);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void Treap::clear() {
    clear(root);
    root = nullptr;
}

void Treap::insertBST(int key, int priority) {
    root = insertBST(root, key, priority);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void Treap::drawTreapNode(TreapNode* curr) {
    if (!curr) return;
    curr->draw();
}

void Treap::drawTreapEdge(TreapEdge* edge) {
    if (!edge || !edge->from || !edge->to) return;
    edge->draw();
}

void Treap::drawTreap(TreapNode* curr) {
    if (!curr) return;

    drawTreapNode(curr);

    if (curr->leftEdge) {
        drawTreapEdge(curr->leftEdge);
        drawTreap(curr->leftEdge->to);
    }

    if (curr->rightEdge) {
        drawTreapEdge(curr->rightEdge);
        drawTreap(curr->rightEdge->to);
    }
}

TreapNode* Treap::searchForNode(TreapNode* curr, int key) {
    if (!curr) return nullptr;
    if (curr->getKey() == key) return curr;
    else if (curr->getKey() > key) {
        return searchForNode(root->leftEdge ? root->leftEdge->to : nullptr, key);
    }
    return searchForNode(root->rightEdge ? root->rightEdge->to : nullptr, key);
}

//TreapEdge* oldRightEdge = root->rightEdge;
//if (!oldRightEdge) return root;
//
//TreapNode* newRoot = oldRightEdge->to;
//
//TreapEdge* temp = newRoot->leftEdge;
//root->rightEdge = temp ? new TreapEdge(root, temp->to) : nullptr;
//
//delete oldRightEdge;
//delete temp;
//
//newRoot->leftEdge = new TreapEdge(newRoot, root);
//
//return newRoot;

//TreapNode* Treap::rotateLeftAtSpecificNode(TreapNode* root, int key) {
//    if (!root) return nullptr;
//
//    if (root->getKey() == key) {
//        TreapEdge* oldRightEdge = root->rightEdge;
//        if (!oldRightEdge) return root;
//        
//        TreapNode* newRoot = oldRightEdge->to;
//
//        TreapEdge* temp = newRoot->leftEdge;
//        root->rightEdge = temp ? new TreapEdge(root, temp->to) : nullptr;
//
//        delete oldRightEdge;
//        //delete temp;
//
//        newRoot->leftEdge = new TreapEdge(newRoot, root);
//
//        return newRoot;
//    }
//    else if (root->getKey() > key) {
//        root->leftEdge = new TreapEdge(root, rotateLeftAtSpecificNode(root->leftEdge ? root->leftEdge->to : nullptr, key));
//    }
//    else {
//        root->rightEdge = new TreapEdge(root, rotateLeftAtSpecificNode(root->rightEdge ? root->rightEdge->to : nullptr, key));
//    }
//    updateSubtreeWidth(root);
//    return root;
//}

TreapNode* Treap::rotateLeftAtSpecificNode(TreapNode* curr, int key) {
    if (!curr) return nullptr;

    if (curr->getKey() == key) {
        TreapEdge* oldRightEdge = curr->rightEdge;
        if (!oldRightEdge) return curr;

        TreapNode* newcurr = oldRightEdge->to;

        TreapNode* movedLeft = newcurr->leftEdge ? newcurr->leftEdge->to : nullptr;

        curr->rightEdge = movedLeft ? new TreapEdge(curr, movedLeft) : nullptr;

        delete oldRightEdge;

        newcurr->leftEdge = new TreapEdge(newcurr, curr);

        cout << "rotate here" << endl;
        return newcurr;
    }
    else if (curr->getKey() > key) {
        cout << "go left" << endl;
        curr->leftEdge = new TreapEdge(curr, rotateLeftAtSpecificNode(curr->leftEdge ? curr->leftEdge->to : nullptr, key));
        cout << "return from left" << endl;
    }
    else {
        cout << "go right" << endl;
        curr->rightEdge = new TreapEdge(curr, rotateLeftAtSpecificNode(curr->rightEdge ? curr->rightEdge->to : nullptr, key));
        cout << "return from right" << endl;
    }

    updateSubtreeWidth(curr);
    return curr;
}