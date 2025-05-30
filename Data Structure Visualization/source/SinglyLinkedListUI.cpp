#include "../header/SinglyLinkedListUI.h"
#include "../header/PseudoCode.h"
#include "../header/Animation.h"

bool SinglyLinkedListUI::isInsert = false;
bool SinglyLinkedListUI::isRemove = false;

void SinglyLinkedListUI::cleanupForOperation() {
    animManager.goToLastStep();
    animManager.clear();
    animManager.resume();
}
void SinglyLinkedListUI::insert(int x, int pos) {
    cleanupForOperation();
    isInsert = true;
    isRemove = false;
    if (pos > linkedlist.getListSize()) {
        pos = linkedlist.getListSize() + 1;
    }
    insertParameters = { x,pos };
    linkedlist.insertnode(CodeBlocks,animManager,x, pos);
}
void SinglyLinkedListUI::remove(int x) {
    cleanupForOperation();

    isRemove = true;
    isInsert = false;
    removeParameters = { x, linkedlist.remove(CodeBlocks,animManager,x) };
}

bool SinglyLinkedListUI::search(int x) {
    cleanupForOperation();

    isRemove = false;
    isInsert = false;
    return linkedlist.search(CodeBlocks,animManager,x);
    
}
void SinglyLinkedListUI::drawlinkedlist() {
    
    if (linkedlist.RemoveFirstNode) {
        linkedlist.RemoveFirstNode->draw();
    }
    LLNode* cur = linkedlist.head;
    while (cur) {
        cur->draw();
        cur = cur->next;
    }
    for (auto& edge : linkedlist.Edges) {
        edge->drawArrowEdge();
    }
}

void SinglyLinkedListUI::resetAnimations() {
	Button::resetButtonsAnimations<RectButton>(Buttons);
	Button::resetButtonsAnimations<RectButton>(CodeBlocks);
}
void SinglyLinkedListUI::clearIndicatesAndHighlights() {
    
    LLNode* cur = linkedlist.head;
    while (cur) {
        cur->indicateNode = "";
        cur = cur->next;
    }
    for (int i = 1; i < CodeBlocks.size(); i++) {
        CodeBlocks[i]->unhighlight();
    }
}
void SinglyLinkedListUI::replayOperation() {
    if (isInsert) {

        // complete all animations to get the list after insert
        animManager.goToLastStep();

        animManager.clear();

        // restore the list to the state before insert
        linkedlist.restoreAfterInsert(insertParameters.first, insertParameters.second);

        // add the animations back
        linkedlist.insertnode(CodeBlocks,animManager,insertParameters.first, insertParameters.second);
    }
    else if (isRemove) {

        // complete all animations to get the list after removal
        animManager.goToLastStep();

        animManager.clear();
        
        // restore the list to the state before removal
        linkedlist.randominsert(removeParameters.first, removeParameters.second );

        // add the animations back
        linkedlist.remove(CodeBlocks, animManager, removeParameters.first);
    }

}

void SinglyLinkedListUI::initButtons() {

    /// Code Blocks
    RectButton* OpenCodeBlocks = new TextBox("<");
    OpenCodeBlocks->rect.x = UI::screenWidth - OpenCodeBlocks->rect.width;
    OpenCodeBlocks->rect.y = UI::screenHeight / 4;
    OpenCodeBlocks->rect.height = 0;
    OpenCodeBlocks->isActivated = true;
    RectButton::insertCodeBlock(CodeBlocks, OpenCodeBlocks);

    /// Buttons

    RectButton::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 5));
    Buttons[0]->animation = new RectMoveXAnim(Buttons[0], 0.5);

    RectButton* Value = new TextBox("Value:");
    RectButton* ValueInput = new NumberInputBox(3);
    RectButton* Pos = new TextBox("Pos:");
    RectButton* PosInput = new NumberInputBox(2);
    RectButton* Enter = new TextBox(">");

    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Pos);
    Buttons[0]->insertSubButton(PosInput);

    Buttons[0]->insertSubButton(Enter, [this, ValueInput, PosInput]() {
        insert(ValueInput->getNumber(), PosInput->getNumber());
        if (PosInput->getNumber() == 1) RectButton::insertPseudoCode(CodeBlocks, PseudoCode::LLInsertHead);
        else if (PosInput->getNumber() == 0) return;
        else RectButton::insertPseudoCode(CodeBlocks, PseudoCode::LLInsertPos);
        static_cast<NumberInputBox*>(ValueInput)->clear();
        static_cast<NumberInputBox*>(PosInput)->clear();
     });

    RectButton::insertHeadButton(Buttons, new TextBox("Remove"));
    Buttons[1]->animation = new RectMoveXAnim(Buttons[1], 0.5);

    RectButton* Value1 = new TextBox("Value:");
    RectButton* ValueInput1 = new NumberInputBox(3);
    RectButton* Enter1 = new TextBox(">");
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::LLRemoveHead);
        remove(ValueInput1->getNumber());
        static_cast<NumberInputBox*>(ValueInput1)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Search"));
    Buttons[2]->animation = new RectMoveXAnim(Buttons[2], 0.5);
    Buttons[2]->insertSubButton(new TextBox("Value:"));
    RectButton* ValueInput2 = new NumberInputBox(3);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(new TextBox(">"), [this, ValueInput2]() {
        if (!search(ValueInput2->getNumber())) {
            cout << "NOT FOUND\n";
        }
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::LLSearch);
        static_cast<NumberInputBox*>(ValueInput2)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Clear"));
    Buttons[3]->animation = new RectMoveXAnim(Buttons[3], 0.5);
    Buttons[3]->onClick = [this]() {
		animManager.clear();
        linkedlist.clear();
        };
    RectButton::insertHeadButton(Buttons, new TextBox("LoadFile"));
    Buttons[4]->animation = new RectMoveXAnim(Buttons[4], 0.5);
    Buttons[4]->onClick = [this]() {
        linkedlist.loadFromFile();
        };

    RectButton::insertHeadButton(Buttons, new TextBox("Random"));
    Buttons[5]->animation = new RectMoveXAnim(Buttons[5], 0.5);

    Buttons[5]->onClick = [this]() {
        linkedlist.clear();
		animManager.clear();
        int n = rand() % 10;
        for (int i = 0; i < n; ++i) {
            int x = rand() % 100;
            int pos = rand() % 10;
            linkedlist.randominsert(x, pos);
        }
        };

    updateButtonPositions();
}

void SinglyLinkedListUI::updateButtonPositions() {

    RectButton::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 5);

    RectButton::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);

}

void SinglyLinkedListUI::init() {
    srand(time(nullptr));
    int n = rand() % 10;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        int pos = rand() % 10;
        linkedlist.randominsert(x,pos);
    }

    initButtons();

}

void SinglyLinkedListUI::displaySceneInCamera() {
    drawlinkedlist();
    
}
void SinglyLinkedListUI::displayScene() {
    Button::drawButtons<RectButton>(Buttons);
    Button::drawButtons<RectButton>(CodeBlocks);
}
void SinglyLinkedListUI::updateSceneInCamera(Camera2D cam) {
    
}
void SinglyLinkedListUI::updateScene() {
    if (linkedlist.RemoveFirstNode) {
        linkedlist.RemoveFirstNode->update();
    }
   LLNode* cur = linkedlist.head;
   while (cur) {
       cur->update();
       if (cur->animation)cur->animation->update(GetFrameTime());
       cur = cur->next;
   }
    
    Button::updateButtons<RectButton>(Buttons);
    Button::updateButtons<RectButton>(CodeBlocks);

    
    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

