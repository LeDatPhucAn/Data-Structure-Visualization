#include "../header/HashTableUI.h"
#include "../header/PseudoCode.h"
#include "../header/Animation.h"
#include "../header/LLNode.h"
using namespace std;
void HashTableUI::init() {
    srand(time(nullptr));
    int n = rand() % 5 + 1;
    for (int i = 0; i < n; ++i) {
        insertHashTable(rand() % 100);
    }
    initButtons();
}

void HashTableUI::initButtons() {
    /// Code Blocks
    Button* OpenCodeBlocks = new TextBox("<");
    OpenCodeBlocks->rect.x = UI::screenWidth - OpenCodeBlocks->rect.width;
    OpenCodeBlocks->rect.y = UI::screenHeight / 4;
    OpenCodeBlocks->rect.height = 0;
    OpenCodeBlocks->isActivated = true;
    Button::insertCodeBlock(CodeBlocks, OpenCodeBlocks);

    /// Buttons
    Button::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 4));
    Buttons[0]->animation = new ButtonMoveXAnimation(Buttons[0], 0.5f);
    Button* Value = new TextBox("Value:");
    Button* ValueInput = new NumberInputBox(3);
    Button* Enter = new TextBox(">");
    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Enter, [this, ValueInput]() {
        int value = ValueInput->getNumber();
        if (value >= 0) {
            insertHashTable(value);
            Button::insertPseudoCode(CodeBlocks, PseudoCode::HashTableInsert);
            static_cast<NumberInputBox*>(ValueInput)->clear();
        }
        });

    Button::insertHeadButton(Buttons, new TextBox("Remove"));
    Buttons[1]->animation = new ButtonMoveXAnimation(Buttons[1], 0.5f);
    Button* Value1 = new TextBox("Value:");
    Button* ValueInput1 = new NumberInputBox(3);
    Button* Enter1 = new TextBox(">");
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        int value = ValueInput1->getNumber();
        if (value >= 0) {
            deleteHashTable(value);
            Button::insertPseudoCode(CodeBlocks, PseudoCode::HashTableRemove);
            static_cast<NumberInputBox*>(ValueInput1)->clear();
        }
        });

    Button::insertHeadButton(Buttons, new TextBox("Search"));
    Buttons[2]->animation = new ButtonMoveXAnimation(Buttons[2], 0.5f);
    Button* Value2 = new TextBox("Value:");
    Button* ValueInput2 = new NumberInputBox(3);
    Button* Enter2 = new TextBox(">");
    Buttons[2]->insertSubButton(Value2);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(Enter2, [this, ValueInput2]() {
        int value = ValueInput2->getNumber();
        bool found = findHashTable(value);
        std::cout << "Value " << value << " found: " << (found ? "Yes" : "No") << std::endl;
        Button::insertPseudoCode(CodeBlocks, PseudoCode::HashTableSearch);
        static_cast<NumberInputBox*>(ValueInput2)->clear();
        });

    Button::insertHeadButton(Buttons, new TextBox("Clear"));
    Buttons[3]->animation = new ButtonMoveXAnimation(Buttons[3], 0.5f);
    Buttons[3]->onClick = [this]() {
        for (int i = 0; i < size; ++i) {
            for (auto node : data[i]) {
                delete node;
            }
            data[i].clear();
        }
        deleteEdges();
        };

    Button::insertHeadButton(Buttons, new TextBox("Random"));
    Buttons[4]->animation = new ButtonMoveXAnimation(Buttons[4], 0.5f);
    Buttons[4]->onClick = [this]() {
        for (int i = 0; i < size; ++i) {
            for (auto node : data[i]) {
                delete node;
            }
            data[i].clear();
        }
        deleteEdges();
        int n = rand() % 10;
        for (int i = 0; i < n; ++i) {
            insertHashTable(rand() % 100);
        }
        };

    updateButtonPositions();
}

void HashTableUI::resetAnimations() {
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
    for (int i = 0; i < size; ++i) {
        for (auto node : data[i]) {
            if (node->animation) {
                node->animation->reset();
            }
        }
    }
}

void HashTableUI::updateButtonPositions() {
    Button::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 4);
    Button::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);

    for (int i = 0; i < size; ++i) {
        adjustPos(i);
    }
}

void HashTableUI::drawHashTable() {
    for (int i = 0; i < size; ++i) {
        float bucketX = startX + i * (Width + spacing);
        float bucketY = startY;
        Rectangle bucketRec = { bucketX, bucketY, Width, Height };
        DrawRectangleLinesEx(bucketRec, 2.0f, BLACK);
        drawtext2(to_string(i), bucketX + Width / 2, bucketY - 20, DARKGRAY);

        for (auto node : data[i]) {
            if (node->animation) {
                node->animation->update(GetFrameTime());
            }
            drawNode(node);
        }

        for (auto edge : Edges) {
            if (edge->from && edge->to) {
                edge->drawEdge();
            }
        }
    }
}

void HashTableUI::displaySceneInCamera() {
    drawHashTable();
}

void HashTableUI::displayScene() {
    Button::drawButtons(Buttons);
    Button::drawButtons(CodeBlocks);
}

void HashTableUI::updateScene() {
    Button::updateButtons(Buttons);
    Button::updateButtons(CodeBlocks);

    for (int i = 0; i < size; ++i) {
        for (auto node : data[i]) {
            // node->update();
            if (node->animation) {
                node->animation->update(GetFrameTime());
            }
        }
    }

    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void HashTableUI::updateSceneInCamera(Camera2D cam) {
    /*
    for (int i = 0; i < size; ++i) {
        for (auto node : data[i]) {
            node->update();
        }
    }
    */
}
