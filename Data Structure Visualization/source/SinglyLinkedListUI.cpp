#include "../header/SinglyLinkedListUI.h"
#include "../header/PseudoCode.h"
void SinglyLinkedListUI::drawlinkedlist() {
    LLNode* cur = this->head;
    while (cur) {
        cur->draw();
        cur = cur->next;
    }
    for (auto& edge : Edges) {
        edge->drawArrowEdge();
    }
}

void SinglyLinkedListUI::resetAnimations() {
	SceneHandler::MenuButton->animation->reset();
	for (auto& button : Buttons) {
        if (button->animation) {
            button->animation->reset();
        }
	}
	for (auto& button : CodeBlocks) {
        if (button->animation) {
            button->animation->reset();
        }
	}
}

void SinglyLinkedListUI::initButtons() {
    
    /// Code Blocks
    Button::insertCodeBlock(CodeBlocks, new TextBox("Code Blocks:", UI::screenWidth * 5 / 8, UI::screenHeight / 4));
    Button::insertPseudoCode(CodeBlocks, PseudoCode::LLInsert);
    /// Buttons
    Button::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 5));
	Buttons[0]->animation = new ButtonMoveXAnimation(Buttons[0], 0.5);


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
  
    Button::insertHeadButton(Buttons, new TextBox("Clear"));
    Buttons[3]->animation = new ButtonMoveXAnimation(Buttons[3], 0.5);
    Buttons[3]->onClick = [this]() {
        this->deletelist();
        this->deleteEdges();
        };

    Button::insertHeadButton(Buttons, new TextBox("Random"));
    Buttons[4]->animation = new ButtonMoveXAnimation(Buttons[4], 0.5);

    Buttons[4]->onClick = [this]() {
        this->deletelist();
        this->deleteEdges();
        int n = rand() % 10;
        for (int i = 0; i < n; ++i) {
            int x = rand() % 100;
            int pos = rand() % 10;
            this->insertnode(x, pos);
        }
    };
    
    updateButtonPositions();
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
void SinglyLinkedListUI::updateSceneInCamera(Camera2D cam) {
    /*Button::isCollision = false;

    LLNode* cur = this->head;
    while (cur) {
        cur->update();
        cur = cur->next;
    }*/
}
void SinglyLinkedListUI::updateScene() {

    Button::isCollision = false;

    LLNode* cur = this->head;
    while (cur) {
        cur->update();
        if (cur->animation)cur->animation->update(GetFrameTime());
        cur = cur->next;
    }
    SceneHandler::MenuButton->update();
    Button::updateButtons(Buttons);
    Button::updateButtons(CodeBlocks);

    
    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

