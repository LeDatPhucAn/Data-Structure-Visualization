#include "header/TreapNode.h"
#include "raylib.h"

void TreapNode::detachLeft(){
    left = nullptr;
}

void TreapNode::detachRight(){
    right = nullptr;
}

void TreapNode::attachLeft(TreapNode* node){
    if(left) detachLeft();
    left = node;
}

void TreapNode::attachRight(TreapNode* node){
    if(right) detachRight();
    right = node;
}

void TreapNode::drawNode(TreapNode* node, int x, int y, int xOffset, int yOffset){
    if(!node) return;

    DrawCircle(x, y, 50, WHITE);
    DrawText(TextFormat("%d", node->data), x, y - 10, 25, BLUE);
    DrawText(TextFormat("%d", node->priority), x, y, 15, RED);

    if(node->left){
        DrawLine(x, y, x + xOffset, y + yOffset, WHITE);
        drawNode(node->left, x + xOffset, y + yOffset, xOffset, yOffset);
    }

    if(node->right){
        DrawLine(x, y, x - xOffset, y + yOffset, WHITE);
        drawNode(node->left, x - xOffset, y + yOffset, xOffset, yOffset);
    }
}