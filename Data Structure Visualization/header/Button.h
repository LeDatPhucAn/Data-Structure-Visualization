#pragma once
#include <functional>
#include "raylib.h"
#include "UI.h"
#include <sstream>
class Animation;
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
    Animation* animation;
    std::function<void()> onClick;
    Button* head;
    Button* next; // Pointer to the next button

    Button(Rectangle r) : rect(r), TextColor(WHITE), FillColor(BLUE), OutLineColor(DARKGRAY),
        animation(nullptr),
        isActivated(false), isHovered(false), isClicked(false), onClick(nullptr), head(nullptr), next(nullptr) {
    };

    Button(Rectangle r, Color tc, Color fc, Color olc) : rect(r), TextColor(tc), FillColor(fc), OutLineColor(olc),
        animation(nullptr),
        isActivated(false), isHovered(false), isClicked(false), onClick(nullptr), head(nullptr), next(nullptr) {
    };

    virtual ~Button() {
        if (animation)delete animation;
    }
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

    virtual void resetSubAni();
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

    NumberInputBox() : InputBox(0), inputNumber(0) {
    }
    // default Number Input Box
    NumberInputBox(int maxCh) : InputBox(maxCh), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(int maxCh, Color tc, Color fc, Color olc) : InputBox(maxCh, tc, fc, olc), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    }
    NumberInputBox(Vector2 pos, int maxCh) : InputBox(pos.x,pos.y,maxCh), inputNumber(0) {
        Vector2 textSize = MeasureTextEx(UI::font, string(maxChars + 1, '0').c_str(), UI::fontSize, UI::spacing);
        rect.width = textSize.x + padding;
        rect.height = textSize.y + padding;
    
    }NumberInputBox(Vector2 pos, int maxCh, Color tc, Color fc, Color olc) : InputBox(pos.x,pos.y,maxCh, tc, fc, olc), inputNumber(0) {
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
    void setNumber(int x) {
        inputNumber = x;
    }
    int getNumber() const override {
        return inputNumber;
    };
    void update() override;
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
class CodeBlock : public TextBox {
public:
    static constexpr Color CodeColor = { 232,232,232,180 };
    CodeBlock(string t) : TextBox(t, DARKGRAY, CodeColor, CodeColor) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { 0, 0, tsize.x + padding, tsize.y + padding };
    }
    CodeBlock(string t, float x, float y) : TextBox(t, x, y, DARKGRAY, CodeColor, CodeColor) {
        Vector2 tsize = MeasureTextEx(UI::font, t.c_str(), UI::fontSize, UI::spacing);
        rect = { x, y, tsize.x + padding, tsize.y + padding };
    }
};


class CircleButton {
protected:
    Vector2 center;
    float radius;
public:
    Color TextColor;
    Color FillColor;
    Color RingColor;
    bool isActivated;
    bool isHovered;
    bool isClicked;
    Animation* animation;
    std::function<void()> onClick;

    // default color
    CircleButton(Vector2 cent, float r);

    CircleButton(Vector2 cent, float r, Color tc, Color fc, Color rc);
    virtual ~CircleButton(){
        if (animation)delete animation;
    }
    virtual void setRadius(int r) {
        radius = r;
    }
    virtual float getRadius() const{
        return radius;
    }
    virtual void setCenterX(int x) {
        center.x = x;
    }
    virtual int getCenterX() const {
        return center.x;
    }

    virtual void setCenterY(int y) {
        center.y = y;
    }
    virtual int getCenterY() const {
        return center.y;
    }
    virtual void update();
    virtual void draw() = 0;
    virtual void hover();
    virtual void unhover();
    virtual void click();
    virtual void unclick();
};



class InputCircle : public CircleButton {
public:
    double lastDeletedTime;
    int maxChars;
    int framesCounter;
    bool Texting;
    std::string inputText;

    InputCircle(int maxCh) : CircleButton({ 0,0 }, 50.0f), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {

    }
    InputCircle(int maxCh, Color tc, Color fc, Color rc) : CircleButton({ 0,0 }, 50.0f, tc, fc, rc), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {
    }

    // input Circle best ones

    InputCircle(Vector2 cent, float r, int maxCh) : CircleButton(cent, r), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {
    }
    InputCircle(Vector2 cent, float r, int maxCh, Color tc, Color fc, Color rc) : CircleButton(cent, r, tc, fc, rc), inputText(""), Texting(false), lastDeletedTime(0), maxChars(maxCh), framesCounter(0) {
    }
    void update() override;
    void draw() override;
    virtual void clear();
};
class NumberInputCircle : public InputCircle {
public:
    int inputNumber;

    // default Number Input Circle
    NumberInputCircle(int maxCh)
        : InputCircle(maxCh), inputNumber(0) {
    }
    NumberInputCircle(int maxCh, Color tc, Color fc, Color rc)
        : InputCircle(maxCh, tc, fc, rc), inputNumber(0) {
    }
    NumberInputCircle(Vector2 cent, float r, int input, int maxCh)
        : InputCircle(cent, r, maxCh) {
        setNumber(input);
    }
    NumberInputCircle(Vector2 cent, float r, int input, int maxCh, Color tc, Color fc, Color rc)
        : InputCircle(cent, r, maxCh, tc, fc, rc) {
        setNumber(input);
    }
    
    virtual void setNumber(int x) {
        inputNumber = x;
        inputText = to_string(x);
    }
    virtual int getNumber() const {
        return inputNumber;
    };
    void update() override;
    void clear() override;
};
class NumberInputCircleInCamera : public NumberInputCircle {
private:
    Camera2D camera;
public:
    // default Number Input Box
    NumberInputCircleInCamera(int maxCh)
        : NumberInputCircle(maxCh) {
    }
    NumberInputCircleInCamera(int maxCh, Color tc, Color fc, Color rc)
        : NumberInputCircle(maxCh, tc, fc, rc) {
    }
    NumberInputCircleInCamera(Vector2 cent, float r, int input, int maxCh)
        : NumberInputCircle(cent, r, input, maxCh) {
    }
    NumberInputCircleInCamera(Vector2 cent, float r, int input, int maxCh, Color tc, Color fc, Color rc)
        : NumberInputCircle(cent, r, input, maxCh, tc, fc, rc) {
    }
    void setCamera(Camera2D cam) {
        camera = cam;
    }
    void update() override;
};


