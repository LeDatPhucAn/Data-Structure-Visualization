#include "../header/TreapUI.h"
#include "../header/PseudoCode.h"
#include "../header/Animation.h"

const Vector2 TreapUI::ROOT_POS = { static_cast<float> (UI::screenWidth) / 2, 0 };

TreapUI::TreapUI() : root(nullptr) {
    init();
}

TreapNode* TreapUI::rotateLeft(TreapNode* root) {
    TreapEdge* oldRightEdge = root->rightEdge;
    if (!oldRightEdge) return root;

    TreapNode* newRoot = oldRightEdge->to;

    TreapEdge* temp = newRoot->leftEdge;
    root->rightEdge = temp ? new TreapEdge(root, temp->to) : nullptr;

    delete oldRightEdge;
    delete temp;

    newRoot->leftEdge = new TreapEdge(newRoot, root);

    return newRoot;
}

TreapNode* TreapUI::rotateLeftWithAnimation(TreapNode* root) {
    TreapEdge* oldRightEdge = root->rightEdge;
    if (!oldRightEdge) return root;

    TreapNode* newRoot = oldRightEdge->to;
    animManager.addAnimation(new TreapNodeMoveAnim(newRoot, 0.4f, newRoot->position, root->position));

    TreapNode* movedLeft = newRoot->leftEdge ? newRoot->leftEdge->to : nullptr;

    delete root->rightEdge;
    root->rightEdge = movedLeft ? new TreapEdge(root, movedLeft) : nullptr;

    delete newRoot->leftEdge;
    newRoot->leftEdge = new TreapEdge(newRoot, root);

    return newRoot;
}

TreapNode* TreapUI::rotateRight(TreapNode* root) {
    TreapEdge* oldLeftEdge = root->leftEdge;
    if (!oldLeftEdge) return root;

    TreapNode* newRoot = oldLeftEdge->to;

    TreapEdge* temp = newRoot->rightEdge;

    root->leftEdge = temp ? new TreapEdge(root, temp->to) : nullptr;

    delete temp;
    delete oldLeftEdge;

    newRoot->rightEdge = new TreapEdge(newRoot, root);

    return newRoot;
}

TreapNode* TreapUI::rotateRightWithAnimation(TreapNode* root) {
    TreapEdge* oldLeftEdge = root->leftEdge;
    if (!oldLeftEdge) return root;

    TreapNode* newRoot = oldLeftEdge->to;
    animManager.addAnimation(new TreapNodeMoveAnim(newRoot, 0.4f, newRoot->position, root->position));

    TreapNode* movedRight = static_cast<TreapNode*>(newRoot->rightEdge ? newRoot->rightEdge->to : nullptr);

    delete root->leftEdge;
    root->leftEdge = movedRight ? new TreapEdge(root, movedRight) : nullptr;

    delete newRoot->rightEdge;
    newRoot->rightEdge = new TreapEdge(newRoot, root);

    return newRoot;
}

int TreapUI::getSubtreeWidth(TreapNode* curr) {
    if (!curr) return 0;
    return curr->subtreeWidth;
}

void TreapUI::updateSubtreeWidth(TreapNode* curr) {
    if (curr) {
        int leftWidth = curr->leftEdge ? getSubtreeWidth(curr->leftEdge->to) : 0;
        int rightWidth = curr->rightEdge ? getSubtreeWidth(curr->rightEdge->to) : 0;
        curr->subtreeWidth = 1 + leftWidth + rightWidth;
    }
}

TreapNode* TreapUI::insert(TreapNode* root, int key, int priority) {
    if (!root) {
        TreapNode* newNode = new TreapNode(key, priority, ROOT_POS);
        return newNode;
    }

    if (root->getKey() > key) {
        TreapNode* newLeftChild = insert(root->leftEdge ? root->leftEdge->to : nullptr, key, priority);
        root->leftEdge = new TreapEdge(root, newLeftChild);
        if (newLeftChild->getPriority() > root->getPriority()) root = rotateRight(root);    
    }
    else if (root->getKey() < key) {
        TreapNode* newRightChild = insert(root->rightEdge ? root->rightEdge->to : nullptr, key, priority);
        root->rightEdge = new TreapEdge(root, newRightChild);
        if (newRightChild->getPriority() > root->getPriority()) root = rotateLeft(root);
    }

    updateSubtreeWidth(root);
    return root;    
}

TreapNode* TreapUI::insertWithAnimation(TreapNode* root, int key, int priority) {
    
}

TreapNode* TreapUI::remove(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (root->getKey() > key) {
        if (root->leftEdge) {
            TreapNode* newLeft = remove(static_cast<TreapNode*> (root->leftEdge->to), key);
            if (root->leftEdge) delete root->leftEdge;
            root->leftEdge = newLeft ? new TreapEdge(root, newLeft) : nullptr;
        }
    }
    else if (root->getKey() < key) {
        if (root->rightEdge) {
            TreapNode* newRight = remove(static_cast<TreapNode*>(root->rightEdge->to), key);
            if (root->rightEdge) delete root->rightEdge;
            root->rightEdge = newRight ? new TreapEdge(root, newRight) : nullptr;
        }
    }
    else {
        if (!root->leftEdge && !root->rightEdge) {
            delete root;
            return nullptr;
        }
        else if (!root->rightEdge) {
            TreapNode* temp = root->leftEdge->to;
            delete root->leftEdge;
            root->leftEdge = nullptr;
            delete root;
            return temp;
        }
        else if (!root->leftEdge) {
            TreapNode* temp = root->rightEdge->to;
            delete root->rightEdge;
            root->rightEdge = nullptr;
            delete root;
            return temp;
        }

        if (root->leftEdge->to->getPriority() > root->rightEdge->to->getPriority()) {
            root = rotateRight(root);
            TreapNode* newRight = remove(root->rightEdge->to, key);
            if (root->rightEdge) delete root->rightEdge;
            root->rightEdge = newRight ? new TreapEdge(root, newRight) : nullptr;
        }
        else {
            root = rotateLeft(root);
            TreapNode* newLeft = remove(root->leftEdge->to, key);
            if (root->leftEdge) delete root->leftEdge;
            root->leftEdge = newLeft ? new TreapEdge(root, newLeft) : nullptr;
        }
    }

    updateSubtreeWidth(root);
    return root;
}

void TreapUI::clear(TreapNode* curr) {
    if (!curr) return;

    if (curr->leftEdge) {
        clear(curr->leftEdge->to);
        delete curr->leftEdge;
        curr->leftEdge = nullptr;
    }
    if (curr->rightEdge) {
        clear(curr->rightEdge->to);
        delete curr->rightEdge;
        curr->rightEdge = nullptr;
    }
    
    delete curr;
}

void TreapUI::insert(int key, int priority, bool isAnimated) {
    cleanupForOperations();
    if (isAnimated) {
        root = insertWithAnimation(root, key, priority);
        animManager.addAnimation(new Animation(0.0f, [this]() {
            reposition(root, ROOT_POS, xOffset, yOffset);
            }));
    }
    else {
        root = insert(root, key, priority);
        reposition(root, ROOT_POS, xOffset, yOffset);
    }
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
    cleanupForOperations();
    searchWithAnimation(root, key);
}

void TreapUI::searchWithAnimation(TreapNode* curr, int key) {
    if (!curr) return;
    
    cout << "Compare with " << curr->getKey() << endl;
    animManager.addAnimation(new RectHighlightAnim(curr->keyBox, 0.75f, ORANGE, DARKGRAY, WHITE));

    if (curr->getKey() == key) {
        animManager.addAnimation(new RectHighlightAnim(curr->keyBox, 0.75f, {82, 172, 16, 255}, DARKGRAY, WHITE));
    }
    else if (curr->getKey() > key) {
        if (curr->leftEdge) {
            animManager.addAnimation(new TreapEdgeHighlightAnim(curr->leftEdge, 0.75f));
            searchWithAnimation(static_cast<TreapNode*> (curr->leftEdge->to), key);
        }
    }
    else {
        if (curr->rightEdge) {
            animManager.addAnimation(new TreapEdgeHighlightAnim(curr->rightEdge, 0.75f));
            searchWithAnimation(static_cast<TreapNode*> (curr->rightEdge->to), key);
        }
    }
}

void TreapUI::remove(int key) {
    root = remove(root, key);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::clear() {
    clear(this->root);
    this->root = nullptr;
}

void TreapUI::cleanupForOperations() {
    animManager.goToLastStep();
    animManager.clear();
    animManager.resume();
}

void TreapUI::reposition(TreapNode* root, Vector2 pos, const int xOffset, const int yOffset) {
    if (!root) return;

    // Position the visual button correctly by setting top-left corner
    float rectX = pos.x - root->keyBox->getWidth() / 2;
    float rectY = pos.y - root->keyBox->getHeight() / 2;
    root->position = { rectX, rectY };
    root->syncPosition();

    int leftWidth = getSubtreeWidth(root->leftEdge ? root->leftEdge->to : nullptr);
    int rightWidth = getSubtreeWidth(root->rightEdge ? root->rightEdge->to : nullptr);
    int newXOffset = max((leftWidth + rightWidth + 1) * 40, 80);
    
    if (root->leftEdge) {
        Vector2 leftPos = { pos.x - newXOffset, pos.y + yOffset };
        reposition(root->leftEdge->to, leftPos, newXOffset, yOffset);
    }

    if (root->rightEdge) {
        Vector2 rightPos = { pos.x + newXOffset, pos.y + yOffset };
        reposition(root->rightEdge->to, rightPos, newXOffset, yOffset);
    }
}

void TreapUI::drawTreapNode(TreapNode* curr) {
    if (!curr) return;
    curr->draw();
}

void TreapUI::drawTreapEdge(TreapEdge* edge) {
    if (!edge || !edge->from || !edge->to) return;
    edge->draw();
}

void TreapUI::drawTreap(TreapNode* curr) {
    if (!curr) return;

    drawTreapNode(curr);

    if (curr->leftEdge) {
        drawTreapEdge(curr->leftEdge);
        drawTreap(curr->leftEdge->to);
    }

    if (curr->rightEdge) {
        drawTreapEdge(curr->rightEdge);
        drawTreap(curr->rightEdge->to);
    }
}

void TreapUI::init() {
    srand(time(nullptr));
    
    int n = rand() % 10;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        this->insert(x, rand(), false);
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
        else this->insert(ValueInput->getNumber(), rand());
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
            this->insert(x, rand(), false);
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
    animManager.update(GetFrameTime());

    Button::updateButtons<RectButton>(Buttons);
    Button::updateButtons<RectButton>(CodeBlocks);

    // Update treap node buttons recursively
    std::function<void(TreapNode*)> updateTreapNodes = [&](TreapNode* node) {
        if (!node) return;
        node->update();
        if (node->leftEdge) updateTreapNodes(node->leftEdge->to);
        if (node->rightEdge) updateTreapNodes(node->rightEdge->to);
        };
    updateTreapNodes(root);

    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}