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

    updateSubtreeWidth(root);
    updateSubtreeWidth(newRoot);
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

    updateSubtreeWidth(root);
    updateSubtreeWidth(newRoot);
    return newRoot;
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

TreapNode* TreapUI::search(TreapNode* root, int key) {
    if (!root) return nullptr;
    if (root->getKey() == key) return root;
    else if (root->getKey() > key) {
        return search(root->leftEdge ? root->leftEdge->to : nullptr, key);
    }
    return search(root->rightEdge ? root->rightEdge->to : nullptr, key);
}

TreapNode* TreapUI::searchForNode(int key) {
    return search(this->root, key);
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

TreapNode* TreapUI::rotateLeftAtSpecificNode(TreapNode* curr, int key) {
    if (!curr) return nullptr;

    if (curr->getKey() == key) {
        cerr << "rotate left here" << endl;
        return rotateLeft(curr);
    }
    else if (curr->getKey() > key) {
        cerr << "go left" << endl;
        curr->leftEdge = new TreapEdge(curr, rotateLeftAtSpecificNode(curr->leftEdge ? curr->leftEdge->to : nullptr, key));
        cerr << "return from left" << endl;
    }
    else {
        cerr << "go right" << endl;
        curr->rightEdge = new TreapEdge(curr, rotateLeftAtSpecificNode(curr->rightEdge ? curr->rightEdge->to : nullptr, key));
        cerr << "return from right" << endl;
    }

    updateSubtreeWidth(curr);
    return curr;
}

TreapNode* TreapUI::rotateRightAtSpecificNode(TreapNode* curr, int key) {
    if (!curr) return nullptr;

    if (curr->getKey() == key) {
        cerr << "rotate right here" << endl;
        return rotateRight(curr);
    }
    else if (curr->getKey() > key) {
        cerr << "go left" << endl;
        TreapEdge* del = curr->leftEdge;
        curr->leftEdge = new TreapEdge(curr, rotateRightAtSpecificNode(curr->leftEdge ? curr->leftEdge->to : nullptr, key));
        delete del;
        cerr << "return from left" << endl;
    }
    else {
        cerr << "go right" << endl;
        TreapEdge* del = curr->rightEdge;
        curr->rightEdge = new TreapEdge(curr, rotateRightAtSpecificNode(curr->rightEdge ? curr->rightEdge->to : nullptr, key));
        delete del;
        cerr << "return from right" << endl;
    }

    updateSubtreeWidth(curr);
    return curr;
}

TreapNode* TreapUI::insertBST(TreapNode* root, int key, int priority) {
    if (!root) return new TreapNode(key, priority, ROOT_POS);

    if (root->getKey() == key) return root;
    else if (root->getKey() > key) {
        TreapEdge* del = root->leftEdge;
        root->leftEdge = new TreapEdge(root, insertBST(root->leftEdge ? root->leftEdge->to : nullptr, key, priority));
        delete del;
    }
    else {
        TreapEdge* del = root->rightEdge;
        root->rightEdge = new TreapEdge(root, insertBST(root->rightEdge ? root->rightEdge->to : nullptr, key, priority));
        delete del;
    }

    updateSubtreeWidth(root);
    return root;
}

void TreapUI::makeNewNodeAppear(TreapNode* curr, int key, stack<int>& visited) {
    if (!curr) return;

    if (curr->getKey() == key) {
        TreapNode* target = curr;
        target->keyBox->noDraw = true;
        target->priorityBox->noDraw = true;
        animManager.addAnimation(new TreapNodeInitializeAnim(target, 0.75f, [target]() {
            target->keyBox->noDraw = false;
            target->priorityBox->noDraw = false;
            }));
        animManager.addAnimation(new RectHighlightAnim(curr->keyBox, 0.75f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
        curr->noDraw = false;
        return;
    }

    visited.push(curr->getKey());
    //cerr << "add " << curr->getKey() << endl;
    animManager.addAnimation(new RectHighlightAnim(curr->keyBox, 0.75f, ORANGE, DARKGRAY, WHITE));

    if (curr->getKey() > key) {
        if (curr->leftEdge && curr->leftEdge->to) {
            TreapEdge* edge = curr->leftEdge;
            if (edge->to->getKey() == key) edge->noDraw = true;
            animManager.addAnimation(new TreapEdgeHighlightAnim(curr->leftEdge, 0.75f, ORANGE, [edge]() {edge->noDraw = false; }));
            makeNewNodeAppear(curr->leftEdge->to, key, visited);
        }
    }
    else if (curr->getKey() < key) {
        if (curr->rightEdge && curr->rightEdge->to) {
            TreapEdge* edge = curr->rightEdge;
            if (edge->to->getKey() == key) edge->noDraw = true;
            animManager.addAnimation(new TreapEdgeHighlightAnim(curr->rightEdge, 0.75f, ORANGE, [edge]() {edge->noDraw = false; }));
            makeNewNodeAppear (curr->rightEdge->to, key, visited);
        }
    }
}

void TreapUI::fixViolation(stack<int>& visited) {
    if (visited.empty()) return;
    int key = visited.top(); // Get the key of the current node
    visited.pop();

    TreapNode* v = searchForNode(key); // Revalidate the node in the updated tree
    if (!v) {
        cerr << "Node with key " << key << " no longer exists in the tree." << endl;
        animManager.addAnimation(new Animation(0.1f, [this, visited]() mutable {
            fixViolation(visited);
            }));
        return;
    }

    cerr << "Handling node with key " << v->getKey() << endl;
    bool hasRotated = false;
    animManager.addAnimation(new RectHighlightAnim(v->priorityBox, 0.75f, { 208, 82, 82, 255 }, DARKGRAY, WHITE));

    if (v->leftEdge && v->leftEdge->to) {
        cerr << "current priority " << v->getPriority() << " checking with priority " << v->leftEdge->to->getPriority() << endl;
        if (v->leftEdge->to->getPriority() > v->getPriority()) {
            //v->leftEdge->noDraw = true;
            cerr << "left node has higher priority" << endl;
            treap.rotateRightAtSpecificNode(v->getKey());
            treap.reposition(treap.root, ROOT_POS, xOffset, yOffset);

            unordered_map<int, Vector2> positions = treap.getAllPositions();

            vector<TreapNode*> move;
            getNodesToMove(move, v);

            animManager.addAnimation(new Animation(0.1f, [this, key]() {
                this->root = rotateRightAtSpecificNode(this->root, key);
                }));
            animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));
            //this->root = rotateRightAtSpecificNode(this->root, key);

            hasRotated = true;
        }
    }

    if (!hasRotated && v->rightEdge && v->rightEdge->to) {
        cerr << "current priority " << v->getPriority() << " checking with priority " << v->rightEdge->to->getPriority() << endl;
        if (v->rightEdge->to->getPriority() > v->getPriority()) {
            //v->rightEdge->noDraw = true;
            cerr << "right node has higher priority" << endl;
            treap.rotateLeftAtSpecificNode(v->getKey());
            treap.reposition(treap.root, ROOT_POS, xOffset, yOffset);

            unordered_map<int, Vector2> positions = treap.getAllPositions();

            vector<TreapNode*> move;
            getNodesToMove(move, v);

            animManager.addAnimation(new Animation(0.1f, [this, key]() {
                this->root = rotateLeftAtSpecificNode(this->root, key);
                }));

            animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));
        }
    }

    animManager.addAnimation(new Animation(1.0f, [this, visited]() mutable {
        fixViolation(visited);
        reposition(this->root, ROOT_POS, xOffset, yOffset);
        }));
}

void TreapUI::getNodesToMove(vector<TreapNode*>& res, TreapNode* curr) {
    if (!curr) return;
    res.push_back(curr);
    getNodesToMove(res, curr->leftEdge ? curr->leftEdge->to : nullptr);
    getNodesToMove(res, curr->rightEdge ? curr->rightEdge->to : nullptr);
}

void TreapUI::insertWithAnimation(int key, int priority) {
    if (treap.search(key)) {
        searchWithAnimation(this->root, key);
        return;
    }

    this->root = insertBST(this->root, key, priority);
    treap.insertBST(key, priority);

    reposition(this->root, ROOT_POS, xOffset, yOffset);

    auto visited = std::make_shared<std::stack<int>>();
    makeNewNodeAppear(this->root, key, *visited);

    cerr << "After step 2, size of stack: " << visited->size() << endl;

    animManager.addAnimation(new Animation(1.0f, [this, temp = *visited]() mutable {
        fixViolation(temp);
        reposition(this->root, ROOT_POS, xOffset, yOffset);
        }));
}

void TreapUI::searchWithAnimation(TreapNode* curr, int key) {
    if (!curr) return;

    cout << "Compare with " << curr->getKey() << endl;
    animManager.addAnimation(new RectHighlightAnim(curr->keyBox, 0.75f, ORANGE, DARKGRAY, WHITE));

    if (curr->getKey() == key) {
        animManager.addAnimation(new RectHighlightAnim(curr->keyBox, 0.75f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
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

void TreapUI::cleanupForOperations() {
    animManager.goToLastStep();
    animManager.clear();
    animManager.resume();
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

void TreapUI::insert(int key, int priority, bool isAnimated) {
    cleanupForOperations();
    if (isAnimated) {
        clear();
        this->root = cloneTree(treap.root);
        //reposition(this->root, ROOT_POS, xOffset, yOffset);
        insertWithAnimation(key, priority);
        /*animManager.addAnimation(new Animation(0.5f, [this]() {
            reposition(root, ROOT_POS, xOffset, yOffset);
            }));*/
    }
    else {
        treap.insert(key, priority);
        root = insert(root, key, priority);
        reposition(root, ROOT_POS, xOffset, yOffset);
    }
}

void TreapUI::search(int key) {
    cleanupForOperations();
    clear();
    this->root = cloneTree(treap.root);
    reposition(this->root, ROOT_POS, xOffset, yOffset);
    searchWithAnimation(root, key);
}

void TreapUI::remove(int key) {
    cleanupForOperations();
    root = remove(root, key);
    treap.remove(key);
    reposition(root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::clear() {
    clear(this->root);
    this->root = nullptr;
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
        if (ValueInput1->getNumber() < 0) return;
        cout << "trying to remove" << ValueInput1->getNumber() << endl;
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

    /*RectButton::insertHeadButton(Buttons, new TextBox("LoadFile"));
    Buttons[3]->onClick = [this]() {
        this->loadFromFile();
        };*/

    RectButton::insertHeadButton(Buttons, new TextBox("DrawInside"));
    Buttons[3]->onClick = [this]() {
        this->drawInsideTreap = !(this->drawInsideTreap);
        };

    RectButton::insertHeadButton(Buttons, new TextBox("Random"));
    Buttons[4]->onClick = [this]() {
        treap.clear();
        cleanupForOperations();
        clear();
        int n = rand() % 10;
        for (int i = 0; i < n; ++i) {
            int x = rand() % 100;
            this->insert(x, rand(), false);
        }
        };

    RectButton::insertHeadButton(Buttons, new TextBox(" Clear ",0,0, WHITE, { 214, 102, 49, 255 }, DARKGRAY));
    Buttons[5]->onClick = [this]() {
        treap.clear();
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