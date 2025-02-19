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
