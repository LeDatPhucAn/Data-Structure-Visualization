#include "../header/SinglyLinkedListUI.h"
#include "../header/PseudoCode.h"
#include "../header/Animation.h"
#include <map>
void SinglyLinkedListUI::insert(int x, int pos) {
    animManager.clear();
    deepCopy(linkedlist, initialState);
    linkedlist.insertnode(CodeBlocks,animManager,x, pos);
}
void SinglyLinkedListUI::remove(int x) {
	animManager.clear();
    linkedlist.remove(CodeBlocks,animManager,x);
}

bool SinglyLinkedListUI::search(int x) {
    animManager.clear();
    return linkedlist.search(CodeBlocks,animManager,x);
    
}
void SinglyLinkedListUI::drawlinkedlist() {
    
    LLNode* cur = linkedlist.head;
    while (cur) {
        cur->draw();
        cur = cur->next;
    }
    for (auto& edge : linkedlist.Edges) {
        edge->drawArrowEdge();
    }
}
void SinglyLinkedListUI::deepCopy(const LinkedList& original, LinkedList& copy) {
    // Clear the copy to avoid leaks
    copy.clear();

    // Step 1: Copy the nodes
    if (!original.head) {
        copy.head = nullptr;
    }
    else {
        copy.head = new LLNode(original.head->getNumber(), original.head->getCenter());
        copy.head->indicateNode = original.head->indicateNode;
        copy.head->noDraw = original.head->noDraw;
        if (original.head->onClick) {
            copy.head->onClick = original.head->onClick;
        }

        LLNode* current = copy.head;
        LLNode* otherCurrent = original.head->next;
        while (otherCurrent) {
            current->next = new LLNode(otherCurrent->getNumber(), otherCurrent->getCenter());
            current->next->indicateNode = otherCurrent->indicateNode;
            current->next->noDraw = otherCurrent->noDraw;
            if (otherCurrent->onClick) {
                current->next->onClick = otherCurrent->onClick;
            }
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

    // Step 2: Copy the edges
    std::map<LLNode*, LLNode*> nodeMap;
    LLNode* orig = original.head;
    LLNode* copyNode = copy.head;
    while (orig && copyNode) {
        nodeMap[orig] = copyNode;
        orig = orig->next;
        copyNode = copyNode->next;
    }

    for (auto edge : original.Edges) {
        LLNode* from = nodeMap[dynamic_cast<LLNode*>(edge->from)];
        LLNode* to = nodeMap[dynamic_cast<LLNode*>(edge->to)];
        if (from && to) {
            CBEdge* newEdge = new CBEdge(from, to);
            newEdge->noDraw = edge->noDraw;
            copy.Edges.push_back(newEdge);
        }
    }
}
//void SinglyLinkedListUI::deepCopy(const LinkedList& original, LinkedList& copy) {
//
//    if (copy.head != nullptr)copy.clear();
//    // Step 1: Copy the nodes
//    if (!original.head) {
//        copy.head = nullptr;
//    }
//    else {
//        copy.head = new LLNode(original.head->getNumber(),original.head->getCenter()); // Assumes LLNode has a copy constructor
//        LLNode* current = copy.head;
//        LLNode* otherCurrent = original.head->next;
//        while (otherCurrent) {
//            copy.randominsert(otherCurrent->getNumber(), 99);
//            otherCurrent = otherCurrent->next;
//        }
//    }
//
//    // Step 2: Copy the edges
//
//    LLNode* copyNode = copy.head;
//
//    LLNode* cur = copyNode;
//    while (cur) {
//        CBEdge::addEdge(copy.Edges, cur, cur->next);
//        cur = cur->next;
//    }
//
//    //std::map<LLNode*, LLNode*> nodeMap; // Maps original nodes to copied nodes
//    //LLNode* orig = original.head;
//    //while (orig) {
//    //    nodeMap[orig] = copyNode;
//    //    orig = orig->next;
//    //    copyNode = copyNode->next;
//    //}
//
//    //for (auto edge : original.Edges) {
//    //    LLNode* from = nodeMap[edge->from];
//    //    LLNode* to = nodeMap[edge->to];
//    //    CBEdge* newEdge = new CBEdge(from, to); // Assumes CBEdge constructor takes from/to pointers
//    //    copy->Edges.push_back(newEdge);
//    //}
//    
//}

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

