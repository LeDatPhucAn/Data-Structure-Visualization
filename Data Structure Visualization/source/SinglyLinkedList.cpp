#include "../header/SinglyLinkedList.h"
#include "../header/Edge.h"
void LinkedList::adjustPos(LLNode* pHead) {
    LLNode* prev = nullptr;
    while (pHead) {
        if (prev) {
            pHead->position.x = prev->position.x + 200;
        }
        prev = pHead;
        pHead = pHead->next;
    }
}
void LinkedList::addEdge(LLNode* from, LLNode* to) {
    Edges.push_back(Edge(from, to));
}
void LinkedList::removeEdge(LLNode* from, LLNode* to) {
    for (int i = 0; i < Edges.size(); i++) {
        if (Edges[i].from == from && Edges[i].to == to) {
            cout << "REMOVED YO ASs";
            Edges.erase(Edges.begin()+i);
            return;
        }
    }
}
bool LinkedList::remove(int x) {
    if (!head) return false;
    if (head && head->data == x) {
        LLNode* del = head;
        head = head->next;

        if(head){
            // adjusting position
            head->position.x = 100;
            adjustPos(head);
            removeEdge(del, head);
        }

        delete del;
        del = nullptr;
        return true;
    }
    LLNode* cur = head;
    while (cur->next) {
        if (cur->next->data == x) {
            removeEdge(cur, cur->next);
            LLNode* temp = cur->next;
            removeEdge(temp, temp->next);
            cur->next = temp->next;
            addEdge(cur, cur->next);
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
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

void LinkedList::deletelist() {
    while (head) {
        LLNode* del = head;
        head = head->next;
        delete del;
    }
}

void LinkedList::insertnode(int x, int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1 || !head) {
        LLNode* temp = new LLNode(x,50,50);
        temp->next = head;
        adjustPos(temp);
        addEdge(temp, head);
        head = temp;
        return;
    }
    LLNode* cur = head;
    for (int i = 1; i < pos - 1 && cur; i++) {
        cur = cur->next;
    }
    if (!cur) return;
    LLNode* newnode = new LLNode(x,cur->position.x + 200, cur->position.y);
    newnode->next = cur->next;
    addEdge(newnode, cur->next);
    removeEdge(cur, cur->next);
    cur->next = newnode;
    adjustPos(newnode);
    addEdge(cur, newnode);
}
