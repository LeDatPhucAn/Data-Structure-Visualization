#include "../header/TreapUI.h"
#include "../header/PseudoCode.h"

const Vector2 TreapUI::ROOT_POS = { static_cast<float> (UI::screenWidth) / 2, 0 };

TreapUI::TreapUI() : root(nullptr) {
    init();
}

void TreapUI::insert(int key, int priority) {
    root = treap.insert(root, ROOT_POS, key, priority);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::loadFromFile(){
    const char* filter[] = {"*.txt"};
    const char* filePath = tinyfd_openFileDialog(
        "Select a text file", // Title
        "", // Default path (empty = open from last used folder)
        1, // Number of filter patterns
        filter, // Filter patterns
        "Text file (*.txt)", // Filter description
        0 // Single file selection mode
    );

    if(filePath){
        cout << "Trying to open the file: " << filePath << endl;
        ifstream fin(filePath);
        if(fin.is_open()){
            clear();
            string line;
            while(getline(fin, line)){
                istringstream iss(line);
                int key = 0, priority = 0;
                if(iss >> key){
                    if(iss >> priority) insert(key, priority);
                    else insert(key);
                }
            }
        }
        else cerr << "Error: Can not open file\n";
    }
}

void TreapUI::search(int key) {
    TreapNode* curr = treap.getRoot();
    if (!curr) return;

}

void TreapUI::remove(int key) {
    root = treap.remove(root, key);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::clear() {
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
    DrawRectangle(pos.x - width / 2 + dataWidth, pos.y - height / 2, priorityWidth, height, { 69, 180, 238, 145 });

    DrawRectangleLines(pos.x - width / 2, pos.y - height / 2, width, height, BLACK);
    DrawLine(pos.x - width / 2 + dataWidth, pos.y - height / 2, pos.x - width / 2 + dataWidth, pos.y + height / 2, BLACK);

    string value = to_string(curr->data).substr(0, 5);
    Vector2 valueTextSize = MeasureTextEx(GetFontDefault(), value.c_str(), 30.0f, 2.0f);
    string priority = to_string(curr->priority);
    Vector2 priorityTextSize = MeasureTextEx(GetFontDefault(), priority.c_str(), 20.0f, 2.0f);

    DrawText(value.c_str(), pos.x - width / 2 + dataWidth / 2 - valueTextSize.x / 2, pos.y - valueTextSize.y / 2, 30, DARKGRAY);
    DrawText(priority.c_str(), pos.x - width / 2 + dataWidth + priorityWidth / 2 - priorityTextSize.x / 2, pos.y - priorityTextSize.y / 2, 20, MAROON);
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

    /// Code Blocks
    RectButton* OpenCodeBlocks = new TextBox("<");
    OpenCodeBlocks->rect.x = UI::screenWidth - OpenCodeBlocks->rect.width;
    OpenCodeBlocks->rect.y = UI::screenHeight / 4;
    OpenCodeBlocks->rect.height = 0;
    OpenCodeBlocks->isActivated = true;
    RectButton::insertCodeBlock(CodeBlocks, OpenCodeBlocks);

    /// Buttons
    RectButton::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 5));
    RectButton* Value = new TextBox("Value:");
    RectButton* ValueInput = new NumberInputBox(3);
    RectButton* Priority = new TextBox("Priority:");
    RectButton* PriorityInput = new NumberInputBox(3);
    RectButton* Enter = new TextBox(">");

    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Priority);
    Buttons[0]->insertSubButton(PriorityInput);

    Buttons[0]->insertSubButton(Enter, [this, ValueInput, PriorityInput]() {
        if (PriorityInput->getNumber() > 0) this->insert(ValueInput->getNumber(), PriorityInput->getNumber());
        else this->insert(ValueInput->getNumber());
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::TreapInsert);
        static_cast<NumberInputBox*>(ValueInput)->clear();
        static_cast<NumberInputBox*>(PriorityInput)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Remove"));
    RectButton* Value1 = new TextBox("Value:");
    RectButton* ValueInput1 = new NumberInputBox(3);
    RectButton* Enter1 = new TextBox(">");

    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        this->remove(ValueInput1->getNumber());
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::TreapRemove);
        static_cast<NumberInputBox*>(ValueInput1)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Search"));
    RectButton* Value2 = new TextBox("Value:");
    RectButton* ValueInput2 = new NumberInputBox(3);
    RectButton* Enter2 = new TextBox(">");

    Buttons[2]->insertSubButton(Value2);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(Enter2, [this, ValueInput2]() {
        this->search(ValueInput2->getNumber());
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::TreapSearch);
        static_cast<NumberInputBox*>(ValueInput2)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("LoadFile"));
    Buttons[3]->onClick = [this]() {
        this->loadFromFile();
        };

    RectButton::insertHeadButton(Buttons, new TextBox("Random"));
    Buttons[4]->onClick = [this]() {
        this->clear();
        int n = rand() % 10;
        for (int i = 0; i < n; ++i) {
            int x = rand() % 100;
            this->insert(x);
        }
        };

    RectButton::insertHeadButton(Buttons, new TextBox(" Clear ",0,0, WHITE, { 214, 102, 49, 255 }, DARKGRAY));
    Buttons[5]->onClick = [this]() {
        this->clear();
        };

    updateButtonPositions();
}


void TreapUI::displayScene() {
    Button::drawButtons<RectButton>(Buttons);
    Button::drawButtons<RectButton>(CodeBlocks);
}

void TreapUI::updateButtonPositions() {
    RectButton::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 5);

    RectButton::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);
}

void TreapUI::updateScene() {
    Button::updateButtons<RectButton>(Buttons);
    Button::updateButtons<RectButton>(CodeBlocks);

    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void TreapUI::addAnimationStep(int priority, function<void()> func) {
    animationQueue.push({ priority, func });
}

void TreapUI::processAnimations() {
    while (!animationQueue.empty()) {
        auto task = animationQueue.top();
        animationQueue.pop();
        task.task();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void TreapUI::drawHighlightedNode(TreapNode* node) {
    if (!node) return;

    static const float width = 140.0f; 
    static const float height = 120.0f; 
    static const float dataWidth = 100.0f;
    static const float priorityWidth = 40.0f;

    Vector2 pos = node->position;

    // Draw highlighted rectangle
    DrawRectangle(pos.x - width / 2, pos.y - height / 2, width, height, { 255, 203, 203, 255 });
    DrawRectangle(pos.x - width / 2 + dataWidth, pos.y - height / 2, priorityWidth, height, { 69, 180, 238, 145 });

    // Draw the outline of the rectangle
    DrawRectangleLines(pos.x - width / 2, pos.y - height / 2, width, height, RED);
    DrawLine(pos.x - width / 2 + dataWidth, pos.y - height / 2, pos.x - width / 2 + dataWidth, pos.y + height / 2, BLACK);

    string value = to_string(node->data).substr(0, 5);
    Vector2 valueTextSize = MeasureTextEx(GetFontDefault(), value.c_str(), 30.0f, 2.0f);
    string priority = to_string(node->priority);
    Vector2 priorityTextSize = MeasureTextEx(GetFontDefault(), priority.c_str(), 20.0f, 2.0f);

    DrawText(value.c_str(), pos.x - width / 2 + dataWidth / 2 - valueTextSize.x / 2, pos.y - valueTextSize.y / 2, 30, DARKGRAY);
    DrawText(priority.c_str(), pos.x - width / 2 + dataWidth + priorityWidth / 2 - priorityTextSize.x / 2, pos.y - priorityTextSize.y / 2, 20, MAROON);
}

void TreapUI::drawHighlightedEdge(Edge* edge) {
    if (!edge || !edge->from || !edge->to) return;

    // Draw the highlighted edge with a thicker line
    Vector2 fromPos = edge->from->position;
    Vector2 toPos = edge->to->position;
    DrawLineEx(fromPos, toPos, 5.0f, RED);
}