// Data Structure Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../header/Animation.h"
#include "../header/SinglyLinkedListUI.h"
#include "../header/SceneHandler.h"
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

	UI ui;
	ui.initTextures();
	if (UI::getfont().texture.id == 0) {
		std::cerr << "Font not initialized correctly!\n";
		return -1; // Exit the program if the font isn't initialized
	}
	SceneHandler scenehandler;
	scenehandler.changeScene(MENU);

	/// main functions
	while (!WindowShouldClose()) {

		// Get screen values
		UI::screenWidth = GetScreenWidth();
		UI::screenHeight = GetScreenHeight();


		/// draw background
		Rectangle screen = { 0, 0, ui.screenWidth, ui.screenHeight };
		DrawTexturePro(UI::Icons[2], screen, screen, { 0,0 }, 0, WHITE);

		if (IsKeyPressed(KEY_THREE))scenehandler.changeScene(MENU);

		// Update
		//----------------------------------------------------------------------------------
		
		scenehandler.updateCurrentScene();

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

		scenehandler.displayCurrentScene();
        // Draw mouse reference
        DrawCircleV(GetMousePosition(), 4, DARKGRAY);
        DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
		Vector2Add(GetMousePosition(), { -44, -24 }), 20, 2, BLACK);
        EndDrawing();


	CloseWindow();
	ui.cleanup();
}
