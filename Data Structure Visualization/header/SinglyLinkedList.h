#pragma once
struct node {
	int data;
	node* next;
	node(int x) {
		data = x;
		next = nullptr;
	}
};
class LinkedList {
public:
	node* head;
	LinkedList() {
		head = new node(5);
		head->next = new node(2);
		head->next->next = new node(34);
		head->next->next->next = new node(-23);
		head->next->next->next->next= new node(53);
	}
	~LinkedList() {
		deletelist();
	}
	bool remove(int x);
	void printlist();
	void deletelist();
	void insertnode(int x);
};
