#include "../header/SinglyLinkedListUI.h"
template <typename T>
void SinglyLinkedListUI<T>::drawlinkedlist() {
	LLNode<T>* cur = head;
	int i = 1;
	while (cur) {
		drawnode(cur->data, headX + i, headY, radius);
		drawlink(headX + i + radius, headY - radius);
		i += 200;
		cur = cur->next;
	}
	

	drawtext2("NULL", headX + i, headY, BLUE);
}