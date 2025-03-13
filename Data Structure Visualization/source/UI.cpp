#include "../header/UI.h"

Font UI::font = { 0 };
int UI::screenWidth = GetScreenWidth();
int UI::screenHeight = GetScreenHeight();
vector<Texture2D> UI::Icons;
vector<Texture2D> UI::Buttons;
vector<Texture2D> UI::selectedButtons;
UI::UI() {
	if (font.texture.id == 0) {
		font = GetFontDefault();
	}
}

void UI::drawBackground() {
	Rectangle screen = { 0, 0, screenWidth, screenHeight };
	Rectangle source = { 1300, 300,screenWidth, screenHeight };
	DrawTexturePro(UI::Icons[2], source, screen, { 0,0 }, 0, LIGHTGRAY);
}
void UI::drawLogo() {
	Rectangle logo = { screenWidth / 2 - UI::Icons[3].width / 2, screenHeight / 64, UI::Icons[3].width, UI::Icons[3].height };
	DrawTexturePro(UI::Icons[3], { 0,0,(float)UI::Icons[3].width,(float)UI::Icons[3].height }, logo, { 0,0 }, 0, WHITE);
}
void UI::initTextures() {

	// credit https://github.com/BJMinhNhut/data-visualization-2
	// Buttons
	Buttons.push_back(LoadTexture("assets/Buttons/menu-sll-normal.png"));
	Buttons.push_back(LoadTexture("assets/Buttons/menu-hash-normal.png"));
	Buttons.push_back(LoadTexture("assets/Buttons/menu-trie-normal.png"));
	Buttons.push_back(LoadTexture("assets/Buttons/menu-graph-normal.png"));

	// Selected Buttons
	selectedButtons.push_back(LoadTexture("assets/Buttons/menu-sll-selected.png"));
	selectedButtons.push_back(LoadTexture("assets/Buttons/menu-hash-selected.png"));
	selectedButtons.push_back(LoadTexture("assets/Buttons/menu-trie-selected.png"));
	selectedButtons.push_back(LoadTexture("assets/Buttons/menu-graph-selected.png"));


	// Icons
	Icons.push_back(LoadTexture("assets/Icons/rightarrow.png"));
	Icons.push_back(LoadTexture("assets/Icons/Sprite.png"));
	Icons.push_back(LoadTexture("assets/Backgrounds/technoBG.jpg"));
	Icons.push_back(LoadTexture("assets/Backgrounds/DSAlogo.png"));
}


/// <summary>
/// Draw functions
/// </summary>

void UI::drawtext2(string message, int X, int Y, Color color) {
	const char* messageStr = message.c_str();

	// Measure text dimensions
	Vector2 textSize = MeasureTextEx(font, messageStr, fontSize, spacing);
	DrawText(messageStr, X - textSize.x / 2, Y - textSize.y / 2, fontSize, color);

}
void UI::drawButton(float X, float Y) {
	float roundness = 0.5f;
	float width = 250.0f;
	float height = 100.0f;
	float segments = 0.0f;
	float lineThick = 12.0f;
	Rectangle rec = { X, Y, (float)width, (float)height };
	DrawRectangleRounded(rec, roundness, (int)segments, Fade(MAROON, 0.2f));
	DrawRectangleRoundedLinesEx(rec, roundness, (int)segments, lineThick, Fade(MAROON, 0.4f));
}

void UI::drawNode(Node* node) {
	if (!node)return;
	string message = to_string(node->data);
	DrawRing(node->position, node->radius * 4 / 5, node->radius, 0, 360, 100, BLUE);
	drawtext2(to_string(node->data), node->position.x, node->position.y, BLUE);
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

	for (const auto& texture : Buttons) {
		UnloadTexture(texture);
	}
	Buttons.clear();
}

void UI::cleanup() {
	UnLoadAllTextures();
}

