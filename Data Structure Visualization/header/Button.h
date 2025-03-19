#pragma once
#include <functional>
#include "raylib.h"
#include "UI.h"
#include <sstream>
class Button {
public:
    static const int padding;
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

    Button(Rectangle r) : rect(r), TextColor(WHITE), FillColor(BLUE), OutLineColor(DARKGRAY), isActivated(false), isHovered(false), isClicked(false), onClick(nullptr), head(nullptr), next(nullptr) {}
    Button(Rectangle r, Color tc, Color fc, Color olc) : rect(r), TextColor(tc), FillColor(fc), OutLineColor(olc), isActivated(false), isHovered(false), isClicked(false), onClick(nullptr), head(nullptr), next(nullptr) {}
    

    virtual int getNumber() const { return 0; }
    
    virtual void setPosition(float x, float y);
    virtual void setSubPosition();

    static void setHeadPosition(vector<Button*>& Buttons, float x, float y);
    static void setCodeBlockPosition(vector<Button*>& CodeBlocks, float x, float y);

    static void insertHeadButton(vector<Button*>& Buttons, Button* button);
    static void insertCodeBlock(vector<Button*>& Buttons, Button* button);
    static void insertPseudoCode(vector<Button*>& CodeBlocks, string pseudocode);

    static void drawButtons(vector<Button*>& Buttons);
    static void updateButtons(vector<Button*>& Buttons);
    static void deleteButtons(vector<Button*>& Buttons);

    virtual void insertSubButton(Button* button);
    virtual void insertSubButton(Button* button, std::function<void()> function);
    virtual void update();
    virtual void draw() = 0;
    virtual void hover();
    virtual void unhover();
    virtual void click();
    virtual void unclick();
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
    virtual void clear();
};

class NumberInputBox : public InputBox {
private:
    int inputNumber;
public:

    // default Number Input Box
    NumberInputBox(int maxCh) : InputBox(maxCh), inputNumber(0){
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(int maxCh, Color tc, Color fc, Color olc) : InputBox(maxCh,tc, fc, olc), inputNumber(0){
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(float x, float y, int maxCh) : InputBox(x, y, maxCh), inputNumber(0){
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(float x, float y, int maxCh, Color tc, Color fc, Color olc) : InputBox(x, y, maxCh, tc, fc, olc), inputNumber(0){
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
    void clear() override;
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
    void update() override;
};
class CodeBlock : public TextBox{
public:
    CodeBlock(string t) : TextBox(t, GRAY, RAYWHITE, RAYWHITE) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { 0, 0, tsize.x + padding, tsize.y + padding };
    }
    CodeBlock(string t, float x, float y) : TextBox(t, x, y,GRAY, RAYWHITE, RAYWHITE) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { x, y, tsize.x + padding, tsize.y + padding };
    }
};
