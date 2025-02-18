#pragma once
#include "SinglyLinkedList.h"
#include "raylib.h"
class UI {
protected:
	float fontSize = 40.0f;
	float spacing = 2.0f;
public:
	void drawnode(int data, int X, int Y, int r);

};