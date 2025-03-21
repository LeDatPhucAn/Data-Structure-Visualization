#pragma once
#include "SinglyLinkedList.h"
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
	static constexpr float fontSize = 30.0f;
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

	static void interpolateColors(Color& color1, Color& color2, float t) {
		color1.r = (unsigned char)(color1.r + (color2.r - color1.r) * t);
		color1.g = (unsigned char)(color1.g + (color2.g - color1.g) * t);
		color1.b = (unsigned char)(color1.b + (color2.b - color1.b) * t);
		color1.a = (unsigned char)(color1.a + (color2.a - color1.a) * t);
	}
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