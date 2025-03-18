#include "../header/Button.h"
bool Button::isCollision = false;

void Button::hover() {
    if (!isHovered) {
        UI::darkenColor(FillColor, 30);
        UI::darkenColor(TextColor, 30);
        isHovered = true;
    }
}

void Button::unhover() {
    if (isHovered) {
        UI::lightenColor(FillColor, 30);
        UI::lightenColor(TextColor, 30);
        isHovered = false;
    }
}

void Button::click() {
    if (!isClicked) {
        UI::lightenColor(FillColor, 30);
        UI::lightenColor(TextColor, 30);
        isClicked = true;
    }
}

void Button::unclick() {
    if (isClicked) {
        UI::darkenColor(FillColor, 30);
        UI::darkenColor(TextColor, 30);
        isClicked = false;
    }
}

void Button::insertHeadButton(vector<Button*>& Buttons, Button* button) {
    if (Buttons.empty()) {
        Buttons.push_back(button);
        return;
    }
    Button* prev = Buttons.back();
    Buttons.push_back(button);
    button->rect.x = prev->rect.x + prev->rect.width - button->rect.width;
    button->rect.y = prev->rect.y + prev->rect.height;
}
void Button::insertSubButton(Button* button) {
    Button* cur = this;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = button;
    button->head = this;
    button->rect = { cur->rect.x + cur->rect.width + padding / 2, cur->rect.y, button->rect.width, button->rect.height };
}
void Button::insertSubButton(Button* button, std::function<void()> function) {
    Button* cur = this;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = button;
    button->head = this;
    button->onClick = function;
    button->rect = { cur->rect.x + cur->rect.width + padding / 2, cur->rect.y, button->rect.width, button->rect.height };
}


void InputBox::hover() {
    OutLineColor = RED;
}

void InputBox::unhover() {
    OutLineColor = DARKGRAY;
}

void InputBox::draw() {
    if(!head || head->isActivated) {
        DrawRectangleRec(rect, FillColor);
        DrawText(inputText.c_str(), (int)rect.x + 5, (int)rect.y + 8, UI::fontSize, TextColor);
        if (Texting && (framesCounter / 20) % 2 == 0) {
            DrawText("_", (int)rect.x + 8 + MeasureText(inputText.c_str(), UI::fontSize), (int)rect.y + 12, UI::fontSize, TextColor);
        }
        DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, OutLineColor);
    }
    if (next) {
        next->draw();
    }
}

void InputBox::update() {
    if (!head || head->isActivated) {
        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            hover();
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isActivated = !isActivated; // Toggle state
            }
            Button::isCollision = true;
        }
        else {
            unhover();
        }
    }

    // Recursively update the next button
    if (next) {
        next->update();
    }

    if (!head || head->isActivated) {
        framesCounter++;
        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Texting = true;
            }
        }
        if (Texting) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (inputText.size() < maxChars)) {
                    inputText += static_cast<char>(key);
                }
                key = GetCharPressed();
            }
            double currenttime = GetTime();
            if (IsKeyPressed(KEY_BACKSPACE) && currenttime-lastDeletedTime>=0.1 && !inputText.empty()) {
                inputText.pop_back();
                lastDeletedTime = currenttime;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (onClick)onClick();
            }
        }
    }
}

void InputBox::clear(){
    inputText.clear();
}

void NumberInputBox::hover() {
    InputBox::hover();
}

void NumberInputBox::unhover() {
    InputBox::unhover();
}

void NumberInputBox::update() {
    if (!head || head->isActivated) {
        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            hover();
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isActivated = !isActivated; // Toggle state
            }
            Button::isCollision = true;
        }
        else {
            unhover();
        }
    }

    // Recursively update the next button
    if (next) {
        next->update();
    }

    if (!head || head->isActivated) {
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
                if (key >= '0' && key <= '9' && (inputText.size() < maxChars))
                {
                    inputText.push_back(key);
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            double currenttime = GetTime();
            if (IsKeyDown(KEY_BACKSPACE) && currenttime - lastDeletedTime >= 0.1 && inputText.size() != 0)
            {
                inputText.pop_back();
                lastDeletedTime = currenttime;
            }

            if (!inputText.empty()) {
                inputNumber = stoi(inputText); 
            } else {
                inputNumber = 0;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (onClick)onClick();
            }
        }
    }
}


void NumberInputBox::clear(){
    InputBox::clear();
    inputNumber = 0;
}

void Button::update() {
    // Head button logic: Toggle activation on click
    if(!head || head->isActivated){
        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            hover();
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isActivated = !isActivated; // Toggle state
                if (onClick) onClick();
            }
            Button::isCollision = true;
        }
        else {
            unhover();
        }
    }

    // Recursively update the next button
    if (next) {
        next->update();
    }
}
void TextBox::update() {
    if(!head || head->isActivated){
        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            hover();
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isActivated = !isActivated; // Toggle state
                if (onClick) onClick();
            }
            Button::isCollision = true;
        }
        else {
            unhover();
        }
    }

    // Recursively update the next button
    if (next) {
        next->update();
    }
}

void TextBox::draw() {
    if(!head || head->isActivated){
        DrawRectangleRec(rect, FillColor);
        DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, OutLineColor);
        DrawTextEx(UI::font, Text.c_str(), { rect.x + padding / 2,rect.y + padding / 2 }, UI::fontSize, UI::spacing, TextColor);
    }
    if (next) {
        next->draw();
    }
}
