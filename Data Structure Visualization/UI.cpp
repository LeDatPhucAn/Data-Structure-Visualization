#include "UI.h"
#include "SinglyLinkedList.h"
#include <string>
void UI::drawnode(int data, int X, int Y, int r) {

	//Use default font
	Font font = GetFontDefault();
	
	//Turn the node value into a string
	std::string messageStr = std::to_string(data);
	const char* message = messageStr.c_str();

	// Measure text dimensions
	Vector2 textSize = MeasureTextEx(font, message, fontSize, spacing);

	//draw the node
	DrawCircle(X, Y, r, BLACK);
	DrawCircle(X, Y, r - 15, RAYWHITE);
	DrawText(message, X - textSize.x / 2, Y - textSize.y / 2, 40, BLUE);
}