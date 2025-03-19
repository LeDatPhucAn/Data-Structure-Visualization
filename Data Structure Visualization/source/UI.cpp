#include "../header/UI.h"
Font UI::font = { 0 };
int UI::screenWidth = 1600;
int UI::screenHeight = 900;
int UI::lastScreenWidth = 1600;
int UI::lastScreenHeight = 900;
vector<Texture2D> UI::Icons;
vector<Texture2D> UI::Buttons;
vector<Texture2D> UI::selectedButtons;
UI::UI() {
	if (font.texture.id == 0) {
		font = GetFontDefault();
	}
}

void UI::drawBackground() {
	Rectangle screen = { 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight)};
	Rectangle source = { 1300, 300,static_cast<float>(screenWidth), static_cast<float>(screenHeight)};
	DrawTexturePro(UI::Icons[2], source, screen, { 0,0 }, 0, LIGHTGRAY);
}

void UI::drawLogo() {
	Rectangle logo = { screenWidth / 2 - static_cast<float>(UI::Icons[3].width) / 2, static_cast<float> (screenHeight) / 64, static_cast<float> (UI::Icons[3].width), static_cast<float> (UI::Icons[3].height) };
	DrawTexturePro(UI::Icons[3], { 0,0,(float)UI::Icons[3].width,(float)UI::Icons[3].height }, logo, { 0,0 }, 0, RAYWHITE);
}

void UI::initTextures() {

	// Buttons
	Buttons.push_back(LoadTexture("assets/Buttons/SinglyLinkedList.png"));
	Buttons.push_back(LoadTexture("assets/Buttons/HashTable.png"));
	Buttons.push_back(LoadTexture("assets/Buttons/Treap.png"));
	Buttons.push_back(LoadTexture("assets/Buttons/Graph.png"));

	// Selected Buttons
	selectedButtons.push_back(LoadTexture("assets/Buttons/SinglyLinkedListSelected.png"));
	selectedButtons.push_back(LoadTexture("assets/Buttons/HashTableSelected.png"));
	selectedButtons.push_back(LoadTexture("assets/Buttons/TreapSelected.png"));
	selectedButtons.push_back(LoadTexture("assets/Buttons/GraphSelected.png"));


	// Icons
	Icons.push_back(LoadTexture("assets/Icons/rightarrow.png"));
	Icons.push_back(LoadTexture("assets/Icons/Sprite.png"));
	Icons.push_back(LoadTexture("assets/Backgrounds/technoBG.jpg"));
	Icons.push_back(LoadTexture("assets/Backgrounds/DSAlogo.png"));
	Icons.push_back(LoadTexture("assets/Icons/Pause.png"));
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

