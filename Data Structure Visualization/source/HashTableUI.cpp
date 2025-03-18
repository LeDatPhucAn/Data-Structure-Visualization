
#include "../header/UI.h"
#include "../header/HashTableUI.h"
#include "../header/SceneHandler.h"
#include "../header/Button.h"

void HashTableUI::init() {
    insertHashTable(10); // example
    insertHashTable(15);
    insertHashTable(7);
    insertHashTable(12);
    
    initButtons();
}
void HashTableUI::initButtons() {
    Button::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 4));
    Button* Value = new TextBox("Value:");
    Button* ValueInput = new NumberInputBox(3);
    Button* Enter = new TextBox(">");

    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Enter, [this, ValueInput]() {
        int value = ValueInput->getNumber();
        if (value >= 0) {
            insertHashTable(value);
        }
        });

    Button::insertHeadButton(Buttons, new TextBox("Remove"));
    Button* Value1 = new TextBox("Value:");
    Button* ValueInput1 = new NumberInputBox(3);
    Button* Enter1 = new TextBox(">");
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        int value = ValueInput1->getNumber();
        if (value >= 0) {
            deleteHashTable(value);
        }
        });

    Button::insertHeadButton(Buttons, new TextBox("Search"));
    Button* Value2 = new TextBox("Value:");
    Button* ValueInput2 = new NumberInputBox(3);
    Button* Enter2 = new TextBox(">");
    Buttons[2]->insertSubButton(Value2);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(Enter2, [this, ValueInput2]() {
        int value = ValueInput2->getNumber();
        bool found = findHashTable(value);
        cout << "Value " << value << " found: " << (found ? "Yes" : "No") << endl;
        });

}

void HashTableUI::updateButtonPositions() {

    SceneHandler::MenuButton->setPosition(UI::screenWidth / 100, UI::screenHeight / 100);

    Button::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 4);

    Button::setHeadPosition(CodeBlocks, UI::screenWidth * 5 / 8, UI::screenHeight * 3 / 4);

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
    Button::drawButtons(Buttons);
    Button::drawButtons(CodeBlocks);
}
void HashTableUI::updateScene() {

    if (UI::lastScreenWidth != UI::screenWidth || UI::lastScreenHeight != UI::screenHeight) {

        updateButtonPositions();

        UI::lastScreenWidth = UI::screenWidth;
        UI::lastScreenHeight = UI::screenHeight;
    }

    Button::isCollision = false;


    SceneHandler::MenuButton->update();
    Button::updateButtons(Buttons);
    Button::updateButtons(CodeBlocks);


    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

