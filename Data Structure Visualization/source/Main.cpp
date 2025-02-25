// Data Structure Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "raylib.h"
#include "../header/UI.h"
#include "../header/SinglyLinkedListUI.h"
#include "header/Treap.h"

using namespace std;
int main()
{
	// InitWindow(1600, 1200, "Bruh");
	// SetWindowState(FLAG_WINDOW_RESIZABLE);


	// UI ui;
	// ui.initTextures();
	// if (UI::getfont().texture.id == 0) {
	// 	std::cerr << "Font not initialized correctly!\n";
	// 	return -1; // Exit the program if the font isn't initialized
	// }
	// SinglyLinkedListUI LinkedListUI;
	// LinkedListUI.insertnode(10, 1);
	// LinkedListUI.insertnode(20, 2);
	// LinkedListUI.insertnode(30, 1);
	// LinkedListUI.insertnode(40, 3);
	// LinkedListUI.remove(20);
	// LinkedListUI.insertnode(40, 1);
	// LinkedListUI.remove(40);
	// while (!WindowShouldClose()) {
	// 	if (IsKeyPressed(KEY_ONE))LinkedListUI.insertnode(40,1);
	// 	if (IsKeyPressed(KEY_TWO) && LinkedListUI.remove(40)) {
	// 		cout << "REMOVED!\n";
	// 	}
	// 	BeginDrawing();
	// 	ClearBackground(RAYWHITE);
	// 	LinkedListUI.drawlinkedlist();
	// 	EndDrawing();
	// }
	// CloseWindow();
	// ui.cleanup();

	InitWindow(1280, 720, "test");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);

	Treap treap;

	treap.insert(10);
	treap.insert(20);
	treap.insert(5);
	treap.insert(7);
	treap.insert(30);
	treap.insert(25);

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		treap.drawTreap();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
