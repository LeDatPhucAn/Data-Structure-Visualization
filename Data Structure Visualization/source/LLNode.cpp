#include "../header/LLNode.h"
#include "../header/Button.h"  
#include "../header/Animation.h"  

LLNode::LLNode() : Node(0, { 0,0 }, 50), next(nullptr) {
    clickBox = new NumberInputCircleInCamera({ 0,0 },radius,3,BLUE,RAYWHITE,RAYWHITE);
    clickBox->setNumber(0);
    clickBox->animation = new CircleButtonInitializeAnimation(clickBox, 1);
}

LLNode::LLNode(int value) : Node(value, { 0,0 }, 50), next(nullptr) {
    clickBox = new NumberInputCircleInCamera({ 0,0 },radius,3, BLUE, RAYWHITE, RAYWHITE);
    clickBox->setNumber(value);
    clickBox->animation = new CircleButtonInitializeAnimation(clickBox, 1);

}

LLNode::LLNode(int value, Vector2 pos) : Node(value, pos, 50), next(nullptr) {
    clickBox = new NumberInputCircleInCamera(pos, radius,3, BLUE, RAYWHITE, RAYWHITE);
    clickBox->setNumber(value);
    clickBox->animation = new CircleButtonInitializeAnimation(clickBox, 1);

}

LLNode::LLNode(int value, float X, float Y) : Node(value, { X,Y }, 50), next(nullptr) {
    clickBox = new NumberInputCircleInCamera({ X,Y }, radius, 3, BLUE, RAYWHITE, RAYWHITE);
    clickBox->setNumber(value);
    clickBox->animation = new CircleButtonInitializeAnimation(clickBox, 1);

}

LLNode::LLNode(int value, float X, float Y, int r) : Node(value, { X,Y }, r), next(nullptr) {
    clickBox = new NumberInputCircleInCamera({ X,Y }, r, 3, BLUE, RAYWHITE, RAYWHITE);
    clickBox->setNumber(value);
    clickBox->animation = new CircleButtonInitializeAnimation(clickBox, 1);
}

LLNode::~LLNode() {
    if (clickBox) delete clickBox;
}