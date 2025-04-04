#include "../header/HashTableNode.h"
#include "../header/UI.h"

HashTableNode::HashTableNode(int number, int x, int y, float radius)
    : NumberInputCircleInCamera({ static_cast<float>(x), static_cast<float>(y) }, radius, number, 3) {
    centerX = x;
    centerY = y;
    originalNumber = number;
}

void HashTableNode::draw() {
    DrawCircleV(center, radius * 4 / 5, FillColor);
    DrawRing(center, radius * 4 / 5, radius, 0, 360, 100, RingColor);
    UI::drawtext2(inputText, center.x, center.y, TextColor);
    if (Texting && (framesCounter / 20) % 2 == 0) {
        Vector2 textSize = MeasureTextEx(UI::font, inputText.c_str(), UI::fontSize, UI::spacing);
        string underscore = inputText + "_";
        DrawText(underscore.c_str(), center.x - textSize.x / 2, center.y - UI::fontSize / 2, UI::fontSize, TextColor);
    }
}