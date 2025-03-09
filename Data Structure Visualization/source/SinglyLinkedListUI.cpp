#include "../header/SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
    LLNode* cur = this->head;
    int i = 0;
    while (cur) {
        UI::drawnode(cur->data, headX + i, headY, radius);
        UI::drawlink(headX + i + radius, headY - radius);
        i += 200;
        cur = cur->next;
    }

    UI::drawtext2("NULL", headX + i, headY, BLUE);
}
void SinglyLinkedListUI::init() {
    this->insertnode(10, 1);
    this->insertnode(20, 2);
    this->insertnode(30, 1);
    this->insertnode(40, 1);
    this->remove(20);
    this->insertnode(40, 1);
    this->remove(40);
}
void SinglyLinkedListUI::displayScene() {
    // Draw the 3d grid, rotated 90 degrees and centered around 0,0 
        // just so we have something in the XY plane
    rlPushMatrix();
    rlTranslatef(0, 10000, 0);
    rlRotatef(90, 1, 0, 0);
    DrawGrid(1000, 100);
    rlPopMatrix();

    // Draw a reference circle
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);
    drawlinkedlist();
}
void SinglyLinkedListUI::updateScene() {
    if (IsKeyPressed(KEY_ONE))this->insertnode(40, 2);
    if (IsKeyPressed(KEY_TWO) && this->remove(40)) {
        cout << "REMOVED!\n";
    }
}