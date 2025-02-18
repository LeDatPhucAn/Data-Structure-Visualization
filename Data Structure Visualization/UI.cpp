#include "UI.h"
#include "LinkedList.h"
#include <string>
void UI::drawnode(node* head, int X, int Y, int r) {
	Font font = GetFontDefault();
	
	std::string messageStr = std::to_string(head->data);
	const char* message = messageStr.c_str();
	// Measure text dimensions
	Vector2 textSize = MeasureTextEx(font, message, fontSize, spacing);

	//draw the node
	DrawCircle(X, Y, r, BLACK);
	DrawCircle(X, Y, r - 15, RAYWHITE);
	DrawText(message, X - textSize.x / 2, Y - textSize.y / 2, 40, BLUE);
}
void UI::LinkedListVSL(LinkedList* list) {
	node* cur = list->head;
	int i = 1;
	while (cur) {
		drawnode(cur, 100 * i, 100, 50);
		i += 2;
		cur = cur->next;
	}
}