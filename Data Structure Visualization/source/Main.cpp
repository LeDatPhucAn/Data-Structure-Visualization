// Data Structure Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../header/Animation.h"
#include "../header/SinglyLinkedListUI.h"
#include "../header/TreapUI.h"
#include "../header/SceneHandler.h"
#include "../header/Button.h"
#include "../header/UI.h"
using namespace std;

int main()
{
	InitWindow(UI::screenWidth, UI::screenHeight, "Bruh");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	UI ui;
	ui.initTextures();
	SceneHandler scenehandler;
	
	/// main functions
	while (!WindowShouldClose()) {

		// Get screen values
		UI::screenWidth = GetScreenWidth();
		UI::screenHeight = GetScreenHeight();

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
