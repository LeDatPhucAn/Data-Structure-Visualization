#include "UI.h"
class Button {
public:
	Rectangle rect;
	Color TextColor;
	Color FillColor;
	Color OutLineColor;
	Button() = default;
	Button(Rectangle r) : rect(r), TextColor(WHITE), FillColor(BLUE), OutLineColor(DARKGRAY) {} // default thematic button
	Button(Rectangle r, Color tc, Color fc, Color olc) : rect(r), TextColor(tc), FillColor(fc), OutLineColor(olc) {}
	virtual void hover() {
		UI::darkenColor(FillColor, 30);
		UI::darkenColor(TextColor, 30);
	}
	virtual void unhover() {
		UI::lightenColor(FillColor, 30);
		UI::lightenColor(TextColor, 30);
	}
	virtual void click() {
		UI::lightenColor(FillColor, 30);
		UI::lightenColor(TextColor, 30);
	}
	virtual void unclick() {
		UI::darkenColor(FillColor, 30);
		UI::darkenColor(TextColor, 30);
	}
};
class InputBox : public Button { 
private:
	int maxChars;
	int framesCounter;
public:
	string inputText;
	bool Texting;
	InputBox(Rectangle r) : inputText(""), Texting(false), Button(r, MAROON, LIGHTGRAY, DARKGRAY), maxChars(10), framesCounter(0) {} //default inputbox
	InputBox(float x, float y, float w, float h) : inputText(""), Texting(false), Button({x,y,w,h}, MAROON, LIGHTGRAY, DARKGRAY), maxChars(10), framesCounter(0) {} //default inputbox
	void update();
	void draw();
	void hover() override;
	void unhover() override;
};
class TextBox : public Button { 
private:
	string Text;
public:
	TextBox(string t, float x, float y) : Text(t) {
		Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
		rect = { x, y, tsize.x + UI::fontSize / 2, tsize.y + UI::fontSize / 2};
		TextColor = WHITE;
		FillColor = BLUE;
		OutLineColor = DARKGRAY;
	}
	TextBox(Rectangle r, string t) : Text(t), Button(r) {} //default TextBox
	TextBox(Rectangle r, string t, Color tc, Color fc, Color olc) : Text(t), Button(r,tc,fc,olc) {}
	void draw();
};
