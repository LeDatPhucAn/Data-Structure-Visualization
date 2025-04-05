#include "../header/HashTableUI.h"
#include "../header/PseudoCode.h"
#include "../header/Animation.h"

void HashTableUI::drawHashTable() {
    for (int i = 0; i < hashtable.bucketCount; i++) {
        Rectangle bucketRect = { 100 + i * 200 - 50, 100, 100, 50 };
        DrawRectangleRec(bucketRect, LIGHTGRAY);
        DrawRectangleLines(bucketRect.x, bucketRect.y, bucketRect.width, bucketRect.height, DARKGRAY);
        UI::drawtext2(std::to_string(i), bucketRect.x + bucketRect.width / 2, bucketRect.y + bucketRect.height / 2, BLACK);

        LLNode* cur = hashtable.buckets[i];
        while (cur) {
            cur->draw();
            cur = cur->next;
        }
    }
    for (auto& edge : hashtable.Edges) {
        edge->drawArrowEdge();
    }
}

void HashTableUI::insert(int x) {
    hashtable.insertNode(x);
}

void HashTableUI::remove(int x) {
    hashtable.remove(x);
}

bool HashTableUI::search(int x) {
    int idx = hashtable.hashFunction(x);
    LLNode* cur = hashtable.buckets[idx];
    while (cur) {
        if (cur->getNumber() == x) {
            animManager.addAnimation(new CircleHighLightAnim(cur, 2, GREEN, RAYWHITE, GREEN));
            return true;
        }
        animManager.addAnimation(new CircleHighLightAnim(cur, 1));
        for (auto& edge : hashtable.Edges) {
            if (edge->from == cur) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 1));
                break;
            }
        }
        cur = cur->next;
    }
    return false;
}

void HashTableUI::resize(int newSize) {
    hashtable.resize(newSize);
}

void HashTableUI::init() {
    srand(time(nullptr));
    int n = rand() % 10;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        hashtable.randomInsert(x);
    }
    initButtons();
}

void HashTableUI::initButtons() {
    RectButton* OpenCodeBlocks = new TextBox("<");
    OpenCodeBlocks->rect.x = UI::screenWidth - OpenCodeBlocks->rect.width;
    OpenCodeBlocks->rect.y = UI::screenHeight / 4;
    OpenCodeBlocks->rect.height = 0;
    OpenCodeBlocks->isActivated = true;
    RectButton::insertCodeBlock(CodeBlocks, OpenCodeBlocks);

    RectButton::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 5));
    Buttons[0]->animation = new RectMoveXAnim(Buttons[0], 0.5);
    RectButton* Value = new TextBox("Value:");
    RectButton* ValueInput = new NumberInputBox(3);
    RectButton* Enter = new TextBox(">");
    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Enter, [this, ValueInput]() {
        insert(ValueInput->getNumber());
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableInsert);
        static_cast<NumberInputBox*>(ValueInput)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Remove"));
    Buttons[1]->animation = new RectMoveXAnim(Buttons[1], 0.5);
    RectButton* Value1 = new TextBox("Value:");
    RectButton* ValueInput1 = new NumberInputBox(3);
    RectButton* Enter1 = new TextBox(">");
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        remove(ValueInput1->getNumber());
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableRemove);
        static_cast<NumberInputBox*>(ValueInput1)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Search"));
    Buttons[2]->animation = new RectMoveXAnim(Buttons[2], 0.5);
    RectButton* Value2 = new TextBox("Value:");
    RectButton* ValueInput2 = new NumberInputBox(3);
    Buttons[2]->insertSubButton(Value2);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(new TextBox(">"), [this, ValueInput2]() {
        if (!search(ValueInput2->getNumber())) {
            std::cout << "NOT FOUND\n";
        }
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableSearch);
        static_cast<NumberInputBox*>(ValueInput2)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Clear"));
    Buttons[3]->animation = new RectMoveXAnim(Buttons[3], 0.5);
    Buttons[3]->onClick = [this]() { hashtable.clear(); };

    RectButton::insertHeadButton(Buttons, new TextBox("Random"));
    Buttons[4]->animation = new RectMoveXAnim(Buttons[4], 0.5);
    Buttons[4]->onClick = [this]() {
        hashtable.clear();
        int n = rand() % 10;
        for (int i = 0; i < n; ++i) {
            int x = rand() % 100;
            hashtable.randomInsert(x);
        }
        };

    RectButton::insertHeadButton(Buttons, new TextBox("Bucket"));
    Buttons[5]->animation = new RectMoveXAnim(Buttons[5], 0.5);
    RectButton* BucketInput = new NumberInputBox(2);
    Buttons[5]->insertSubButton(new TextBox("Size:"));
    Buttons[5]->insertSubButton(BucketInput);
    Buttons[5]->insertSubButton(new TextBox(">"), [this, BucketInput]() {
        int newSize = BucketInput->getNumber();
        if (newSize > 0) {
            resize(newSize);
        }
        static_cast<NumberInputBox*>(BucketInput)->clear();
        });

    updateButtonPositions();
}

void HashTableUI::resetAnimations() {
    Button::resetButtonsAnimations<RectButton>(Buttons);
    Button::resetButtonsAnimations<RectButton>(CodeBlocks);
}

void HashTableUI::updateButtonPositions() {
    RectButton::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 5);
    RectButton::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);
}

void HashTableUI::displaySceneInCamera() {
    drawHashTable();
}

void HashTableUI::displayScene() {
    Button::drawButtons<RectButton>(Buttons);
    Button::drawButtons<RectButton>(CodeBlocks);
}

void HashTableUI::updateScene() {
    for (int i = 0; i < hashtable.bucketCount; i++) {
        LLNode* cur = hashtable.buckets[i];
        while (cur) {
            cur->update();
            if (cur->animation) cur->animation->update(GetFrameTime());

            if (cur->checkCollision() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                selectedNode = cur;
                selectedBucketIdx = i;
            }
            if (selectedNode == cur && GetGestureDetected() == GESTURE_TAP && !cur->checkCollision()) {
                int oldValue = selectedNode->getNumber();
                int newValue = cur->getNumber();
                if (oldValue != newValue) {
                    hashtable.removeFromBucket(oldValue, selectedBucketIdx);
                    hashtable.insertNode(newValue);
                }
                selectedNode = nullptr;
                selectedBucketIdx = -1;
            }
            cur = cur->next;
        }
    }
    Button::updateButtons<RectButton>(Buttons);
    Button::updateButtons<RectButton>(CodeBlocks);
    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void HashTableUI::updateSceneInCamera(Camera2D cam) {}
