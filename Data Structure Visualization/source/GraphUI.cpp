#include "../header/GraphUI.h"
void GraphUI::init() {
	buttonsOnGraph.push_back(new TextBox("Menu", 50, 50));
	
}
void GraphUI::displayScene() {
	for (auto button : buttonsOnGraph) {
		button->draw();
	}
}
void GraphUI::updateScene() {
	Button::isCollision = false;
	for (auto button : buttonsOnGraph) {
		button->update();
	}
	if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}