#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "Edge.h"
using namespace std;

class UI {
public:
	static Font font;
	static constexpr float spacing = 2.0f;
	static constexpr float fontSize = 20.0f;
	UI();

	bool menuhovered = false;
	static int screenWidth;
	static int screenHeight;
	static int lastScreenWidth;
	static int lastScreenHeight;
	static vector <Texture2D> Icons;
	static vector <Texture2D> Buttons;
	static vector<Texture2D> selectedButtons;
	void initTextures();
	
	static void drawBackground();
	static void drawLogo();
	static void drawNode(Node* node);
	static void drawlink(int X, int Y);
	static void drawtext2(string message, int X, int Y, Color color);

	static void darkenColor(Color& color, int amount) {
		color.r = (unsigned char)(color.r - amount < 0 ? 0 : color.r - amount);
		color.g = (unsigned char)(color.g - amount < 0 ? 0 : color.g - amount);
		color.b = (unsigned char)(color.b - amount < 0 ? 0 : color.b - amount);
	}
	static void lightenColor(Color& color, int amount) {
		color.r = (unsigned char)(color.r + amount > 255 ? 255 : color.r + amount);
		color.g = (unsigned char)(color.g + amount > 255 ? 255 : color.g + amount);
		color.b = (unsigned char)(color.b + amount > 255 ? 255 : color.b + amount);
	}

	void cleanup();

private:
	void UnLoadAllTextures();

};