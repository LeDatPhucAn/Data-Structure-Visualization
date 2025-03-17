#include "../header/TreapUI.h"


const Vector2 TreapUI::ROOT_POS = { UI::screenWidth / 2, 0 };

TreapUI::TreapUI(SceneHandler* handler) : sceneHandler(handler), root(nullptr) {

    init();
}

void TreapUI::insert(int key) {
    root = treap.insert(root, key, ROOT_POS);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::search(int key) {
    root = treap.search(root, key);
}

void TreapUI::remove(int key) {
    root = treap.remove(root, key);
    reposition(root, ROOT_POS, xOffset, yOffset);
}


void TreapUI::reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset) {
    if (!root) return;

    root->position = pos;

    int leftWidth = treap.getSubtreeWidth(root->leftEdge ? static_cast<TreapNode*> (root->leftEdge->to) : nullptr);
    int rightWidth = treap.getSubtreeWidth(root->rightEdge ? static_cast<TreapNode*> (root->rightEdge->to) : nullptr);

    int newXOffset = max((leftWidth + rightWidth + 1) * 120, 120);

    if (root->leftEdge) {
        Vector2 leftPos = { pos.x - newXOffset, pos.y + yOffset };
        reposition(static_cast<TreapNode*> (root->leftEdge->to), leftPos, newXOffset, yOffset);
    }

    if (root->rightEdge) {
        Vector2 rightPos = { pos.x + newXOffset, pos.y + yOffset };
        reposition(static_cast<TreapNode*> (root->rightEdge->to), rightPos, newXOffset, yOffset);
    }
}
void TreapUI::drawTreapNode(TreapNode* curr){
    if(!curr) return;

    static const float width = 120.0f;
    static const float height = 100.0f;
    static const float dataWidth = 80.0f;
    static const float priorityWidth = 40.0f;

    Vector2 pos = curr->position;

    DrawRectangle(pos.x - width / 2, pos.y - height / 2, width, height, {255, 203, 203, 255});
    DrawRectangle(pos.x - width / 2 + dataWidth, pos.y - height / 2, priorityWidth, height, {69, 180, 238, 255});

    DrawRectangleLines(pos.x - width / 2, pos.y - height / 2, width, height, BLACK);
    DrawLine(pos.x - width / 2 + dataWidth, pos.y - height / 2, pos.x - width / 2 + dataWidth, pos.y + height / 2, BLACK);

    string value = to_string(curr->data).substr(0, 5);
    Vector2 valueTextSize = MeasureTextEx(GetFontDefault(), value.c_str(), 30.0f, 2.0f);
    string priority = to_string(curr->priority);
    Vector2 priorityTextSize = MeasureTextEx(GetFontDefault(), priority.c_str(), 20.0f, 2.0f);

    DrawText(value.c_str(), pos.x - width / 2 + dataWidth / 2 - valueTextSize.x / 2, pos.y - valueTextSize.y / 2, 30, DARKGRAY);
    DrawText(priority.c_str(), pos.x - width / 2 + dataWidth + priorityWidth / 2 - priorityTextSize.x / 2, pos.y - priorityTextSize.y / 2, 20, DARKPURPLE);
}

void TreapUI::drawTreapLink(Edge* edge) {
    if (!edge || !edge->from || !edge->to) return;
    edge->drawTreapEdge();
}

void TreapUI::drawTreap(TreapNode* curr){
    if(!curr) return;

    drawTreapNode(curr);

    if (curr->leftEdge) {
        drawTreap(static_cast<TreapNode*>(curr->leftEdge->to));
        drawTreapLink(curr->leftEdge);
    }

    if (curr->rightEdge) {
        drawTreap(static_cast<TreapNode*>(curr->rightEdge->to));
        drawTreapLink(curr->rightEdge);
    }
}

void TreapUI::init(){
    srand(time(nullptr));
    int n = rand() % 10;
    for(int i = 0; i < n; ++i){
        int x = rand() % 100;
        insert(x);
    }
}