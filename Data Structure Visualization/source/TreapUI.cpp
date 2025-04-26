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

TreapNode* TreapUI::removeSpecificNode(TreapNode* curr, int key) {
    if (!curr) return nullptr;
    if (curr->getKey() > key) {
        TreapEdge* del = curr->leftEdge;
        curr->leftEdge = new TreapEdge(curr, removeSpecificNode(curr->leftEdge ? curr->leftEdge->to : nullptr, key));
        delete del;
    }
    else if (curr->getKey() < key) {
        TreapEdge* del = curr->rightEdge;
        curr->rightEdge = new TreapEdge(curr, removeSpecificNode(curr->rightEdge ? curr->rightEdge->to : nullptr, key));
        delete del;
    }
    else {
        if ((!curr->leftEdge || !curr->leftEdge->to) && (!curr->rightEdge || !curr->rightEdge->to)) {
            delete curr;
            return nullptr;
        }
        else if (!curr->leftEdge || !curr->leftEdge->to) {
            TreapNode* r = curr->rightEdge->to;
            delete curr->rightEdge;
            delete curr;
            return r;
        }
        else if (!curr->rightEdge || !curr->rightEdge->to) {
            TreapNode* r = curr->leftEdge->to;
            delete curr->leftEdge;
            delete curr;
            return r;
        }
    }
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

void TreapUI::sbs_insertBST(TreapNode* root, int key, int priority) {
    if (!root) {
        treap.insertBST(key, priority);
        steps.push_back(new TreapStep(cloneTree(treap.root), CodeBlocks, { { key, { 'k', {{ 82, 172, 16, 255 }, DARKGRAY, WHITE} } } }, {}, { 1, 2 }));
        return;
    }

    cerr << "handle node with key " << root->getKey() << endl;
    /*TreapStep* s =  new TreapStep(cloneTree(treap.root), { {root->getKey(), {'k', {ORANGE, DARKGRAY, WHITE}}} }, {});
    cerr << s.root->getKey() << endl;
    cerr << s.highlightedNodes.size() << endl;
    cerr << s.highlightedEdges.size() << endl;*/
    steps.push_back(new TreapStep(cloneTree(treap.root), {}, { { root->getKey(), { 'k', {ORANGE, DARKGRAY, WHITE} } } }));
    cerr << "reach here" << endl;
    cerr << "handle node with key " << root->getKey() << endl;

    if (root->getKey() == key) {
        steps.push_back(new TreapStep(cloneTree(treap.root), CodeBlocks, { { key, { 'k', {{ 82, 172, 16, 255 }, DARKGRAY, WHITE} } } }, {}, { 3, 4 }));
    }
    else if (root->getKey() > key) {
        cerr << "goleft" << endl;
        if (root->leftEdge && root->leftEdge->to) {
            steps.push_back(new TreapStep(cloneTree(treap.root), CodeBlocks, {}, { {root->getKey(), root->leftEdge->to->getKey()} }));
        }
        sbs_insertBST(root->leftEdge ? root->leftEdge->to : nullptr, key, priority);
    }
    else {
        cerr << "go right" << endl;
        if (root->rightEdge && root->rightEdge->to) {
            steps.push_back(new TreapStep(cloneTree(treap.root), CodeBlocks, {}, { {root->getKey(), root->rightEdge->to->getKey()} }));
        }
        sbs_insertBST(root->rightEdge ? root->rightEdge->to : nullptr, key, priority);
    }
}

void TreapUI::makeNewNodeAppear(TreapNode* curr, int key, stack<int>& visited) {
    if (!curr) return;

    if (curr->getKey() == key) {
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[1]->highlight();
            }));
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[2]->highlight();
            }));
        TreapNode* target = curr;
        target->keyBox->noDraw = true;
        target->priorityBox->noDraw = true;
        animManager.addAnimation(new TreapNodeInitializeAnim(target, 0.75f, [target]() {
            target->keyBox->noDraw = false;
            target->priorityBox->noDraw = false;
            }));
        animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 4.0f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
        curr->noDraw = false;
        return;
    }

    visited.push(curr->getKey());
    //animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 1.75f, ORANGE, DARKGRAY, WHITE));

    if (curr->getKey() > key) {
        animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 1.75f, ORANGE, DARKGRAY, WHITE, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[5]->highlight();
            }));
        if (curr->leftEdge && curr->leftEdge->to) {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[6]->highlight();
                }));
            TreapEdge* edge = curr->leftEdge;
            if (edge->to->getKey() == key) edge->noDraw = true;
            animManager.addAnimation(new TreapEdgeHighlight2Anim(curr->leftEdge, 1.75f, ORANGE, [edge]() {edge->noDraw = false; }));
            makeNewNodeAppear(curr->leftEdge->to, key, visited);
        }
    }
    else if (curr->getKey() < key) {
        animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 1.75f, ORANGE, DARKGRAY, WHITE, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[9]->highlight();
            }));
        if (curr->rightEdge && curr->rightEdge->to) {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[10]->highlight();
                }));
            TreapEdge* edge = curr->rightEdge;
            if (edge->to->getKey() == key) edge->noDraw = true;
            animManager.addAnimation(new TreapEdgeHighlight2Anim(curr->rightEdge, 1.75f, ORANGE, [edge]() {edge->noDraw = false; }));
            makeNewNodeAppear (curr->rightEdge->to, key, visited);
        }
    }
}

void TreapUI::fixViolation(stack<int>& visited) {
    if (visited.empty()) return;
    int key = visited.top();
    visited.pop();

    TreapNode* v = searchForNode(key);
    if (!v) {
        cerr << "Node with key " << key << " no longer exists in the tree." << endl;
        animManager.addAnimation(new Animation(0.1f, [this, visited]() mutable {
            fixViolation(visited);
            }));
        return;
    }

    cerr << "Handling node with key " << v->getKey() << endl;
    bool hasRotated = false;
    animManager.addAnimation(new RectHighlight2Anim(v->priorityBox, 1.75f, ORANGE, DARKGRAY, WHITE));

    if (v->leftEdge && v->leftEdge->to) {
        if (v->leftEdge->to->getPriority() > v->getPriority()) {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[7]->highlight();
                }));
            animManager.addAnimation(new RectHighlight2Anim(v->leftEdge->to->priorityBox, 1.75f, { 208, 82, 82, 255 }, DARKGRAY, WHITE));
            cerr << "left node has higher priority" << endl;
            treap.rotateRightAtSpecificNode(v->getKey());

            unordered_map<int, Vector2> positions = treap.getAllPositions();

            vector<TreapNode*> move;
            getNodesToMove(move, v);

            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[8]->highlight();
                }));

            animManager.addAnimation(new Animation(0.1f, [this, key]() {
                this->root = rotateRightAtSpecificNode(this->root, key);
                }));

            animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));

            hasRotated = true;
        }
    }

    if (!hasRotated && v->rightEdge && v->rightEdge->to) {
        if (v->rightEdge->to->getPriority() > v->getPriority()) {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[11]->highlight();
                }));
            animManager.addAnimation(new RectHighlight2Anim(v->rightEdge->to->priorityBox, 1.75f, { 208, 82, 82, 255 }, DARKGRAY, WHITE));
            cerr << "right node has higher priority" << endl;
            treap.rotateLeftAtSpecificNode(v->getKey());

            unordered_map<int, Vector2> positions = treap.getAllPositions();

            vector<TreapNode*> move;
            getNodesToMove(move, v);

            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[12]->highlight();
                }));

            animManager.addAnimation(new Animation(0.1f, [this, key]() {
                this->root = rotateLeftAtSpecificNode(this->root, key);
                }));

            animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));
        }
    }

    animManager.addAnimation(new Animation(1.0f, [this, visited]() mutable {
        fixViolation(visited);
        }));
    reposition(this->root, ROOT_POS, xOffset, yOffset);
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

    treap.insertBST(key, priority);
    this->root = insertBST(this->root, key, priority);
    reposition(this->root, ROOT_POS, xOffset, yOffset);

    auto visited = std::make_shared<std::stack<int>>();
    makeNewNodeAppear(this->root, key, *visited);

    cerr << "After step 2, size of stack: " << visited->size() << endl;

    animManager.addAnimation(new Animation(1.0f, [this, temp = *visited]() mutable {
        fixViolation(temp);
        }));

    reposition(this->root, ROOT_POS, xOffset, yOffset);
}

void TreapUI::searchWithAnimation(TreapNode* curr, int key) {
    if (!curr) {
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[1]->highlight();
            }));
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[2]->highlight();
            }));
        return;
    }

    if (curr->getKey() == key) {
        animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 1.75f, ORANGE, DARKGRAY, WHITE));
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[3]->highlight();
            }));
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[4]->highlight();
            }));
        animManager.addAnimation(new RectHighlightAnim(curr->keyBox, 1.75f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
    }
    else if (curr->getKey() > key) {
        animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 1.75f, ORANGE, DARKGRAY, WHITE, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[5]->highlight();
            }));
        if (curr->leftEdge) {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[6]->highlight();
                }));
            animManager.addAnimation(new TreapEdgeHighlight2Anim(curr->leftEdge, 1.75f));          
            searchWithAnimation(curr->leftEdge->to, key);
        }
        else {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[5]->highlight();
                }));
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[6]->highlight();
                }));
            searchWithAnimation(nullptr, key);
        }
    }
    else {       
        animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 1.75f, ORANGE, DARKGRAY, WHITE, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[7]->highlight();
            }));
        if (curr->rightEdge) {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[8]->highlight();
                }));
            animManager.addAnimation(new TreapEdgeHighlight2Anim(curr->rightEdge, 1.75f));
            searchWithAnimation(curr->rightEdge->to, key);
        }
        else {
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[7]->highlight();
                }));
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[8]->highlight();
                }));
            searchWithAnimation(nullptr, key);
        }
    }
}

bool TreapUI::searchBeforeRemove(TreapNode* curr, int key) {
    if (!curr) {
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[1]->highlight();
            }));
        return false;
    }
    
    animManager.addAnimation(new RectHighlight2Anim(curr->keyBox, 1.75f, ORANGE, DARKGRAY, WHITE));

    if (curr->getKey() == key) {
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[4]->highlight();
            }));
        return true;
    }
    else if (curr->getKey() > key) {
        if (curr->leftEdge && curr->leftEdge->to) animManager.addAnimation(new TreapEdgeHighlight2Anim(curr->leftEdge, 1.75f, ORANGE, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[2]->highlight();
            }));
        return searchBeforeRemove(curr->leftEdge ? curr->leftEdge->to : nullptr, key);
    }
    else {
        if (curr->rightEdge && curr->rightEdge->to) animManager.addAnimation(new TreapEdgeHighlight2Anim(curr->rightEdge, 1.75f, ORANGE, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[3]->highlight();
            }));
        return searchBeforeRemove(curr->rightEdge ? curr->rightEdge->to : nullptr, key);
    }
}

void TreapUI::makeNodeDisappear(TreapNode* curr, int key) {
    if (!curr) return;

    if (curr->getKey() == key) {
        curr->keyBox->noDraw = true;
        curr->priorityBox->noDraw = true;
    }
    else if (curr->getKey() > key) {
        if (curr->leftEdge && curr->leftEdge->to) {
            makeNodeDisappear(curr->leftEdge->to, key);
            if (curr->leftEdge->to->getKey() == key) {
                curr->leftEdge->noDraw = true;
            }
        }
    }
    else {
        if (curr->rightEdge && curr->rightEdge->to) {
            makeNodeDisappear(curr->rightEdge->to, key);
            if (curr->rightEdge->to->getKey() == key) {
                curr->rightEdge->noDraw = true;
            }
        }
    }
}

void TreapUI::makeNodeDisappearWithAnimation(TreapNode* curr, int key) {
    if (!curr) return;

    if (curr->getKey() == key) {
        animManager.addAnimation(new Animation(0.1f, [curr]() {
            curr->keyBox->noDraw = true;
            curr->priorityBox->noDraw = true;
            }));
    }
    else if (curr->getKey() > key) {
        if (curr->leftEdge && curr->leftEdge->to) {
            makeNodeDisappearWithAnimation(curr->leftEdge->to, key);
            if (curr->leftEdge->to->getKey() == key) {
                animManager.addAnimation(new Animation(0.1f, [curr]() {
                    curr->leftEdge->noDraw = true;
                    }));
            }
        }
    }
    else {
        if (curr->rightEdge && curr->rightEdge->to) {
            makeNodeDisappearWithAnimation(curr->rightEdge->to, key);
            if (curr->rightEdge->to->getKey() == key) {
                animManager.addAnimation(new Animation(0.1f, [curr]() {
                    curr->rightEdge->noDraw = true;
                    }));
            }
        }
    }
}

void TreapUI::removeWithAnimation(int key) {
    TreapNode* del = searchForNode(key);
    animManager.addAnimation(new RectHighlight2Anim(del->keyBox, 3.0f, { 208, 82, 82, 255 }, DARKGRAY, WHITE));
    // No child
    if ((!del->leftEdge || !del->leftEdge->to) && (!del->rightEdge || !del->rightEdge->to)) {
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[5]->highlight();
            }));
        makeNodeDisappearWithAnimation(this->root, key);
        treap.remove(key);
        unordered_map<int, Vector2> positions = treap.getAllPositions();

        vector<TreapNode*> move;
        getNodesToMove(move, this->root);

        animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));
    }
    // Only right child
    else if (!del->leftEdge || !del->leftEdge->to) {
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[6]->highlight();
            }));
        animManager.addAnimation(new RectHighlight2Anim(del->rightEdge->to->keyBox, 3.0f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
        treap.remove(key);
        unordered_map<int, Vector2> positions = treap.getAllPositions();
        positions[del->getKey()] = positions[del->rightEdge->to->getKey()];

        vector<TreapNode*> move;
        getNodesToMove(move, del->rightEdge->to);
        move.push_back(del);

        animManager.addAnimation(new Animation(0.1f, [this, key]() {
            this->root = rotateLeftAtSpecificNode(this->root, key);
            makeNodeDisappear(this->root, key);
            }));

        animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));
    }
    // Only left child
    else if (!del->rightEdge || !del->rightEdge->to) {
        animManager.addAnimation(new Animation(0.5f, [this]() {
            unhighlightAllCodeBlocks();
            CodeBlocks[7]->highlight();
            }));
        animManager.addAnimation(new RectHighlight2Anim(del->leftEdge->to->keyBox, 3.0f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
        treap.remove(key);
        unordered_map<int, Vector2> positions = treap.getAllPositions();
        positions[del->getKey()] = positions[del->leftEdge->to->getKey()];

        vector<TreapNode*> move;
        getNodesToMove(move, del->leftEdge->to);
        move.push_back(del);

        animManager.addAnimation(new Animation(0.1f, [this, key]() {
            this->root = rotateRightAtSpecificNode(this->root, key);
            makeNodeDisappear(this->root, key);
            }));

        animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));
    }
    // Two children
    else {
        if (del->leftEdge->to->getPriority() > del->rightEdge->to->getPriority()) {
            animManager.addAnimation(new RectHighlight2Anim(del->leftEdge->to->priorityBox, 3.0f, ORANGE, DARKGRAY, WHITE, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[8]->highlight();
                }));
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[9]->highlight();
                }));
            animManager.addAnimation(new RectHighlight2Anim(del->leftEdge->to->keyBox, 3.0f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
            treap.rotateRightAtSpecificNode(key);

            unordered_map<int, Vector2> positions = treap.getAllPositions();

            vector<TreapNode*> move;
            getNodesToMove(move, del);

            animManager.addAnimation(new Animation(0.1f, [this, key]() {
                this->root = rotateRightAtSpecificNode(this->root, key);
                }));

            animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));

            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[10]->highlight();
                }));

            animManager.addAnimation(new Animation(1.0f, [this, key]() {
                removeWithAnimation(key);
                }));
        }
        else {
            animManager.addAnimation(new RectHighlight2Anim(del->rightEdge->to->priorityBox, 3.0f, ORANGE, DARKGRAY, WHITE, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[11]->highlight();
                }));
            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[12]->highlight();
                }));
            animManager.addAnimation(new RectHighlight2Anim(del->rightEdge->to->keyBox, 3.0f, { 82, 172, 16, 255 }, DARKGRAY, WHITE));
            treap.rotateLeftAtSpecificNode(key);
            
            unordered_map<int, Vector2> positions = treap.getAllPositions();

            vector<TreapNode*> move;
            getNodesToMove(move, del);

            animManager.addAnimation(new Animation(0.1f, [this, key]() {
                this->root = rotateLeftAtSpecificNode(this->root, key);
                }));

            animManager.addAnimation(new MoveMultipleTreapNodesAnim(move, positions, 1.5f));

            animManager.addAnimation(new Animation(0.5f, [this]() {
                unhighlightAllCodeBlocks();
                CodeBlocks[13]->highlight();
                }));

            animManager.addAnimation(new Animation(1.0f, [this, key]() {
                removeWithAnimation(key);
                }));
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

TreapNode* TreapUI::cloneTree(TreapNode* root) {
    if (!root) return nullptr;

    TreapNode* cloneRoot = new TreapNode(root->getKey(), root->getPriority(), root->position);
    cloneRoot->subtreeWidth = root->subtreeWidth;

    if (root->leftEdge) {
        cloneRoot->leftEdge = new TreapEdge(cloneRoot, cloneTree(root->leftEdge->to));
    }
    if (root->rightEdge) {
        cloneRoot->rightEdge = new TreapEdge(cloneRoot, cloneTree(root->rightEdge->to));
    }

    return cloneRoot;
}

void TreapUI::unhighlightAllCodeBlocks() {
    for (auto& c : CodeBlocks) {
        c->unhighlight();
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
    steps.clear();
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
    if (isAnimated) {
        cleanupForOperations();
        clear();
        this->root = nullptr;
        if (!stepByStepAnimation) {
            this->root = cloneTree(treap.root);
            RectButton::insertPseudoCode(CodeBlocks, PseudoCode::TreapInsert);
            insertWithAnimation(key, priority);
        }
        else {
            steps.push_back(new TreapStep(cloneTree(treap.root)));
            sbs_insertBST(treap.root, key, priority);
            steps.push_back(new TreapStep(cloneTree(treap.root)));
        }
    }
    else {
        clear();
        treap.insert(key, priority);
        this->root = cloneTree(treap.root);
    }
}

void TreapUI::search(int key) {
    cleanupForOperations();
    clear();
    this->root = cloneTree(treap.root);
    RectButton::insertPseudoCode(CodeBlocks, PseudoCode::TreapSearch);
    searchWithAnimation(root, key);
}

void TreapUI::remove(int key) {
    cleanupForOperations();
    clear();
    this->root = cloneTree(treap.root);
    RectButton::insertPseudoCode(CodeBlocks, PseudoCode::TreapRemove);
    if (!searchBeforeRemove(this->root, key)) return;
    removeWithAnimation(key);
}

void TreapUI::clear() {
    clear(this->root);
}

void TreapUI::init() {
    srand(time(nullptr));
    
    int n = rand() % 7;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        treap.insert(x, rand() % 100);
    }
    this->root = cloneTree(treap.root);

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
        cleanupForOperations();
        clear();
        treap.clear();
        int n = rand() % 7;
        for (int i = 0; i < n; ++i) {
            int x = rand() % 100;
            treap.insert(x, rand() % 100);
        }
        this->root = cloneTree(treap.root);
        };

    RectButton::insertHeadButton(Buttons, new TextBox(" Clear ",0,0, WHITE, { 214, 102, 49, 255 }, DARKGRAY));
    Buttons[5]->onClick = [this]() {
        cleanupForOperations();
        clear();
        this->root = nullptr;
        treap.clear();
        };

    CircleButton* GoPrevious = new TextCircle("<",
        {
            (float)UI::screenWidth / 2 - 60 - 55,
            (float)UI::screenHeight - 100
        },
        55.0f, BLACK, ORANGE, RED);

    GoPrevious->onClick = [this]() {
        goToPreviousStep();
        cerr << "click new GoPrevious" << endl;
        };

    OverrideButtons.push_back(GoPrevious);

    CircleButton* GoNext = new TextCircle(">",
        {
            (float)UI::screenWidth / 2 + 60 + 55,
            (float)UI::screenHeight - 100
        },
        55.0f, BLACK, ORANGE, RED);

    GoNext->onClick = [this]() {
        goToNextStep();
        cerr << "click new GoNext" << endl;
        };

    OverrideButtons.push_back(GoNext);

    CircleButton* test = new TextCircle("*", {
            GoPrevious->getCenterX(),
            GoPrevious->getCenterY() - 60 - 55
        },
        55.0f, BLACK, ORANGE, RED);

    test->onClick = [this, test]() {
        this->stepByStepAnimation = !this->stepByStepAnimation;
        if (stepByStepAnimation) cerr << "turn on step by step animations option" << endl;
        else cerr << "turn off step by step animations option" << endl;
        };

    OverrideButtons.push_back(test);


    updateButtonPositions();
}


void TreapUI::displayScene() {
    Button::drawButtons<RectButton>(Buttons);
    Button::drawButtons<CircleButton>(OverrideButtons);
    Button::drawButtons<RectButton>(CodeBlocks);
}

// 0: go previous
// 1: go next
void TreapUI::updateButtonPositions() {
    RectButton::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 5);
    if (UI::lastScreenWidth != UI::screenWidth || UI::lastScreenHeight != UI::screenHeight) {
        OverrideButtons[0]->setCenter(
            (float)UI::screenWidth / 2 - 60 - 55,
            (float)UI::screenHeight - 100
        );
        OverrideButtons[1]->setCenter(
            (float)UI::screenWidth / 2 + 60 + 55,
            (float)UI::screenHeight - 100
        );
        OverrideButtons[2]->setCenter(
            OverrideButtons[0]->getCenterX(),
            OverrideButtons[0]->getCenterY() - 60 - 55
        );
    }
    RectButton::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);
}

void TreapUI::updateScene() {
    animManager.update(GetFrameTime());

    Button::updateButtons<CircleButton>(OverrideButtons);
    Button::updateButtons<RectButton>(Buttons);
    Button::updateButtons<RectButton>(CodeBlocks);

    // Update treap node buttons recursively
    std::function<void(TreapNode*)> updateTreapNodes = [&](TreapNode* node) {
        if (!node) return;
        node->update();
        if (node->isModified()) {
            trashbin.push_back(this->root);
            treap.remove(node->originalKey);
            node->updateOriginalValues();
            cleanupForOperations();
            this->root = cloneTree(treap.root);
            RectButton::insertPseudoCode(CodeBlocks, PseudoCode::TreapInsert);
            insertWithAnimation(node->getKey(), node->getPriority());
        }
        if (node->leftEdge) updateTreapNodes(node->leftEdge->to);
        if (node->rightEdge) updateTreapNodes(node->rightEdge->to);
        };
    updateTreapNodes(root);

    if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}