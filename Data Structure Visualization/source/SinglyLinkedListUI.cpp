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
    this->insertnode(30, 1);
    this->insertnode(40, 1);
}
void SinglyLinkedListUI::displayScene() {
    drawlinkedlist();
}
void SinglyLinkedListUI::updateScene() {
    if (IsKeyPressed(KEY_ONE))this->insertnode(40, 2);
    if (IsKeyPressed(KEY_TWO) && this->remove(40)) {
        cout << "REMOVED!\n";
    }

}