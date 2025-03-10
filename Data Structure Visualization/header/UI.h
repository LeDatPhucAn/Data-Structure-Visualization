#pragma once
#include "SinglyLinkedList.h"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class UI {
protected:

	//Use default font
	static Font font;
	
	int totalicons = 3;
	static constexpr float fontSize = 40.0f;
	static constexpr float spacing = 2.0f;
public:
	UI();
	bool menuhovered = false;
	static int screenWidth;
	static int screenHeight;
	static vector <Texture2D> Icons;
	static vector <Texture2D> Buttons;
	static vector<Texture2D> selectedButtons;

	static Font getfont() {
		return font;
	}
	void initTextures();
	void drawButton(float X, float Y);
	void drawnode(int data, int X, int Y, int r);
	void drawlink(int X, int Y);
	void drawtext2(string message, int X, int Y, Color color);
	void cleanup();

private:
	void UnLoadAllTextures();

};