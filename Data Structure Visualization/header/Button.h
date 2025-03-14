#pragma once
#include "UI.h"

class Button {
protected:
    const int padding = UI::fontSize;
public:
    Rectangle rect;
    Color TextColor;
    Color FillColor;
    Color OutLineColor;
    bool isHovered; // Flag to track hover state
    bool isClicked; // Flag to track click state
    std::function<void()> onClick;
    Button() = default;
    Button(Rectangle r) : rect(r), TextColor(WHITE), FillColor(BLUE), OutLineColor(DARKGRAY), isHovered(false), isClicked(false), onClick(nullptr)  {} // default thematic button
    Button(Rectangle r, Color tc, Color fc, Color olc) : rect(r), TextColor(tc), FillColor(fc), OutLineColor(olc), isHovered(false), isClicked(false), onClick(nullptr) {}

    virtual void update();
    virtual void draw() = 0;

    virtual void hover() {
        if (!isHovered) {
            UI::darkenColor(FillColor, 30);
            UI::darkenColor(TextColor, 30);
            isHovered = true;
        }
    }

    virtual void unhover() {
        if (isHovered) {
            UI::lightenColor(FillColor, 30);
            UI::lightenColor(TextColor, 30);
            isHovered = false;
        }
    }

    virtual void click() {
        if (!isClicked) {
            UI::lightenColor(FillColor, 30);
            UI::lightenColor(TextColor, 30);
            isClicked = true;
        }
    }

    virtual void unclick() {
        if (isClicked) {
            UI::darkenColor(FillColor, 30);
            UI::darkenColor(TextColor, 30);
            isClicked = false;
        }
    }
};

class InputBox : public Button {
protected:
    int maxChars;
    int framesCounter;
    bool Texting;
public:
    string inputText;
    // default input box best one
    InputBox(float x, float y, int maxCh) : Button({x, y, x, y},MAROON,LIGHTGRAY,DARKGRAY), inputText(""), Texting(false), maxChars(maxCh), framesCounter(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars-1, 'W').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }  
    InputBox(Rectangle r) : inputText(""), Texting(false), Button(r, MAROON, LIGHTGRAY, DARKGRAY), maxChars(10), framesCounter(0) {} //default inputbox
    InputBox(Rectangle r, int maxCh) : inputText(""), Texting(false), Button(r, MAROON, LIGHTGRAY, DARKGRAY), maxChars(maxCh), framesCounter(0) {} 
    InputBox(float x, float y, float w, float h) : inputText(""), Texting(false), Button({ x,y,w,h }, MAROON, LIGHTGRAY, DARKGRAY), maxChars(10), framesCounter(0) {} //default inputbox
    void update() override;
    void draw();
    void hover() override;
    void unhover() override;
};
class NumberInputBox : public InputBox {
public:
    int inputNumber;

    // default Number Input Box
    NumberInputBox(float x, float y, int maxCh) : InputBox(x, y, maxCh), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars+1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    void update() override;
};
class TextBox : public Button {
private:
    string Text;
public:

    //default TextBox best one
    TextBox(string t, float x, float y) : Text(t), Button({ x,y,x,y }) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { x, y, tsize.x + padding, tsize.y + padding };
    }
    TextBox(Rectangle r, string t) : Text(t), Button(r) {} 
    TextBox(Rectangle r, string t, Color tc, Color fc, Color olc) : Text(t), Button(r, tc, fc, olc) {}
    void draw();
};

