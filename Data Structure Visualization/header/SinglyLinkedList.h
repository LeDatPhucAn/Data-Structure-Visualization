#pragma once
#include "../header/LinkedListNode.h"

template <typename T>
class LinkedList : public LLNode<T> {
public:
	LLNode<T>* head;
	LinkedList() : head(nullptr) {}
	~LinkedList() {
		deletelist();
	}
	bool remove(T x);
	void printlist();
	void deletelist();
	void insertnode(T x,int pos);
};
template <typename T>
bool LinkedList<T>::remove(T x) {
    if (!head) return false;
    if (head && head->data == x) {
        LLNode<T>* del = head;
        head = head->next;
        delete del;
        return true;
    }
    LLNode<T>* cur = head;
    while (cur->next) {
        if (cur->next->data == x) {
            LLNode<T>* temp = cur->next;
            cur->next = temp->next;
            delete temp;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

template <typename T>
void LinkedList<T>::printlist() {
    LLNode<T>* cur = head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

template <typename T>
void LinkedList<T>::deletelist() {
    while (head) {
        LLNode<T>* del = head;
        head = head->next;
        delete del;
    }
}

template <typename T>
void LinkedList<T>::insertnode(T x, int pos) {
    if (pos<1) {
        return;
    }
    if (pos == 1) {
		LLNode<T>* temp = new LLNode<T>(x);
		temp->next = head;
		head = temp;
		return;
    }
    LLNode<T>* cur = head;
    for (int i = 1; i < pos - 1 && cur; i++) {
        cur = cur->next;
    }
    if (!cur)return;
    LLNode<T>* newnode = new LLNode<T>(x);
	newnode->next = cur->next;
    cur->next = newnode;
}