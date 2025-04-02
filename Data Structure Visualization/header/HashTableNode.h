#pragma once
#include "Button.h"
using namespace std;

class HashTableNode : public NumberInputCircleInCamera {
private:
    int centerX;
    int centerY;
    int originalNumber;

public:
    HashTableNode(int number, int x, int y, float radius = 50.0f);
    void setCenterX(int x) override { centerX = x; NumberInputCircleInCamera::setCenterX(x); }
    void setCenterY(int y) override { centerY = y; NumberInputCircleInCamera::setCenterY(y); }
    int getCenterX() const override { return centerX; }
    int getCenterY() const override { return centerY; }
    float getCenterXFloat() const { return static_cast<float>(centerX); }
    float getCenterYFloat() const { return static_cast<float>(centerY); }
    int getOriginalNumber() const { return originalNumber; }
    void setOriginalNumber(int number) { originalNumber = number; }
    void draw() override;
    string getInputText() const { return inputText; }
};