#include "../header/Button.h"

void InputBox::hover() { // Renamed from TextBox to InputBox
	OutLineColor = RED;
}
void InputBox::unhover() { // Renamed from TextBox to InputBox
	OutLineColor = DARKGRAY;
}
void InputBox::draw() { // Renamed from TextBox to InputBox
	DrawRectangleRec(rect, FillColor);

	DrawText(inputText.c_str(), (int)rect.x + 5, (int)rect.y + 8, UI::fontSize, TextColor);

	if (Texting)
	{
		DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, OutLineColor);
		if (inputText.size() < maxChars)
		{
			// Draw blinking underscore char
			if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)rect.x + 8 + MeasureText(inputText.c_str(), UI::fontSize), (int)rect.y + 12, UI::fontSize, TextColor);
		}
	}
}
void InputBox::update() { // Renamed from TextBox to InputBox
	framesCounter++;

	if (Texting) {

		hover();

		// Get char pressed (unicode character) on the queue
		int key = GetCharPressed();

		// Check if more characters have been pressed on the same frame
		while (key > 0)
		{
			// NOTE: Only allow keys in range [32..125]
			if ((key >= 32) && (key <= 125) && (inputText.size() < maxChars))
			{
				inputText.push_back(key);
			}

			key = GetCharPressed();  // Check next character in the queue
		}

		if (IsKeyPressed(KEY_BACKSPACE) && inputText.size() != 0)
		{
			inputText.pop_back();
		}
	}
	else
	{
		unhover();
		framesCounter = 0;
	}
}

void TextBox::draw() {
	DrawRectangleRec(rect, FillColor);
	DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, OutLineColor);
	DrawTextEx(UI::font, Text.c_str(), { rect.x+10,rect.y+10 }, UI::fontSize, UI::spacing, TextColor);
}