#include "../header/GraphUI.h"

void GraphUI::init() {
	//buttonsOnGraph.push_back(new TextBox("Menu", 50, 50));
	initButtons();
}
void GraphUI::displayScene() {
	SceneHandler::MenuButton->draw();
	Button::drawButtons(buttonsOnGraph);


}
void GraphUI::updateScene() {
	Button::isCollision = false;
	SceneHandler::MenuButton->update();
	Button::updateButtons(buttonsOnGraph);
	if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}
void GraphUI::initButtons() {
	Button::insertHeadButton(buttonsOnGraph, 
		new TextBox("Add Node", 100, UI::screenHeight * 3 / 4));
	//buttonsOnGraph[0]->onClick = [this]
}
void GraphUI::drawGraph() {

}
void GraphUI::displaySceneInCamera() {
	drawGraph();
}