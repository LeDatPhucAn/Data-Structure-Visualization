#include "../header/Button.h"

void TextBox::hover() {
	OutLineColor = RED;
}
void TextBox::unhover() {
	OutLineColor = DARKGRAY;
}
void TextBox::draw() {
	DrawRectangleRec(rect, FillColor);

	DrawText(inputText.c_str(), (int)rect.x + 5, (int)rect.y + 8, UI::fontSize, TextColor);

	if (Texting)
	{
		DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, TextColor);
		if (inputText.size() < maxChars)
		{
			// Draw blinking underscore char
			if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)rect.x + 8 + MeasureText(inputText.c_str(), UI::fontSize), (int)rect.y + 12, UI::fontSize, TextColor);
		}
	}
}
void TextBox::update() {
	framesCounter++;

	if (Texting) {

		OutLineColor = RED;

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
		OutLineColor = DARKGRAY;
		framesCounter = 0;
	}
}