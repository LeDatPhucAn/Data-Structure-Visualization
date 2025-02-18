#pragma once
#include "UI.h"
#include "SinglyLinkedList.h"
class SinglyLinkedListUI : public UI {
private:
	static constexpr int headX = 200;
	static constexpr int headY = 350;
	static constexpr int radius = 50;
public:
	void drawlinkedlist();
};