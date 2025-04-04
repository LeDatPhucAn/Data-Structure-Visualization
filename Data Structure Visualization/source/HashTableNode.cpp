#include "../header/HashTableNode.h"
#include "../header/UI.h"

HashTableNode::HashTableNode(int number, int x, int y, float radius)
    : NumberInputCircleInCamera({ static_cast<float>(x), static_cast<float>(y) }, radius, number, 3) {
    centerX = x;
    centerY = y;
    originalNumber = number;
}