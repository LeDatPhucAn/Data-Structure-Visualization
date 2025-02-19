#pragma once
#include "UI.h"
#include "SinglyLinkedList.h"
class SinglyLinkedListUI : public UI {
private:
	static constexpr int headX = 100;
	static constexpr int headY = 450;
	static constexpr int radius = 50;
public:
	void drawlinkedlist();
};