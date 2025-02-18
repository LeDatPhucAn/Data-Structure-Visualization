#pragma once
#include "UI.h"
#include "SinglyLinkedList.h"
class SinglyLinkedListUI : public UI, public LinkedList {
public:
	void drawlinkedlist();
};