#include "../header/SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
    LLNode* cur = this->head;
    while (cur) {
        UI::drawNode(cur);
        cur = cur->next;
    }
    for (auto& edge : Edges) {
        edge->drawLLEdge();
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

    Button::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight*3/4));

    Button* Value = new TextBox("Value:");
    Button* ValueInput = new NumberInputBox(3);
    Button* Pos = new TextBox("Pos:");
    Button* PosInput = new NumberInputBox(2);
    Button* Enter = new TextBox(">");

    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Pos);
    Buttons[0]->insertSubButton(PosInput);

    Buttons[0]->insertSubButton(Enter, [this, ValueInput, PosInput]() {
        this->insertnode(ValueInput->getNumber(), PosInput->getNumber());
        });

    Button::insertHeadButton(Buttons, new TextBox("Remove"));
    Button* Value1 = new TextBox("Value:");
    Button* ValueInput1 = new NumberInputBox(3);
    Button* Enter1 = new TextBox(">");
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1, [this, ValueInput1]() {
        this->remove(ValueInput1->getNumber());
        });
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        this->remove(ValueInput1->getNumber());
        });
    Button::insertHeadButton(Buttons, new TextBox("Search"));
    Buttons[2]->insertSubButton(new TextBox("Value:"));

    Button* ValueInput2 = new NumberInputBox(3);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(new TextBox(">"), [this, ValueInput2]() {
        this->search(ValueInput2->getNumber());
        });

    Buttons.push_back(new TextBox("Menu", 50, 50));
    Buttons[3]->onClick = [this]() {
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
    Button::isCollision = false;
    for (auto button : Buttons) {
        button->update();
    }
    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}