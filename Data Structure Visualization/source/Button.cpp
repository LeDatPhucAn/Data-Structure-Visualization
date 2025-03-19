#include "../header/Button.h"
bool Button::isCollision = false;
const int Button::padding = UI::fontSize;

void Button::deleteButtons(vector<Button*>& Buttons) {
    for (auto button : Buttons) {
        while (button) {
            Button* del = button;
            button = button->next;
            delete del;
        }
    }
}

void Button::drawButtons(vector<Button*>& Buttons) {
    for (auto button : Buttons) {
        button->draw();
    }
}

void Button::updateButtons(vector<Button*>& Buttons) {
    for (auto button : Buttons) {
        button->update();
    }
}

void Button::setPosition(float x, float y) {
    rect.x = x;
    rect.y = y;
}

void Button::setSubPosition() {
    Button* prev = this;
    Button* cur = this->next;
    while (cur) {
        cur->setPosition(prev->rect.x + prev->rect.width + padding / 2, prev->rect.y);
        prev = cur;
        cur = cur->next;
    }
}

void Button::setHeadPosition(vector<Button*>&Buttons, float x, float y) {
    if (Buttons.empty()) {
        cout << "YO ur Button is missing";
        return;
    }

    // Update the first head
    Buttons[0]->setPosition(x, y);
    Buttons[0]->setSubPosition();

    for (int i = 1; i < Buttons.size(); i++) {
        // update the group Head Buttons
        Button* prevHead = Buttons[i - 1];
        Button* curHead = Buttons[i];
        curHead->setPosition(
            prevHead->rect.x,
            prevHead->rect.y + prevHead->rect.height
        );
        // update the Sub Buttons
        Buttons[i]->setSubPosition();
    }
}

void Button::setCodeBlockPosition(vector<Button*>& CodeBlocks, float x, float y) {
    if (CodeBlocks.empty()) {
        cout << "YO ur Button is missing";
        return;
    }

    // Update the first head
    CodeBlocks[0]->setPosition(x, y);
    CodeBlocks[1]->setPosition(
		CodeBlocks[0]->rect.x - CodeBlocks[1]->rect.width,
        CodeBlocks[0]->rect.y);
    for (int i = 2; i < CodeBlocks.size(); i++) {
        // update the group Head Buttons
        Button* curHead = CodeBlocks[i];
        Button* prevHead = CodeBlocks[i - 1];
        curHead->setPosition(
			prevHead->rect.x,
			prevHead->rect.y + prevHead->rect.height
        );
    }
}

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
    if (button->rect.width <= prev->rect.width) {
        button->rect.width = prev->rect.width;
    }
    else {
        for (int i = 0; i < Buttons.size() - 1; i++) {
            Buttons[i]->rect.width = button->rect.width;
        }
    }
    button->rect.x = prev->rect.x;
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

void Button::insertCodeBlock(vector<Button*>& CodeBlocks, Button* codeblock) {
    if (CodeBlocks.empty()) {
        CodeBlocks.push_back(codeblock);
        return;
    }

    if (CodeBlocks.size() == 1) {
        CodeBlocks.push_back(codeblock);
        codeblock->head = CodeBlocks[0];
		codeblock->rect.x = CodeBlocks[0]->rect.x - codeblock->rect.width;
        codeblock->rect.y = CodeBlocks[0]->rect.y;;
        return;
    }
    
    Button* prev = CodeBlocks.back();
    CodeBlocks.push_back(codeblock);
	if (codeblock->rect.width <= prev->rect.width) {
		codeblock->rect.width = prev->rect.width;
		codeblock->rect.x = prev->rect.x;
	}
	else {
		for (int i = 1; i < CodeBlocks.size(); i++) {
			CodeBlocks[i]->rect.width = codeblock->rect.width;
            CodeBlocks[i]->rect.x = CodeBlocks[0]->rect.x - codeblock->rect.width;
		}
	}
    codeblock->head = CodeBlocks[0];
    codeblock->rect.y = prev->rect.y + prev->rect.height;
	CodeBlocks[0]->rect.height += codeblock->rect.height;
}

void Button::insertPseudoCode(vector<Button*>& CodeBlocks, string pseudocode) {
    std::stringstream ss(pseudocode);
    std::string line;

    while (std::getline(ss, line, '\n')) {
        insertCodeBlock(CodeBlocks, new CodeBlock(line.c_str()));
    }
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

        //Vector2 tsize = MeasureTextEx(UI::font, Text.c_str(), UI::fontSize, UI::spacing);
        DrawTextEx(UI::font, Text.c_str(), { rect.x + padding/2, rect.y + rect.height /2 - padding/2}, UI::fontSize, UI::spacing, TextColor);
    }
    if (next) {
        next->draw();
    }
}
