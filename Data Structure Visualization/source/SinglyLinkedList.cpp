#include "../header/SinglyLinkedList.h"
#include "../header/Edge.h"
#include "../header/Animation.h"
vector<Edge*> LinkedList::Edges;
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

bool LinkedList::remove(int x) {
    if (!head) return false;
    if (head && head->data == x) {
        LLNode* del = head;
        head = head->next;

        if(head){
            // adjusting position
            head->position.x = 100;
            adjustPos(head);
            Edge::removeEdge(Edges, del, head);
        }
        delete del->animation;
        delete del;
        del = nullptr;
        return true;
    }
    LLNode* cur = head;
    while (cur->next) {
        if (cur->next->data == x) {
            Edge::removeEdge(Edges, cur, cur->next);
            LLNode* temp = cur->next;
            Edge::removeEdge(Edges, temp, temp->next);
            cur->next = temp->next;
            Edge::addEdge(Edges, cur, cur->next);
            adjustPos(cur);
            Edge::removeEdge(Edges, cur, temp);
            Edge::addEdge(Edges,cur, cur->next);
            delete temp->animation;
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
bool LinkedList::search(int x) {
    LLNode* cur = head;
    while (cur) {
        if (cur->data == x)return true;
        cur = cur->next;

    }
    return false;
}
void LinkedList::deletelist() {
    while (head) {
        LLNode* del = head;
        head = head->next;
        delete del->animation;
        delete del;
    }
    cout << "DELETED\n";
    head = nullptr;
}
void LinkedList::deleteEdges() {
    for (auto edge : Edges) {
        delete edge;
    }
    Edges.clear();
}
void LinkedList::insertnode(int x, int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1 || !head) {
        LLNode* temp = new LLNode(x,100,100);
		temp->animation = new NodeInitialAnimation(temp, 1);
        temp->next = head;
        adjustPos(temp);
        Edge::addEdge(Edges, temp, head);
        head = temp;
        return;
    }
    LLNode* cur = head;
    for (int i = 1; i < pos - 1 && cur && cur->next; i++) {
        cur = cur->next;
    }

    LLNode* newnode = new LLNode(x,cur->position.x + 200, cur->position.y);
    newnode->animation = new NodeInitialAnimation(newnode, 1);

    newnode->next = cur->next;
    Edge::addEdge(Edges, newnode, cur->next);
    Edge::removeEdge(Edges, cur, cur->next);
    cur->next = newnode;
    adjustPos(newnode);
    Edge::addEdge(Edges, cur, newnode);
}
