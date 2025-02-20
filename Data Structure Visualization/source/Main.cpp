// Data Structure Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "raylib.h"
#include "../header/Animation.h"
#include "../header/SinglyLinkedListUI.h"

using namespace std;
int main()
{
	InitWindow(1600, 1200, "Bruh");
	SetWindowState(FLAG_WINDOW_RESIZABLE);


	UI ui;
	ui.initTextures();
	if (UI::getfont().texture.id == 0) {
		std::cerr << "Font not initialized correctly!\n";
		return -1; // Exit the program if the font isn't initialized
	}
	SinglyLinkedListUI LinkedListUI;
	LinkedListUI.insertnode(10, 1);
	LinkedListUI.insertnode(20, 2);
	LinkedListUI.insertnode(30, 1);
	LinkedListUI.insertnode(40, 3);
	LinkedListUI.remove(20);
	LinkedListUI.insertnode(40, 1);
	LinkedListUI.remove(40);

	Animation sprite;
	int frameindex = 0;
	int framedelay = 100;
	int framedelaycounter = 0;
	bool isanimating = false;
	float posX = 200;
	float posY = 200;
	while (!WindowShouldClose()) {

		// update
		if (IsKeyPressed(KEY_ONE))LinkedListUI.insertnode(40,2);
		if (IsKeyPressed(KEY_TWO) && LinkedListUI.remove(40)) {
			cout << "REMOVED!\n";
		}
		if (IsKeyDown(KEY_LEFT)) {
			posX-=0.25;
			isanimating = true;
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			posX+=0.25;
			isanimating = true;
		}
		else if (IsKeyDown(KEY_DOWN)) {
			posY += 0.25;
			isanimating = true;
		}
		else if (IsKeyDown(KEY_UP)) {
			posY -= 0.25;
			isanimating = true;
		}
		else {
			isanimating = false;
		}
		framedelaycounter++;
		if (framedelaycounter >= framedelay) {
			framedelaycounter = 0;
			if(isanimating)
			{
				frameindex++;
				if (frameindex == 10) frameindex = 0;
			}
		}
		// draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		sprite.AnimateSprite(posX, posY, UI::Icons[1], 10, frameindex);
		//LinkedListUI.drawlinkedlist();
		EndDrawing();
	}
	CloseWindow();
	ui.cleanup();

}
