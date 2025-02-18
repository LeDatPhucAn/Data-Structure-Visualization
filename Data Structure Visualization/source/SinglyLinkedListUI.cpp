#include "../header/SinglyLinkedListUI.h"

void SinglyLinkedListUI::drawlinkedlist() {
	node* cur = head;
	int i = 1;
	while (cur) {
		drawnode(cur->data, headX + i, headY, radius);
		DrawTexture(Icons[0], headX + i + radius, headY - radius,WHITE);
		i += 200;
		cur = cur->next;
	}
	drawtext2("NULL", headX + i, headY, BLUE);
}