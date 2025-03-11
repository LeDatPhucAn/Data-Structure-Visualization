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
	InitWindow(1600, 1200, "Bruh");
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
        
        
        EndDrawing();
		//----------------------------------------------------------------------------------
		
	}
	CloseWindow();
	ui.cleanup();
}
