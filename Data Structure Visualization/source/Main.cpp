// Data Structure Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "raylib.h"
#include "../header/UI.h"
#include "../header/SinglyLinkedListUI.h"

using namespace std;
int main()
{
	InitWindow(1600, 1200, "Bruh");
	SetWindowState(FLAG_WINDOW_RESIZABLE);


	UI ui;
	ui.initTextures();
	SinglyLinkedListUI LinkedListUI;

	while (!WindowShouldClose()) {
		BeginDrawing();
		if (IsKeyPressed(KEY_ONE))LinkedListUI.insertnode(53);
		if (IsKeyPressed(KEY_TWO) && LinkedListUI.remove(53)) {
			cout << "REMOVED!\n";
		}
		ClearBackground(RAYWHITE);
		LinkedListUI.drawlinkedlist();
		EndDrawing();
	}
	CloseWindow();
	ui.cleanup();
}
