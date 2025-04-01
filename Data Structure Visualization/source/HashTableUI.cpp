#include "../header/UI.h"
#include "../header/HashTableUI.h"
#include "../header/SceneHandler.h"
#include "../header/Button.h"
#include "../header/PseudoCode.h"

void HashTableUI::init() {
    insertHashTable(10); // example
    insertHashTable(15);
    insertHashTable(7);
    insertHashTable(12);

    initButtons();
}

void HashTableUI::initButtons() {

    /// Code Blocks
    RectButton* OpenCodeBlocks = new TextBox("<");
    OpenCodeBlocks->rect.x = UI::screenWidth - OpenCodeBlocks->rect.width;
    OpenCodeBlocks->rect.y = UI::screenHeight / 4;
    OpenCodeBlocks->rect.height = 0;
    OpenCodeBlocks->isActivated = true;
    RectButton::insertCodeBlock(CodeBlocks, OpenCodeBlocks);

    /// Buttons
    RectButton* InsertButton = new TextBox("Insert", 100, UI::screenHeight * 3 / 4);
    RectButton::insertHeadButton(Buttons, InsertButton);
    RectButton* Value = new TextBox("Value:");
    RectButton* ValueInput = new NumberInputBox(3);
    RectButton* Enter = new TextBox(">");

    InsertButton->insertSubButton(Value);
    InsertButton->insertSubButton(ValueInput);
    InsertButton->insertSubButton(Enter, [this, ValueInput]() {
        int value = ValueInput->getNumber();
        if (value >= 0) {
            insertHashTable(value);
        }
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableInsert);
        });

    RectButton* RemoveButton = new TextBox("Remove");
    RectButton::insertHeadButton(Buttons, RemoveButton);
    RectButton* Value1 = new TextBox("Value:");
    RectButton* ValueInput1 = new NumberInputBox(3);
    RectButton* Enter1 = new TextBox(">");

    RemoveButton->insertSubButton(Value1);
    RemoveButton->insertSubButton(ValueInput1);
    RemoveButton->insertSubButton(Enter1, [this, ValueInput1]() {
        int value = ValueInput1->getNumber();
        if (value >= 0) {
            deleteHashTable(value);
        }
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableRemove);
        });

    RectButton* SearchButton = new TextBox("Search");
    RectButton::insertHeadButton(Buttons, SearchButton);
    RectButton* Value2 = new TextBox("Value:");
    RectButton* ValueInput2 = new NumberInputBox(3);
    RectButton* Enter2 = new TextBox(">");

    SearchButton->insertSubButton(Value2);
    SearchButton->insertSubButton(ValueInput2);
    SearchButton->insertSubButton(Enter2, [this, ValueInput2]() {
        int value = ValueInput2->getNumber();
        bool found = findHashTable(value);
        cout << "Value " << value << " found: " << (found ? "Yes" : "No") << endl;
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableSearch);
        });
}


void HashTableUI::updateButtonPositions() {
    SceneHandler::MenuButton->setPosition(UI::screenWidth / 100, UI::screenHeight / 100);

    RectButton::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 4);

    RectButton::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);
}

void HashTableUI::drawHashTable() {
    for (int i = 0; i < size; ++i) {
        float bucketX = startX + i * (Width + spacing);
        float bucketY = startY;

        Rectangle bucketRec = { bucketX, bucketY, Width, Height };
        DrawRectangleLinesEx(bucketRec, 2.0f, BLACK);
        drawtext2("Bucket " + to_string(i), bucketX + Width / 2, bucketY - 20, DARKGRAY);

        for (int j = 0; j < data[i].size(); ++j) {
            Vector2 nodePos = { bucketX + Width / 2, bucketY + Height + (j + 1) * (nodeRadius * 2 + 10) };
            Node* node = new Node(data[i][j], nodePos, nodeRadius);
            drawNode(node);

            if (j == 0) {
                DrawLine(bucketX + Width / 2, bucketY + Height, nodePos.x, nodePos.y - nodeRadius, BLACK);
            }
            else {
                Vector2 prevNodePos = { bucketX + Width / 2, bucketY + Height + j * (nodeRadius * 2 + 10) };
                DrawLine(prevNodePos.x, prevNodePos.y + nodeRadius, nodePos.x, nodePos.y - nodeRadius, BLACK);
            }

            delete node;
        }
    }
}

void HashTableUI::displaySceneInCamera() {
    drawHashTable();
}

void HashTableUI::displayScene() {
    SceneHandler::MenuButton->draw();
    Button::drawButtons<RectButton>(Buttons);
    Button::drawButtons<RectButton>(CodeBlocks);
}

void HashTableUI::updateScene() {
    Button::isCollision = false;

    SceneHandler::MenuButton->update();
    Button::updateButtons<RectButton>(Buttons);
    Button::updateButtons<RectButton>(CodeBlocks);

    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}
