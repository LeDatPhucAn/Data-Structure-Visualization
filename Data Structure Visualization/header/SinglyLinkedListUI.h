#pragma once
#include "UI.h"
#include "SinglyLinkedList.h"
template <typename T>
class SinglyLinkedListUI : public UI, public LinkedList<T> {
private:
	static constexpr int headX = 100;
	static constexpr int headY = 450;
	static constexpr int radius = 50;
public:
	void drawlinkedlist();
};

template <typename T>
void SinglyLinkedListUI<T>::drawlinkedlist() {
	LLNode<T>* cur = this->head;
	int i = 1;
	while (cur) {
		drawnode(cur->data, headX + i, headY, radius);
		drawlink(headX + i + radius, headY - radius);
		i += 200;
		cur = cur->next;
	}


	drawtext2("NULL", headX + i, headY, BLUE);
}