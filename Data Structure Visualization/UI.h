#pragma once
#include "LinkedList.h"
#include "raylib.h"
class UI {
public:

	void LinkedListVSL(LinkedList* list);
	void drawnode(node* head, int X, int Y, int r);
private:
	float fontSize = 40.0f;
	float spacing = 2.0f;
};