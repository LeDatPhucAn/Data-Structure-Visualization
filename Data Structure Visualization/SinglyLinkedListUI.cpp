#include "SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
	node* cur = head;
	int i = 1;
	while (cur) {
		drawnode(cur->data, 100 * i, 100, 50);
		i += 2;
		cur = cur->next;
	}
}