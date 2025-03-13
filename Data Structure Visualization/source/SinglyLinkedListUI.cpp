#include "../header/SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
    LLNode* cur = this->head;
    while (cur) {
        UI::drawNode(cur);
        cur = cur->next;
    }
    for (auto& edge : Edges) {
        edge.drawEdge();
    }
}
void SinglyLinkedListUI::init() {
    this->insertnode(10, 1);
    this->insertnode(30, 1);
    this->insertnode(40, 1);
    this->insertnode(50, 3);
    this->insertnode(50, 5);
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