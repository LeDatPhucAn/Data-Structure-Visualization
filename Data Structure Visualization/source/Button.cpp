#include "../header/Button.h"

void InputBox::hover() { 
	OutLineColor = RED;
}
void InputBox::unhover() { 
	OutLineColor = DARKGRAY;
}
void InputBox::draw() { 
	DrawRectangleRec(rect, FillColor);

	DrawText(inputText.c_str(), (int)rect.x + 5, (int)rect.y + 8, UI::fontSize, TextColor);

	if (Texting)
	{
		DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, OutLineColor);
		// Draw blinking underscore char
		if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)rect.x + 8 + MeasureText(inputText.c_str(), UI::fontSize), (int)rect.y + 12, UI::fontSize, TextColor);
	}
}
void InputBox::update() { 
	framesCounter++;
	if (GetGestureDetected() == GESTURE_TAP) {
		Texting = 0;
	}
	if (CheckCollisionPointRec(GetMousePosition(), rect))
	{
		hover();

		// Set the window's cursor to the I-Beam
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		if (GetGestureDetected() == GESTURE_TAP) {
			Texting = 1;
		}
	}
	if (Texting) {

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

		if (IsKeyDown(KEY_BACKSPACE) && GetFrameTime() >= 0.014 && inputText.size() != 0 )
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
void NumberInputBox::update() { 
	framesCounter++;
	if (GetGestureDetected() == GESTURE_TAP) {
		Texting = 0;
	}
	if (CheckCollisionPointRec(GetMousePosition(), rect))
	{
		hover();

		// Set the window's cursor to the I-Beam
		SetMouseCursor(MOUSE_CURSOR_IBEAM);

		if (GetGestureDetected() == GESTURE_TAP) {
			Texting = 1;
		}
	}
	if (Texting) {

		// Get char pressed (unicode character) on the queue
		int key = GetCharPressed();

		// Check if more characters have been pressed on the same frame
		while (key > 0)
		{
			// NOTE: Only numbers
			if ( key >= '0' && key <= '9' && (inputText.size() < maxChars))
			{
				inputText.push_back(key);
				inputNumber = stoi(inputText);
			}

			key = GetCharPressed();  // Check next character in the queue
		}

		if (IsKeyDown(KEY_BACKSPACE) && GetFrameTime() == 0.01 && inputText.size() != 0 )
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

void Button::update() {
	if (CheckCollisionPointRec(GetMousePosition(), rect))
	{
		hover();
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) click();
		

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			onClick();
			unclick();
		}
	}
	else unhover();
}
void TextBox::draw() {
	DrawRectangleRec(rect, FillColor);
	DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, OutLineColor);
	DrawTextEx(UI::font, Text.c_str(), { rect.x+padding/2,rect.y+padding/2 }, UI::fontSize, UI::spacing, TextColor);
}