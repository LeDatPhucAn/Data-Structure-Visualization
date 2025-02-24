// Data Structure Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "../header/Animation.h"
#include "../header/SinglyLinkedListUI.h"

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
	SinglyLinkedListUI LinkedListUI;
	LinkedListUI.insertnode(10, 1);
	LinkedListUI.insertnode(20, 2);
	LinkedListUI.insertnode(30, 1);
	LinkedListUI.insertnode(40, 3);
	LinkedListUI.remove(20);
	LinkedListUI.insertnode(40, 1);
	LinkedListUI.remove(40);
	Camera2D camera = { 0 };
	camera.zoom = 1.0f;
	Animation sprite;
	int radius = 0;
	float frameindex = 0;
	int framedelay = 100;
	int framedelaycounter = 0;
	bool isanimating = false;
	float speed = 1000;
	float zoomspeed = 2;
	bool visible = false;
    bool zoomMode = 1;
	Vector2 circlepos = { 100,100 };
	while (!WindowShouldClose()) {

		// update
		Vector2 motion = { 0,0 };
		Rectangle screen = { 0, 0, GetScreenWidth(), GetScreenHeight() };
		DrawTexturePro(UI::Icons[2], screen, screen, { 0,0 }, 0, WHITE);
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}
		if (IsKeyPressed(KEY_ONE))LinkedListUI.insertnode(40, 2);
		if (IsKeyPressed(KEY_TWO) && LinkedListUI.remove(40)) {
			cout << "REMOVED!\n";
		}
		if (IsKeyPressed(KEY_THREE))visible = !visible;
		if (IsKeyDown(KEY_LEFT)) {
			motion.x -= 1;
			isanimating = true;
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			motion.x += 1;
			isanimating = true;
		}
		if (IsKeyDown(KEY_DOWN)) {
			motion.y += 1;
			isanimating = true;
		}
		else if (IsKeyDown(KEY_UP)) {
			motion.y -= 1;
			isanimating = true;
		}
		if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)) {
			isanimating = false;
		}

        // Translate based on mouse right click
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }

            // Zoom based on mouse wheel
            float wheel = GetMouseWheelMove();
            if (wheel != 0)
            {
                // Get the world point that is under the mouse
                Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                // Set the offset to where the mouse is
                camera.offset = GetMousePosition();

                // Set the target to match, so that the camera maps the world space point 
                // under the cursor to the screen space point under the cursor at any zoom
                camera.target = mouseWorldPos;

                // Zoom increment
                float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
                if (wheel < 0) scaleFactor = 1.0f / scaleFactor;

				// limit the values of zoom
                camera.zoom = Clamp(camera.zoom * scaleFactor, 0.25f, 10.0f);
            }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        // Draw the 3d grid, rotated 90 degrees and centered around 0,0 
        // just so we have something in the XY plane
        rlPushMatrix();
        rlTranslatef(0, 10000, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(1000, 100);
        rlPopMatrix();

        // Draw a reference circle
        DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);
        LinkedListUI.drawlinkedlist();
        EndMode2D();
        // Draw mouse reference
        //Vector2 mousePos = GetWorldToScreen2D(GetMousePosition(), camera)
        DrawCircleV(GetMousePosition(), 4, DARKGRAY);
        DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
		Vector2Add(GetMousePosition(), { -44, -24 }), 20, 2, BLACK);

        DrawText("[1][2] Select mouse zoom mode (Wheel or Move)", 20, 20, 20, DARKGRAY);
        if (zoomMode == 0) DrawText("Mouse left button drag to move, mouse wheel to zoom", 20, 50, 20, DARKGRAY);
        else DrawText("Mouse left button drag to move, mouse press and move to zoom", 20, 50, 20, DARKGRAY);

        EndDrawing();

		
	}
	CloseWindow();
	ui.cleanup();

}
