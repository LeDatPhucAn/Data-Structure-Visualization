#include "../header/SinglyLinkedList.h"

bool LinkedList::remove(int x) {
    if (!head) return false;
    if (head && head->data == x) {
        LLNode* del = head;
        head = head->next;
        delete del;
        return true;
    }
    LLNode* cur = head;
    while (cur->next) {
        if (cur->next->data == x) {
            LLNode* temp = cur->next;
            cur->next = temp->next;
            delete temp;
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
        LLNode* temp = new LLNode(x);
        temp->next = head;
        head = temp;
        return;
    }
    LLNode* cur = head;
    for (int i = 1; i < pos - 1 && cur; i++) {
        cur = cur->next;
    }
    if (!cur) return;
    LLNode* newnode = new LLNode(x);
    newnode->next = cur->next;
    cur->next = newnode;
}
