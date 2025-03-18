#include "../header/SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
    LLNode* cur = this->head;
    while (cur) {
        UI::drawNode(cur);
        cur = cur->next;
    }
    for (auto& edge : Edges) {
        edge->drawArrowEdge();
    }
}
void SinglyLinkedListUI::deleteButtons(vector<Button*>& Buttons){
    for (auto button : Buttons) {
        while (button) {
            Button* del = button;
            button = button->next;
            delete del;
        }
    }
}
void SinglyLinkedListUI::drawButtons(vector<Button*>&Buttons) {
    for (auto button : Buttons) {
        button->draw();
    }
}
void SinglyLinkedListUI::updateButtons(vector<Button*>&Buttons) {
    for (auto button : Buttons) {
        button->update();
    }
}
void SinglyLinkedListUI::init() {
    srand(time(nullptr));
    int n = rand() % 10;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        int pos = rand() % 10;
        this->insertnode(x,pos);
    }
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
        static_cast<NumberInputBox*>(ValueInput)->clear();
        static_cast<NumberInputBox*>(PosInput)->clear();
        });

    Button::insertHeadButton(Buttons, new TextBox("Remove"));
    Button* Value1 = new TextBox("Value:");
    Button* ValueInput1 = new NumberInputBox(3);
    Button* Enter1 = new TextBox(">");
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        this->remove(ValueInput1->getNumber());
        static_cast<NumberInputBox*>(ValueInput1)->clear();
        });

    Button::insertHeadButton(Buttons, new TextBox("Search"));
    Buttons[2]->insertSubButton(new TextBox("Value:"));
    Button* ValueInput2 = new NumberInputBox(3);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(new TextBox(">"), [this, ValueInput2]() {
        this->search(ValueInput2->getNumber());
        static_cast<NumberInputBox*>(ValueInput2)->clear();
        });

    Buttons.push_back(new TextBox("Menu", 50, 50));
    Buttons[3]->onClick = [this]() {
        this->scenehandler->changeScene(MENU);
        };
    
    /// Code Blocks
    Button::insertHeadButton(CodeBlocks, new TextBox("Code Block:", UI::screenWidth * 5 / 8, UI::screenHeight * 3 / 4));

}

void SinglyLinkedListUI::displaySceneInCamera() {
    drawlinkedlist();
    
}
void SinglyLinkedListUI::displayScene() {
    drawButtons(Buttons);
    drawButtons(CodeBlocks);
}
void SinglyLinkedListUI::updateScene() {
    Button::isCollision = false;
    updateButtons(Buttons);
    updateButtons(CodeBlocks);
    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}