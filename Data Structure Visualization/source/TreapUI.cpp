#include "../header/TreapUI.h"

const Vector2 TreapUI::ROOT_POS = {GetScreenWidth() / 2, 0};

TreapUI::TreapUI(){
    root = nullptr;
}

void TreapUI::insert(int key){
    root = treap.insert(root, key, ROOT_POS);
}

void TreapUI::search(int key){
    root = treap.search(root, key);
}

void TreapUI::remove(int key){
    root = treap.remove(root, key);
}



void TreapUI::drawTreapNode(TreapNode* curr, const Vector2 pos){
    static const float width = 60.0f;
    static const float height = 30.0f;
    static const float dataWidth = 40.0f;
    static const float priorityWidth = 20.0f;

    DrawRectangle(pos.x - width / 2, pos.y - height / 2, width, height, {255, 203, 203, 255});
    DrawRectangleLines(pos.x - width / 2, pos.y - height / 2, width, height, BLACK);
    DrawLine(pos.x - width / 2 + dataWidth, pos.y - height / 2, pos.x - width / 2 + dataWidth, pos.y + height / 2, BLACK);
    string value = to_string(curr->data);
    Vector2 valueTextSize = MeasureTextEx(GetFontDefault(), value.c_str(), 20.0f, 2.0f);
    string priority = to_string(curr->priority);
    Vector2 priorityTextSize = MeasureTextEx(GetFontDefault(), priority.c_str(), 15.0f, 2.0f);
    DrawText(value.c_str(), pos.x - width / 2 + dataWidth / 2 - valueTextSize.x / 2, pos.y - valueTextSize.y / 2, 20, DARKGRAY);
    DrawText(priority.c_str(), pos.x - width / 2 + dataWidth + priorityWidth / 2 - priorityTextSize.x / 2, pos.y - priorityTextSize.y / 2, 15, RED);
}

void TreapUI::drawTreap(TreapNode* curr, Vector2 pos, const int xOffset, const int yOffset){
    if (!curr) return;

    drawTreapNode(curr, pos);
    
    int leftWidth = getSubtreeWidth(curr->left);
    int rightWidth = getSubtreeWidth(curr->right);
    int newXOffset = max((leftWidth + rightWidth) * 15, 30);

    if (curr->left) {
        Vector2 leftPos = {pos.x - newXOffset, pos.y + yOffset};
        drawTreap(curr->left, leftPos, newXOffset, yOffset);
        drawTreapLink(pos, leftPos, true);
    }

    if (curr->right) {
        Vector2 rightPos = {pos.x + newXOffset, pos.y + yOffset};
        drawTreap(curr->right, rightPos, newXOffset, yOffset);
        drawTreapLink(pos, rightPos, false);
    }
}

void TreapUI::drawTreap(){
    drawTreap(root, rootPos, xOffset, yOffset);
}
