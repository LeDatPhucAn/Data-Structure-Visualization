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
	void insertnode(T x);
};
template <typename T>
bool LinkedList<T>::remove(T x) {
    if (!head) return false;
    if (head && head->data == x) {
        LLNode<T>* del = head;
        head = head->next;
        delete del;
        del = nullptr;
        return true;
    }
    LLNode<T>* cur = head;
    while (cur->next) {
        if (cur->next->data == x) {
            LLNode<T>* temp = cur->next;
            cur->next = temp->next;
            delete temp;
            temp = nullptr;
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
void LinkedList<T>::insertnode(T x) {
    if (!head) {
        head = new LLNode<T>(x);
        return;
    }
    LLNode<T>* cur = head;
    while (cur && cur->next) {
        cur = cur->next;
    }
    cur->next = new LLNode<T>(x);
}