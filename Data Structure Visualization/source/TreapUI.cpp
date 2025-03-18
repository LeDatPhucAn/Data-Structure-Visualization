#include "../header/TreapUI.h"

const Vector2 TreapUI::ROOT_POS = { static_cast<float> (UI::screenWidth) / 2, 0 };

TreapUI::TreapUI() : root(nullptr) {
    init();
}
void TreapUI::deleteButtons() {
    for (auto button : Buttons) {
        while (button) {
            Button* del = button;
            button = button->next;
            delete del;
        }
    }
}

void TreapUI::insert(int key, int priority) {
    root = treap.insert(root, ROOT_POS, key, priority);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::search(int key) {
    root = treap.search(root, key);
}

void TreapUI::remove(int key) {
    root = treap.remove(root, key);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::clear(){
    treap.Treap::clear();
    this->root = nullptr;
}


void TreapUI::reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset) {
    if (!root) return;

    root->position = pos;

    int leftWidth = treap.getSubtreeWidth(root->leftEdge ? static_cast<TreapNode*> (root->leftEdge->to) : nullptr);
    int rightWidth = treap.getSubtreeWidth(root->rightEdge ? static_cast<TreapNode*> (root->rightEdge->to) : nullptr);

    int newXOffset = max((leftWidth + rightWidth + 1) * 60, 120);

    if (root->leftEdge) {
        Vector2 leftPos = { pos.x - newXOffset, pos.y + yOffset };
        reposition(static_cast<TreapNode*> (root->leftEdge->to), leftPos, newXOffset, yOffset);
    }

    if (root->rightEdge) {
        Vector2 rightPos = { pos.x + newXOffset, pos.y + yOffset };
        reposition(static_cast<TreapNode*> (root->rightEdge->to), rightPos, newXOffset, yOffset);
    }
}


void TreapUI::drawTreapNode(TreapNode* curr) {
    if (!curr) return;

    static const float width = 120.0f;
    static const float height = 100.0f;
    static const float dataWidth = 80.0f;
    static const float priorityWidth = 40.0f;

    Vector2 pos = curr->position;

    DrawRectangle(pos.x - width / 2, pos.y - height / 2, width, height, { 255, 203, 203, 255 });
    DrawRectangle(pos.x - width / 2 + dataWidth, pos.y - height / 2, priorityWidth, height, { 69, 180, 238, 255 });

    DrawRectangleLines(pos.x - width / 2, pos.y - height / 2, width, height, BLACK);
    DrawLine(pos.x - width / 2 + dataWidth, pos.y - height / 2, pos.x - width / 2 + dataWidth, pos.y + height / 2, BLACK);

    string value = to_string(curr->data).substr(0, 5);
    Vector2 valueTextSize = MeasureTextEx(GetFontDefault(), value.c_str(), 30.0f, 2.0f);
    string priority = to_string(curr->priority);
    Vector2 priorityTextSize = MeasureTextEx(GetFontDefault(), priority.c_str(), 20.0f, 2.0f);

    DrawText(value.c_str(), pos.x - width / 2 + dataWidth / 2 - valueTextSize.x / 2, pos.y - valueTextSize.y / 2, 30, DARKGRAY);
    DrawText(priority.c_str(), pos.x - width / 2 + dataWidth + priorityWidth / 2 - priorityTextSize.x / 2, pos.y - priorityTextSize.y / 2, 20, DARKPURPLE);
}

void TreapUI::drawTreapLink(Edge* edge) {
    if (!edge || !edge->from || !edge->to) return;
    edge->drawTreapEdge();
}

void TreapUI::drawTreap(TreapNode* curr) {
    if (!curr) return;
  
    drawTreapNode(curr);

    if (curr->leftEdge) {
        drawTreapLink(curr->leftEdge);
        drawTreap(static_cast<TreapNode*>(curr->leftEdge->to));
    }

    if (curr->rightEdge) {
        drawTreapLink(curr->rightEdge);
        drawTreap(static_cast<TreapNode*>(curr->rightEdge->to));
    }
}

void TreapUI::init() {
    srand(time(nullptr));
    int n = rand() % 10;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        insert(x);
    }
    initButtons();
}

void TreapUI::initButtons() {
    Button::insertHeadButton(Buttons, new TextBox(" Insert", 100, UI::screenHeight * 3 / 4));
    Button* Value = new TextBox("Value:");
    Button* ValueInput = new NumberInputBox(3);
    Button* Priority = new TextBox("Priority:");
    Button* PriorityInput = new NumberInputBox(3);
    Button* Enter = new TextBox(">");

    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Priority);
    Buttons[0]->insertSubButton(PriorityInput);

    Buttons[0]->insertSubButton(Enter, [this, ValueInput, PriorityInput]() {
        if (PriorityInput->getNumber() > 0) this->insert(ValueInput->getNumber(), PriorityInput->getNumber());
        else this->insert(ValueInput->getNumber());
        static_cast<NumberInputBox*>(ValueInput)->clear();
        static_cast<NumberInputBox*>(PriorityInput)->clear();
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

    Button::insertHeadButton(Buttons, new TextBox(" Clear ", WHITE, { 214, 102, 49, 255 }, DARKGRAY));
    Buttons[3]->onClick = [this]() {
        this->clear();
        };

}

void TreapUI::displayScene() {
    SceneHandler::MenuButton->draw();
    Button::drawButtons(Buttons);
    Button::drawButtons(CodeBlocks);
}
void TreapUI::updateButtonPositions() {

    SceneHandler::MenuButton->setPosition(UI::screenWidth / 100, UI::screenHeight / 100);

    Button::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 4);

    Button::setHeadPosition(CodeBlocks, UI::screenWidth * 5 / 8, UI::screenHeight * 3 / 4);

}
void TreapUI::updateScene() {

    Button::isCollision = false;


    SceneHandler::MenuButton->update();
    Button::updateButtons(Buttons);
    Button::updateButtons(CodeBlocks);


    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}