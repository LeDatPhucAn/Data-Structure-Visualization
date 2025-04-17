#include "../header/HashTableUI.h"
#include "../header/PseudoCode.h"
#include "../header/Animation.h"
#include <iostream>

void HashTableUI::drawHashTable() {
    for (int i = 0; i < hashtable.bucketCount; i++) {
        Rectangle bucketRect = { 250 + i * 200 - 50, 100, 100, 50 };
        DrawRectangleRec(bucketRect, LIGHTGRAY);
        DrawRectangleLines(bucketRect.x, bucketRect.y, bucketRect.width, bucketRect.height, DARKGRAY);
        UI::drawtext2(std::to_string(i), bucketRect.x + bucketRect.width / 2, bucketRect.y + bucketRect.height / 2, BLACK);

        LLNode* cur = hashtable.buckets[i];
        while (cur) {
            cur->draw();
            cur = cur->next;
        }
    }
    for (auto& edge : hashtable.Edges) {
        edge->drawArrowEdge();
    }
}

void HashTableUI::insert(int x) {
    animManager.clear();
    isInsert = true;
    isRemove = false;
    int pos = -1;
    hashtable.insertNode(CodeBlocks, animManager, x, pos);
    insertParameters = { x, pos };
}

void HashTableUI::remove(int x) {
    animManager.clear();
    isRemove = true;
    isInsert = false;
    int pos = -1;
    bool success = hashtable.remove(CodeBlocks, animManager, x, pos);
    removeParameters = { x, pos };
}

bool HashTableUI::search(int x) {
    animManager.clear();
    isInsert = false;
    isRemove = false;
    return hashtable.search(CodeBlocks, animManager, x);
}

void HashTableUI::resize(int newSize) {
    hashtable.resize(newSize);
}

void HashTableUI::loadFromFile() {
    hashtable.loadFromFile(CodeBlocks, animManager);
}

void HashTableUI::init() {
    srand(time(nullptr));
    int n = rand() % 10;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        hashtable.randomInsert(x);
    }
    initButtons();
}

void HashTableUI::initButtons() {
    RectButton* OpenCodeBlocks = new TextBox("<");
    OpenCodeBlocks->rect.x = UI::screenWidth - OpenCodeBlocks->rect.width;
    OpenCodeBlocks->rect.y = UI::screenHeight / 4;
    OpenCodeBlocks->rect.height = 0;
    OpenCodeBlocks->isActivated = true;
    RectButton::insertCodeBlock(CodeBlocks, OpenCodeBlocks);

    RectButton::insertHeadButton(Buttons, new TextBox("Insert", 100, UI::screenHeight * 3 / 5));
    Buttons[0]->animation = new RectMoveXAnim(Buttons[0], 0.5);
    RectButton* Value = new TextBox("Value:");
    RectButton* ValueInput = new NumberInputBox(3);
    RectButton* Enter = new TextBox(">");
    Buttons[0]->insertSubButton(Value);
    Buttons[0]->insertSubButton(ValueInput);
    Buttons[0]->insertSubButton(Enter, [this, ValueInput]() {
        insert(ValueInput->getNumber());
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableInsert);
        static_cast<NumberInputBox*>(ValueInput)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Remove"));
    Buttons[1]->animation = new RectMoveXAnim(Buttons[1], 0.5);
    RectButton* Value1 = new TextBox("Value:");
    RectButton* ValueInput1 = new NumberInputBox(3);
    RectButton* Enter1 = new TextBox(">");
    Buttons[1]->insertSubButton(Value1);
    Buttons[1]->insertSubButton(ValueInput1);
    Buttons[1]->insertSubButton(Enter1, [this, ValueInput1]() {
        remove(ValueInput1->getNumber());
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableRemove);
        static_cast<NumberInputBox*>(ValueInput1)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Search"));
    Buttons[2]->animation = new RectMoveXAnim(Buttons[2], 0.5);
    RectButton* Value2 = new TextBox("Value:");
    RectButton* ValueInput2 = new NumberInputBox(3);
    Buttons[2]->insertSubButton(Value2);
    Buttons[2]->insertSubButton(ValueInput2);
    Buttons[2]->insertSubButton(new TextBox(">"), [this, ValueInput2]() {
        if (!search(ValueInput2->getNumber())) {
            std::cout << "NOT FOUND\n";
        }
        RectButton::insertPseudoCode(CodeBlocks, PseudoCode::HashTableSearch);
        static_cast<NumberInputBox*>(ValueInput2)->clear();
        });

    RectButton::insertHeadButton(Buttons, new TextBox("Clear"));
    Buttons[3]->animation = new RectMoveXAnim(Buttons[3], 0.5);
    Buttons[3]->onClick = [this]() {
        animManager.clear();
        hashtable.clear();
        };

    RectButton::insertHeadButton(Buttons, new TextBox("Random"));
    Buttons[4]->animation = new RectMoveXAnim(Buttons[4], 0.5);
    Buttons[4]->onClick = [this]() {
        animManager.clear();
        hashtable.clear();
        int n = rand() % 10;
        for (int i = 0; i < n; ++i) {
            int x = rand() % 100;
            hashtable.randomInsert(x);
        }
        };

    RectButton::insertHeadButton(Buttons, new TextBox("LoadFile"));
    Buttons[5]->animation = new RectMoveXAnim(Buttons[5], 0.5);
    Buttons[5]->onClick = [this]() {
        loadFromFile();
        };

    RectButton::insertHeadButton(Buttons, new TextBox("Bucket"));
    Buttons[6]->animation = new RectMoveXAnim(Buttons[6], 0.5);
    RectButton* BucketInput = new NumberInputBox(2);
    Buttons[6]->insertSubButton(new TextBox("Size:"));
    Buttons[6]->insertSubButton(BucketInput);
    Buttons[6]->insertSubButton(new TextBox(">"), [this, BucketInput]() {
        int newSize = BucketInput->getNumber();
        if (newSize > 0) {
            resize(newSize);
        }
        static_cast<NumberInputBox*>(BucketInput)->clear();
        });

    updateButtonPositions();
}

void HashTableUI::resetAnimations() {
    Button::resetButtonsAnimations<RectButton>(Buttons);
    Button::resetButtonsAnimations<RectButton>(CodeBlocks);
}

void HashTableUI::updateButtonPositions() {
    RectButton::setHeadPosition(Buttons, 100, UI::screenHeight * 3 / 5);
    RectButton::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);
}

void HashTableUI::displaySceneInCamera() {
    drawHashTable();
}

void HashTableUI::displayScene() {
    Button::drawButtons<RectButton>(Buttons);
    Button::drawButtons<RectButton>(CodeBlocks);
    // Vẽ NumberInputBox và nút xác nhận nếu đang chỉnh sửa
    if (editValueInput) {
        editValueInput->draw();
    }
    if (editValueConfirm) {
        editValueConfirm->draw();
    }
}

void HashTableUI::updateScene() {
    bool needUpdateHashTable = false;
    int newValue = 0;
    int oldValue = 0;
    int bucketIdx = -1;

    for (int i = 0; i < hashtable.bucketCount; i++) {
        LLNode* cur = hashtable.buckets[i];
        while (cur) {
            cur->update();
            if (cur->animation) cur->animation->update(GetFrameTime());

            // Khi click vào node, hiển thị NumberInputBox
            if (!isEditingNode && cur->checkCollision() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                selectedNode = cur;
                selectedBucketIdx = i;
                isEditingNode = true;

                // Tạo NumberInputBox gần node
                editValueInput = new NumberInputBox(3);
                editValueInput->rect.x = cur->getCenterX() + 50;
                editValueInput->rect.y = cur->getCenterY() - 20;
                static_cast<NumberInputBox*>(editValueInput)->setNumber(cur->getNumber()); // Ép kiểu để gọi setNumber

                // Tạo nút xác nhận
                editValueConfirm = new TextBox(">");
                editValueConfirm->rect.x = editValueInput->rect.x + editValueInput->rect.width + 10;
                editValueConfirm->rect.y = editValueInput->rect.y;
                editValueConfirm->onClick = [this, cur, i, &needUpdateHashTable, &newValue, &oldValue, &bucketIdx]() {
                    newValue = static_cast<NumberInputBox*>(editValueInput)->getNumber();
                    oldValue = cur->getNumber();
                    bucketIdx = i;
                    needUpdateHashTable = true; // Đánh dấu cần cập nhật hash table
                    isEditingNode = false; // Kết thúc trạng thái chỉnh sửa
                    };
            }
            cur = cur->next;
        }
    }

    // Cập nhật NumberInputBox và nút xác nhận
    if (editValueInput) {
        editValueInput->update();
    }
    if (editValueConfirm) {
        editValueConfirm->update();
    }

    // Xử lý cập nhật hash table sau khi vòng lặp duyệt node hoàn tất
    if (needUpdateHashTable && newValue != oldValue) {
        hashtable.removeFromBucket(oldValue, bucketIdx);
        vector<int> values = hashtable.collectValues();
        values.push_back(newValue);
        hashtable.clear();
        for (int val : values) {
            hashtable.randomInsert(val);
        }
    }

    // Xóa editValueInput và editValueConfirm nếu không còn chỉnh sửa
    if (!isEditingNode && editValueInput) {
        delete editValueInput;
        editValueInput = nullptr;
    }
    if (!isEditingNode && editValueConfirm) {
        delete editValueConfirm;
        editValueConfirm = nullptr;
    }

    Button::updateButtons<RectButton>(Buttons);
    Button::updateButtons<RectButton>(CodeBlocks);
    if (!Button::isCollision && !isEditingNode) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void HashTableUI::updateSceneInCamera(Camera2D cam) {}

void HashTableUI::clearIndicatesAndHighlights() {
    hashtable.clearIndicates();
    for (int i = 1; i < CodeBlocks.size(); i++) {
        CodeBlocks[i]->unhighlight();
    }
}

void HashTableUI::replayOperation() {
    if (isInsert) {
        animManager.clear();
        hashtable.restoreAfterInsert(insertParameters.first, insertParameters.second);
        int pos = -1;
        hashtable.insertNode(CodeBlocks, animManager, insertParameters.first, pos);
    }
    else if (isRemove && removeParameters.second != -1) {
        animManager.clear();
        hashtable.randomInsert(removeParameters.first);
        int pos = -1;
        hashtable.remove(CodeBlocks, animManager, removeParameters.first, pos);
    }
}
