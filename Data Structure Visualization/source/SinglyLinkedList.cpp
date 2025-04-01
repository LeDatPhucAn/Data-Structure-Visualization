#include "../header/SinglyLinkedList.h"
#include "../header/Edge.h"
#include "../header/Animation.h"
#include "../header/tinyfiledialogs.h"
#include <fstream>
vector<CBEdge*> LinkedList::Edges;

void LinkedList::loadFromFile() {
    const char* filter[] = { "*.txt" };
    const char* filePath = tinyfd_openFileDialog(
        "Select a text file", // Title
        "", // Default path (empty = open from last used folder)
        1, // Number of filter patterns
        filter, // Filter patterns
        "Text file (*.txt)", // Filter description
        0 // Single file seclection mode
    );

    if (filePath) {
        cout << "Trying to open the file: " << filePath << "\n";
        ifstream fin(filePath);
        if (fin.is_open()) {
            deletelist();
            deleteEdges();
            string line;
            int pos = 1;
            int key = 0;
            while (fin>>key) {
                insertnode(key,pos);
                pos++;
            }
        }
        else cerr << "Error: Can not open file\n";
        fin.close();
    }
}
void LinkedList::adjustPos(LLNode* pHead) {
    LLNode* prev = nullptr;
    while (pHead) {
        if (prev) {
            pHead->setCenterX(prev->getCenterX() + 200);
            pHead->setCenterX(pHead->getCenterX());
        }

        prev = pHead;
        pHead = pHead->next;
    }
}

bool LinkedList::remove(int x) {
    if (!head) return false;
    if (head && head->getNumber() == x) {
        LLNode* del = head;
        head = head->next;

        if(head){
            CBEdge::removeEdge(Edges, del, head);
            // adjusting position
            head->setCenterX(100);
            adjustPos(head);
        }
        delete del;
        del = nullptr;
        return true;
    }
    LLNode* cur = head;
    while (cur->next) {
        if (cur->next->getNumber() == x) {
            CBEdge::removeEdge(Edges, cur, cur->next);
            LLNode* temp = cur->next;
            CBEdge::removeEdge(Edges, temp, temp->next);
            cur->next = temp->next;
            CBEdge::addEdge(Edges, cur, cur->next);
            adjustPos(cur);
            delete temp;
            temp = nullptr;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void LinkedList::printlist() {
    LLNode* cur = head;
    while (cur) {
        cout << cur->getNumber() << " ";
        cur = cur->next;
    }
    cout << endl;
}
bool LinkedList::search(int x) {
    LLNode* cur = head;
    while (cur) {
        if (cur->getNumber() == x)return true;
        cur = cur->next;

    }
    return false;
}
void LinkedList::deletelist() {
    while (head) {
        LLNode* del = head;
        head = head->next;
        delete del;
    }
}
void LinkedList::deleteEdges() {
    for (auto edge : Edges) {
        delete edge;
    }
}
void LinkedList::insertnode(int x, int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1 || !head) {
        LLNode* temp = new LLNode(x,100,100);
        temp->next = head;
        adjustPos(temp);
        CBEdge::addEdge(Edges, temp, head);
        head = temp;
        return;
    }
    LLNode* cur = head;
    for (int i = 1; i < pos - 1 && cur; i++) {
        cur = cur->next;
    }

    LLNode* newnode = new LLNode(x,cur->getCenterX() + 200, cur->getCenterY());

    newnode->next = cur->next;
    CBEdge::addEdge(Edges, newnode, cur->next);
    CBEdge::removeEdge(Edges, cur, cur->next);
    cur->next = newnode;
    adjustPos(newnode);
    CBEdge::addEdge(Edges, cur, newnode);
}
