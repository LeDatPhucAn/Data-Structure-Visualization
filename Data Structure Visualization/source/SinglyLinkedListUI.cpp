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

void SinglyLinkedListUI::initButtons() {
    const char* pseudocode =
        "Function insertnode(x, pos):\n"
        "    If pos < 1:\n"
        "        Return  // Invalid position\n"
        "\n"
        "    If pos is 1 OR list is empty:\n"
        "        Create a new node (temp) with value x\n"
        "        Set temp’s next pointer to head\n"
        "        Adjust temp’s position\n"
        "        Add an edge between temp and head\n"
        "        Update head to temp\n"
        "        Return\n"
        "\n"
        "    Set cur to head\n"
        "    Loop from 1 to (pos - 1):\n"
        "        If cur is NULL:\n"
        "            Return  // Position is out of range\n"
        "        Move cur to next node\n"
        "\n"
        "    If cur is NULL:\n"
        "        Return  // Position is invalid\n"
        "\n"
        "    Create a new node (newnode) with value x\n"
        "    Set newnode’s next pointer to cur’s next\n"
        "    Add an edge between newnode and cur’s next\n"
        "    Remove the edge between cur and cur’s next\n"
        "    Set cur’s next to newnode\n"
        "    Adjust newnode’s position\n"
        "    Add an edge between cur and newnode\n";
    /// Code Blocks
    Button::insertCodeBlock(CodeBlocks, new TextBox("Code Blocks:", UI::screenWidth * 5 / 8, UI::screenHeight / 4));
    Button::insertCodeBlock(CodeBlocks, new CodeBlock(pseudocode));
    /// Buttons
    Button::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 4));

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
        Button::insertCodeBlock(CodeBlocks,
            new CodeBlock("Inserting " + to_string(ValueInput->getNumber()) + " to Position: " + to_string(PosInput->getNumber())));
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


    

}

void SinglyLinkedListUI::updateButtonPositions() {

    SceneHandler::MenuButton->setPosition(UI::screenWidth / 100, UI::screenHeight / 100);

    Button::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 4);

    Button::setHeadPosition(CodeBlocks, UI::screenWidth * 5 / 8, UI::screenHeight / 4);

}
void SinglyLinkedListUI::init() {

    srand(time(nullptr));
    int n = rand() % 10;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        int pos = rand() % 10;
        this->insertnode(x,pos);
    }

    initButtons();

}

void SinglyLinkedListUI::displaySceneInCamera() {
    drawlinkedlist();
    
}
void SinglyLinkedListUI::displayScene() {
    SceneHandler::MenuButton->draw();
    Button::drawButtons(Buttons);
    Button::drawButtons(CodeBlocks);
}
void SinglyLinkedListUI::updateScene() {

    Button::isCollision = false;


    SceneHandler::MenuButton->update();
    Button::updateButtons(Buttons);
    Button::updateButtons(CodeBlocks);

    
    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}