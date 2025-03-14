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
        while (button) {
            Button* del = button;
            button = button->next;
            delete del;
        }
    }
}
void SinglyLinkedListUI::init() {
    this->insertnode(10, 1);
    this->insertnode(30, 1);
    this->insertnode(40, 1);
    this->insertnode(50, 3);
    this->insertnode(50, 5);

    Buttons.push_back(new TextBox("Insert", 100, UI::screenHeight / 2));
    //Buttons[0]->head = Buttons[0];
    Button* Value = new TextBox("Value:",0,0);
    Button* ValueInput = new NumberInputBox(0,0,3);
    Button* Pos = new TextBox("Pos:", 0, 0);
    Button* PosInput = new NumberInputBox(0, 0, 2);
    Button* Enter = new TextBox(">", 0, 0);
    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Pos);
    Buttons[0]->insertSubButton(PosInput);
    Buttons[0]->insertSubButton(Enter, [this, ValueInput, PosInput]() {
        this->insertnode(ValueInput->getNumber(), PosInput->getNumber());
        });


    Buttons.push_back(new TextBox("Remove", Buttons[0]->rect.x, Buttons[0]->rect.y + Buttons[0]->rect.height));
    //Buttons[0]->head = Buttons[0]
    Button* Value1 = new TextBox("Value:", 0, 0);
    Button* ValueInput1 = new NumberInputBox(0, 0, 3);
    Button* Enter1 = new TextBox(">", 0, 0);
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        this->remove(ValueInput1->getNumber());
        });

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
}