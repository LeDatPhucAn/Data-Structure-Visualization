#include "../header/UI.h"

Font UI::font = { 0 };

vector<Texture2D> UI::Icons;

UI::UI() {
	if (font.texture.id == 0) {
		font = GetFontDefault();
	}
}

void UI::initTextures() {
	if (font.texture.id == 0) {
		cout << "Error: Default font not loaded correctly!" << endl;
	}
	Icons.push_back(LoadTexture("assets/Icons/rightarrow.png"));
}


/// <summary>
/// Draw functions
/// </summary>

void UI::drawtext2(string message, int X, int Y, Color color) {
	const char* messageStr = message.c_str();
	//Font font = GetFontDefault();
	// Measure text dimensions
	Vector2 textSize = MeasureTextEx(font, messageStr, fontSize, spacing);
	DrawText(messageStr, X - textSize.x / 2, Y - textSize.y / 2, fontSize, color);

}

void UI::drawnode(int data, int X, int Y, int r) {
	//draw the node
	DrawCircle(X, Y, r, BLACK);
	DrawCircle(X, Y, r * 4/5, RAYWHITE);
	drawtext2(to_string(data), X, Y, BLUE);
}

void UI::drawlink(int X, int Y) {
	DrawTexture(Icons[0], X, Y, WHITE);
}



/// <summary>
/// Cleanup functions
/// </summary>

void UI::UnLoadAllTextures() {
	for (const auto& texture : Icons) {
		UnloadTexture(texture);
	}
	Icons.clear();
}

void UI::cleanup() {
	UnLoadAllTextures();
}
