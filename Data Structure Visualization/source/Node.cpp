#include "../header/Node.h"
#include "../header/Animation.h"
Node::Node(int value, Vector2 pos, float r) : data(value), position(pos), radius(r) {
    animation = new NodeInitializeAnimation(this, 1);
}