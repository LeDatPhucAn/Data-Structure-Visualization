#pragma once
#include "SinglyLinkedList.h"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <string>
#include "Edge.h"
using namespace std;
class UI {
protected:


public:
	UI();
	static Font font;
	static constexpr float fontSize = 40.0f;
	static constexpr float spacing = 2.0f;

	bool menuhovered = false;
	static int screenWidth;
	static int screenHeight;
	static vector <Texture2D> Icons;
	static vector <Texture2D> Buttons;
	static vector<Texture2D> selectedButtons;
	void initTextures();
	void drawButton(float X, float Y);
	void drawNode(Node* node);
	void drawlink(int X, int Y);
	static void drawtext2(string message, int X, int Y, Color color);
	void cleanup();

private:
	void UnLoadAllTextures();

};