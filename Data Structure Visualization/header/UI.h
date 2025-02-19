#pragma once
#include "SinglyLinkedList.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class UI {
protected:

	//Use default font
	static Font font;

	int totalicons = 1;
	static vector <Texture2D> Icons;
	static constexpr float fontSize = 40.0f;
	static constexpr float spacing = 2.0f;
public:
	void initTextures();
	void drawnode(int data, int X, int Y, int r);
	void drawlink(int X, int Y);
	void drawtext2(string message, int X, int Y, Color color);
	void cleanup();

private:
	void UnLoadAllTextures();

};