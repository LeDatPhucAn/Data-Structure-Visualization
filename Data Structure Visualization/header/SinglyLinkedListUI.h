#pragma once
#include "UI.h"
#include "SinglyLinkedList.h"
#include "SceneManager.h"
class SinglyLinkedListUI : public UI, public LinkedList, public SceneManager {
private:
    static constexpr int headX = 100;
    static constexpr int headY = 450;
    static constexpr int radius = 50;
public:
    SinglyLinkedListUI() {
        init();
    }
    void init();
    void drawlinkedlist();
    void displayScene() override;
    void updateScene() override;
};


