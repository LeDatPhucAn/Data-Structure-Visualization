#include "../header/HashTable.h"
#include "../header/Animation.h"
#include "../header/PseudoCode.h"
#include "../header/UI.h"
#include "../header/tinyfiledialogs.h"
#include <fstream>
using namespace std;

vector<CBEdge*> HashTable::Edges;

HashTable::HashTable(int size) : bucketCount(size) {
    buckets.resize(size, nullptr);
    Edges.reserve(100);
}

HashTable::~HashTable() {
    clear();
}

void HashTable::loadFromFile(vector<RectButton*>& CodeBlocks, AnimationManager& animManager) {
    const char* filter[] = { "*.txt" };
    const char* filePath = tinyfd_openFileDialog(
        "Select a text file",
        "",
        1,
        filter,
        "Text file (*.txt)",
        0
    );

    if (filePath) {
        cout << "Trying to open the file: " << filePath << "\n";
        ifstream fin(filePath);
        if (fin.is_open()) {
            clear();
            int value;
            while (fin >> value) {
                if (value >= 0) {
                    randomInsert(value, 99);
                }
            }
            fin.close();
        }
        else {
            cerr << "Error: Cannot open file\n";
        }
    }
}

void HashTable::clearIndicates() {
    for (int i = 0; i < bucketCount; i++) {
        LLNode* cur = buckets[i];
        while (cur) {
            cur->indicateNode = "";
            cur = cur->next;
        }
    }
}

void HashTable::adjustPos(LLNode* head, int bucketIdx) {
    LLNode* prev = nullptr;
    float startX = 250 + bucketIdx * 200;
    float startY = 200;
    while (head) {
        if (!prev) {
            head->setCenter(startX, startY);
        }
        else {
            head->setCenterY(prev->getCenterY() + 150);
            head->setCenterX(startX);
        }
        prev = head;
        head = head->next;
    }
}

void HashTable::adjustPosWithAnim(AnimationManager& animManager, LLNode* head, int bucketIdx) {
    if (!head) return;
    float startX = 250 + bucketIdx * 200;
    float startY = 200;
    int index = 0;
    while (head) {
        float targetY = startY + index * 150;
        animManager.addAnimation(new CircleMoveAnim(head, 0.5f, head->getCenterX(), head->getCenterY(), startX, targetY));
        index++;
        head = head->next;
    }
}

void HashTable::insertNode(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x, int& pos) {
    clearIndicates();
    int idx = hashFunction(x);
    LLNode* newNode = new LLNode(x, 50, 400);
    newNode->noDraw = true;
    pos = 1;

    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
        CodeBlocks[1]->highlight();
        }));

    std::string indicateText = std::to_string(x) + "%" + std::to_string(bucketCount) + "=" + std::to_string(idx);

    Animation* insertAnim = new CircleHighLightAnim(newNode, 0.5f, GREEN, RAYWHITE, GREEN);
    insertAnim->Function = [newNode, indicateText]() {
        newNode->noDraw = false;
        newNode->indicateNode = indicateText;
        };
    animManager.addAnimation(insertAnim);

    if (!buckets[idx]) {
        buckets[idx] = newNode;
        animManager.addAnimation(new CircleMoveAnim(newNode, 0.5f, newNode->getCenterX(), 400, 250 + idx * 200, 200, [&CodeBlocks, newNode]() {
            CodeBlocks[1]->unhighlight();
            newNode->indicateNode = "InsertedNode";
            }));
    }
    else {
        LLNode* cur = buckets[idx];
        LLNode* prev = nullptr;
        while (cur) {
            prev = cur;
            cur = cur->next;
            pos++;
        }
        prev->next = newNode;
        CBEdge::addEdgeAndAnim(animManager, Edges, prev, newNode);
        Edges.back()->noDraw = true;
        adjustPosWithAnim(animManager, buckets[idx], idx);
        animManager.addAnimation(new Animation(0.1f, [newNode, &CodeBlocks]() {
            newNode->indicateNode = "InsertedNode";
            CodeBlocks[1]->unhighlight();
            }));
    }
}

void HashTable::randomInsert(int x, int pos) {
    int idx = hashFunction(x);
    LLNode* newNode = new LLNode(x, 250 + idx * 200, 200);

    if (!buckets[idx]) {
        buckets[idx] = newNode;
    }
    else {
        LLNode* cur = buckets[idx];
        for (int i = 1; i < pos - 1 && cur && cur->next; i++) {
            cur = cur->next;
        }

        newNode->next = cur->next;
        CBEdge::addEdge(Edges, newNode, cur->next);
        CBEdge::removeEdge(Edges, cur, cur->next);
        cur->next = newNode;
        CBEdge::addEdge(Edges, cur, newNode);

    }
    adjustPos(buckets[idx], idx);
}

bool HashTable::remove(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x, int& pos) {
    int idx = hashFunction(x);
    clearIndicates();
    pos = 1;

    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
        CodeBlocks[1]->highlight();
        }));

    LLNode* cur = buckets[idx];
    if (!cur) {
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[1]->unhighlight();
            CodeBlocks[2]->highlight();
            }));
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[2]->unhighlight();
            }));
        return false;
    }

    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks, cur]() {
        CodeBlocks[1]->unhighlight();
        CodeBlocks[2]->highlight();
        cur->indicateNode = "cur";
        }));

    const float nodeRadius = 30.0f;
    const float moveDistance = 1.5f * nodeRadius;

    if (cur->getNumber() == x) {
        deleteLater.insert(cur);
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f, GREEN, RAYWHITE, GREEN, [&CodeBlocks, cur]() {
            CodeBlocks[2]->unhighlight();
            CodeBlocks[3]->highlight();
            cur->indicateNode = "del";
            }));
        animManager.addAnimation(new CircleMoveXAnim(cur, 0.5f, cur->getCenterX(), cur->getCenterX() + moveDistance));
        animManager.addAnimation(new CircleRemoveAnim(cur, 0.5f));
        LLNode* nextNode = cur->next;
        CBEdge* edgeToRemove = nullptr;
        for (auto& edge : Edges) {
            if (edge->from == cur && edge->to == nextNode) {
                edgeToRemove = edge;
                break;
            }
        }
        if (edgeToRemove) {
            animManager.addAnimation(new CBEdgeHighLightAnim(edgeToRemove, 0.5f, PURPLE));
            animManager.addAnimation(new Animation(0.5f, [this, edgeToRemove]() {
                for (auto it = Edges.begin(); it != Edges.end(); ++it) {
                    if (*it == edgeToRemove) {
                        delete* it;
                        Edges.erase(it);
                        break;
                    }
                }
                }));
        }
        animManager.addAnimation(new Animation(0.5f, [this, cur, idx, nextNode, &CodeBlocks, &animManager]() {
            buckets[idx] = nextNode;
            adjustPosWithAnim(animManager, buckets[idx], idx);
            CodeBlocks[3]->unhighlight();
            }));
        return true;
    }

    while (cur->next) {
        pos++;
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f, ORANGE, RAYWHITE, ORANGE));
        for (auto& edge : Edges) {
            if (edge->from == cur && edge->to == cur->next) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 0.5f, PURPLE));
                break;
            }
        }
        if (cur->next->getNumber() == x) {

            LLNode* temp = cur->next;
            deleteLater.insert(temp);

            animManager.addAnimation(new CircleHighLightAnim(temp, 0.5f, GREEN, RAYWHITE, GREEN, [&CodeBlocks, temp]() {
                CodeBlocks[2]->unhighlight();
                CodeBlocks[3]->highlight();
                temp->indicateNode = "del";
                }));
            animManager.addAnimation(new CircleMoveXAnim(temp, 0.5f, temp->getCenterX(), temp->getCenterX() + moveDistance));
            animManager.addAnimation(new CircleRemoveAnim(temp, 0.5f));
            LLNode* nextNode = temp->next;
            CBEdge* edgeToCur = nullptr;
            CBEdge* edgeToNext = nullptr;
            for (auto& edge : Edges) {
                if (edge->from == cur && edge->to == temp) {
                    edgeToCur = edge;
                }
                if (edge->from == temp && edge->to == nextNode) {
                    edgeToNext = edge;
                }
            }
            if (edgeToCur) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edgeToCur, 0.5f, PURPLE));

                CBEdge::removeEdgeAndAnim(animManager, Edges, edgeToCur->from, edgeToCur->to);
                //animManager.addAnimation(new Animation(0.5f, [this, edgeToCur]() {
                //    for (auto it = Edges.begin(); it != Edges.end(); ++it) {
                //        if (*it == edgeToCur) {
                //            delete* it;
                //            Edges.erase(it);
                //            break;
                //        }
                //    }
                //    }));
            }
            if (edgeToNext) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edgeToNext, 0.5f, PURPLE));

                CBEdge::removeEdgeAndAnim(animManager, Edges, edgeToNext->from, edgeToNext->to);
                //animManager.addAnimation(new Animation(0.5f, [this, edgeToNext]() {
                //    for (auto it = Edges.begin(); it != Edges.end(); ++it) {
                //        if (*it == edgeToNext) {
                //            delete* it;
                //            Edges.erase(it);
                //            break;
                //        }
                //    }
                //    }));
            }
            if (nextNode) {
                CBEdge::addEdgeAndAnim(animManager, Edges, cur, nextNode);
                Edges.back()->noDraw = true;
                //animManager.addAnimation(new Animation(0.5f, [this, cur, nextNode, &animManager]() {
                //    CBEdge::addEdgeAndAnim(animManager, Edges, cur, nextNode);
                //    Edges.back()->noDraw = true;
                //    }));
            }
            animManager.addAnimation(new Animation(0.5f, [this, cur, temp, idx, nextNode, &CodeBlocks, &animManager]() {
                cur->next = nextNode;
                adjustPosWithAnim(animManager, buckets[idx], idx);
                CodeBlocks[3]->unhighlight();
                }));
            return true;
        }
        cur = cur->next;
    }

    animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f, ORANGE, RAYWHITE, ORANGE));
    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
        CodeBlocks[2]->unhighlight();
        }));
    return false;
}

bool HashTable::removeFromBucket(int x, int bucketIdx) {
    LLNode* cur = buckets[bucketIdx];
    if (!cur) return false;

    if (cur->getNumber() == x) {
        buckets[bucketIdx] = cur->next;
        CBEdge::removeEdge(Edges, cur, cur->next);
        deleteLater.insert(cur);
        adjustPos(buckets[bucketIdx], bucketIdx);
        return true;
    }

    while (cur->next) {
        if (cur->next->getNumber() == x) {
            LLNode* temp = cur->next;
            CBEdge::removeEdge(Edges, cur, temp);
            CBEdge::removeEdge(Edges, temp, temp->next);
            cur->next = temp->next;
            CBEdge::addEdge(Edges, cur, cur->next);
            deleteLater.insert(temp);
            adjustPos(buckets[bucketIdx], bucketIdx);
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool HashTable::search(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int x) {
    int idx = hashFunction(x);
    clearIndicates();

    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
        CodeBlocks[1]->highlight();
        }));

    LLNode* cur = buckets[idx];
    if (!cur) {
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[1]->unhighlight();
            CodeBlocks[2]->highlight();
            }));
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[2]->unhighlight();
            CodeBlocks[4]->highlight();
            }));
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[4]->unhighlight();
            }));
        return false;
    }

    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks, cur]() {
        CodeBlocks[1]->unhighlight();
        CodeBlocks[2]->highlight();
        cur->indicateNode = "cur";
        }));

    while (cur) {
        animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f, ORANGE, RAYWHITE, ORANGE));
        for (auto& edge : Edges) {
            if (edge->from == cur && edge->to == cur->next) {
                animManager.addAnimation(new CBEdgeHighLightAnim(edge, 0.5f, PURPLE));
                break;
            }
        }
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
            CodeBlocks[2]->unhighlight();
            CodeBlocks[3]->highlight();
            }));
        if (cur->getNumber() == x) {
            animManager.addAnimation(new CircleHighLightAnim(cur, 0.5f, GREEN, RAYWHITE, GREEN, [&CodeBlocks]() {
                CodeBlocks[3]->unhighlight();
                CodeBlocks[4]->highlight();
                }));
            animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
                CodeBlocks[4]->unhighlight();
                }));
            return true;
        }
        animManager.addAnimation(new Animation(0.5f, [&CodeBlocks, cur]() {
            CodeBlocks[3]->unhighlight();
            cur->indicateNode = "";
            if (cur->next) cur->next->indicateNode = "cur";
            }));
        cur = cur->next;
    }

    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
        CodeBlocks[2]->unhighlight();
        CodeBlocks[4]->highlight();
        }));
    animManager.addAnimation(new Animation(0.5f, [&CodeBlocks]() {
        CodeBlocks[4]->unhighlight();
        }));
    return false;
}

void HashTable::clear() {
    for (int i = 0; i < bucketCount; i++) {
        while (buckets[i]) {
            LLNode* temp = buckets[i];
            buckets[i] = buckets[i]->next;
            deleteLater.insert(temp);
        }
    }
    deleteEdges();
    for (auto node : deleteLater) {
        if (node) {
            delete node;
        }
    }
    deleteLater.clear();
}

void HashTable::resize(int newSize) {
    vector<LLNode*> oldBuckets = buckets;
    int oldSize = bucketCount;
    bucketCount = newSize;
    buckets.clear();
    buckets.resize(newSize, nullptr);
    deleteEdges();

    for (int i = 0; i < oldSize; i++) {
        LLNode* cur = oldBuckets[i];
        while (cur) {
            LLNode* next = cur->next;
            cur->next = nullptr;
            randomInsert(cur->getNumber(), 99);
            cur = next;
        }
    }
    for (int i = 0; i < oldSize; i++) {
        delete oldBuckets[i];
    }
}

void HashTable::deleteEdges() {
    for (auto edge : Edges) {
        delete edge;
    }
    Edges.clear();
}

void HashTable::restoreAfterInsert(int x, int pos) {
    int idx = hashFunction(x);
    LLNode* cur = buckets[idx];
    LLNode* prev = nullptr;
    int i = 1;

    if (pos == 1) {
        buckets[idx] = cur->next;
        Edges.erase(
            std::remove_if(Edges.begin(), Edges.end(),
                [cur](CBEdge* edge) {
                    if (edge->from == cur || edge->to == cur) {
                        delete edge;
                        return true;
                    }
                    return false;
                }),
            Edges.end()
        );
        deleteLater.insert(cur);
        return;
    }

    while (cur && i < pos) {
        prev = cur;
        cur = cur->next;
        i++;
    }

    if (!cur) return;

    prev->next = cur->next;
    Edges.erase(
        std::remove_if(Edges.begin(), Edges.end(),
            [cur](CBEdge* edge) {
                if (edge->from == cur || edge->to == cur) {
                    delete edge;
                    return true;
                }
                return false;
            }),
        Edges.end()
    );
    CBEdge::addEdge(Edges, prev, cur->next);
    adjustPos(buckets[idx], idx);
    deleteLater.insert(cur);
}

vector<int> HashTable::collectValues() {
    vector<int> values;
    for (int i = 0; i < bucketCount; i++) {
        LLNode* cur = buckets[i];
        while (cur) {
            values.push_back(cur->getNumber());
            cur = cur->next;
        }
    }
    return values;
}