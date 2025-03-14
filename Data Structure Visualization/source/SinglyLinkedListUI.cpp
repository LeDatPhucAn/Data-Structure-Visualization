#include "../header/SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
    LLNode* cur = this->head;
    while (cur) {
        UI::drawNode(cur);
        cur = cur->next;
    }
    for (auto& edge : Edges) {
        edge->drawEdge();
    }
}
void SinglyLinkedListUI::deleteButtons(){
    for (auto button : Buttons) {
        delete button;
    }
}
void SinglyLinkedListUI::init() {
    this->insertnode(10, 1);
    this->insertnode(30, 1);
    this->insertnode(40, 1);
    this->insertnode(50, 3);
    this->insertnode(50, 5);

    Buttons.push_back(new TextBox("Insert", 100, UI::screenHeight / 2));
    Buttons[0]->onClick = [this]() {
        this->insertnode(60, 2); // Example action: Insert a node with value 60 at position 1
        };
    Buttons.push_back(new TextBox("Remove", Buttons[0]->rect.x, Buttons[0]->rect.y + Buttons[0]->rect.height));
    Buttons[1]->onClick = [this]() {
        this->remove(60); 
        };

    Buttons.push_back(new TextBox("Menu", 50, 50));
    Buttons[2]->onClick = [this]() {
        this->scenehandler->changeScene(MENU);
        };

}
void SinglyLinkedListUI::displaySceneInCamera() {
    drawlinkedlist();
    
}
void SinglyLinkedListUI::displayScene() {
    for (auto button : Buttons) {
        button->draw();
    }
}
void SinglyLinkedListUI::updateScene() {
    for (auto button : Buttons) {
        button->update();
    }
    if (IsKeyPressed(KEY_ONE))this->insertnode(40, 2);
    if (IsKeyPressed(KEY_TWO) && this->remove(40)) {
        cout << "REMOVED!\n";
    }

}