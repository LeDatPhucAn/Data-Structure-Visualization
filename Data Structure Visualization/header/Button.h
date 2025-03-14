#pragma once
#include <functional>
#include "raylib.h"
#include "UI.h"
class Button {
public:
    const int padding = UI::fontSize;
    static bool isCollision;
    Rectangle rect;
    Color TextColor;
    Color FillColor;
    Color OutLineColor;
    bool isActivated;
    bool isHovered;
    bool isClicked;
    std::function<void()> onClick;

    Button* head;
    Button* next; // Pointer to the next button

    Button(Rectangle r) : rect(r), TextColor(WHITE), FillColor(BLUE), OutLineColor(DARKGRAY), isActivated(false), isHovered(false), isClicked(false), onClick(nullptr), head(this), next(nullptr) {}
    Button(Rectangle r, Color tc, Color fc, Color olc) : rect(r), TextColor(tc), FillColor(fc), OutLineColor(olc), isActivated(false), isHovered(false), isClicked(false), onClick(nullptr), head(this), next(nullptr) {}
    

    virtual int getNumber() const { return 0; }
    static void insertHeadButton(vector<Button*>& Buttons, Button* button) {
        if (Buttons.empty()) {
            Buttons.push_back(button);
            return;
        }
        Button* prev = Buttons.back();
        Buttons.push_back(button);
        button->rect.x = prev->rect.x + prev->rect.width - button->rect.width;
        button->rect.y = prev->rect.y + prev->rect.height;
    }
    virtual void insertSubButton(Button* button) {
        Button* cur = this;
        while(cur->next){
            cur = cur->next;
        }
        cur->next = button;
        button->head = this;
        button->rect = { cur->rect.x + cur->rect.width + padding/2, cur->rect.y, button->rect.width, button->rect.height };
    }
    virtual void insertSubButton(Button* button, std::function<void()> function) {
        Button* cur = this;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = button;
        button->head = this;
        button->onClick = function;
        button->rect = { cur->rect.x + cur->rect.width + padding/2, cur->rect.y, button->rect.width, button->rect.height };

    }


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
public:
    double lastDeletedTime;
    int maxChars;
    int framesCounter;
    bool Texting;
    std::string inputText;

    // default input box best one
    InputBox(int maxCh) : Button({ 0,0,0,0 }, MAROON, LIGHTGRAY, DARKGRAY), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars - 1, 'W').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    InputBox(int maxCh, Color tc, Color fc, Color olc) : Button({ 0, 0, 0, 0 }, tc, fc, olc), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars - 1, 'W').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    InputBox(float x, float y, int maxCh) : Button({ x, y, 0, 0 }, MAROON, LIGHTGRAY, DARKGRAY), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars - 1, 'W').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    InputBox(float x, float y, int maxCh, Color tc, Color fc, Color olc) : Button({ x, y, 0, 0 }, tc, fc, olc), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars - 1, 'W').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }

    void update() override;
    void draw() override;
    void hover() override;
    void unhover() override;
};

class NumberInputBox : public InputBox {
private:
    int inputNumber;
public:

    // default Number Input Box
    NumberInputBox(int maxCh) : InputBox(maxCh), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(int maxCh, Color tc, Color fc, Color olc) : InputBox(maxCh,tc, fc, olc), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(float x, float y, int maxCh) : InputBox(x, y, maxCh), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(float x, float y, int maxCh, Color tc, Color fc, Color olc) : InputBox(x, y, maxCh, tc, fc, olc), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    int getNumber() const override {
        return inputNumber;
    };
    void update() override;
    void hover() override;
    void unhover() override;
};

class TextBox : public Button {
public:
    std::string Text;

    TextBox(string t) : Text(t), Button({ 0,0,0,0 }) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { 0, 0, tsize.x + padding, tsize.y + padding };
    }
    TextBox(string t, Color tc, Color fc, Color olc) : Text(t), Button({ 0,0,0,0 }, tc, fc, olc) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { 0, 0, tsize.x + padding, tsize.y + padding };
    }
    TextBox(string t, float x, float y) : Text(t), Button({ x,y,0,0 }) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { x, y, tsize.x + padding, tsize.y + padding };
    }
    TextBox(string t, float x, float y, Color tc, Color fc, Color olc) : Text(t), Button({ x,y,0,0 }, tc, fc, olc) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { x, y, tsize.x + padding, tsize.y + padding };
    }

    void draw() override;
};
