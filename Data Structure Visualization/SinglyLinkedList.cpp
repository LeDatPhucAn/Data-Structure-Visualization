#pragma once
#include<iostream>
#include"SinglyLinkedList.h"
using namespace std;

bool LinkedList::remove(node*& head, int x) {
	if (!head) return false;

	if (head->data == x) {
		node* temp = head;
		head = head->next;
		delete temp;
		return true;
	}

	return remove(head->next, x);
}
void LinkedList::printlist() {
	while (head) {
		cout << head->data << " ";
		head = head->next;
	}
}
void LinkedList::deletelist() {
	while (head) {
		node* del = head;
		head = head->next;
		delete del;
	}
}
void LinkedList::insertnode(node* head, int x) {
	if (!head) {
		head = new node(x);
		return;
	}
	while (head && head->next) {
		head = head->next;
	}
	head->next = new node(x);
}