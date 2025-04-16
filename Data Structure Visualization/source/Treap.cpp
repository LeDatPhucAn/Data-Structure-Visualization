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
