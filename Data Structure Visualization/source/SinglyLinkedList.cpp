#include<iostream>
#include"../header/SinglyLinkedList.h"
using namespace std;

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
void LinkedList<T>::insertnode(T x) {
    if (!head) {
        head = new LLNode(x);
        return;
    }
    LLNode<T>* cur = head;
    while (cur && cur->next) {
        cur = cur->next;
    }
    cur->next = new LLNode(x);
}