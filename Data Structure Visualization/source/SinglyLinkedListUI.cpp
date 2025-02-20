#include "../header/SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
    LLNode* cur = this->head;
    int i = 0;
    while (cur) {
        drawnode(cur->data, headX + i, headY, radius);
        drawlink(headX + i + radius, headY - radius);
        i += 200;
        cur = cur->next;
    }

    drawtext2("NULL", headX + i, headY, BLUE);
}