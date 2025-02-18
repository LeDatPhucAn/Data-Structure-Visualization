#include<iostream>
#include"../header/SinglyLinkedList.h"
using namespace std;

bool LinkedList::remove(int x) {
	if (head && head->data == x) {
		node* del = head;
		head = head->next;
		delete del;
		return true;
	}
	node* cur = head;
	while (cur) {
		if (cur->data == x) {
			node* temp = cur;
			cur = cur->next;
			delete temp;
			return true;
		}
		head = head->next;
	}
	return false;
}
void LinkedList::printlist() {
	node* cur = head;
	while (cur) {
		cout << cur->data << " ";
		cur = cur->next;
	}
}
void LinkedList::deletelist() {
	while (head) {
		node* del = head;
		head = head->next;
		delete del;
	}
}
void LinkedList::insertnode(int x) {
	if (!head) {
		head = new node(x);
		return;
	}
	node* cur = head;
	while (cur && cur->next) {
		cur = cur->next;
	}
	cur->next = new node(x);
}