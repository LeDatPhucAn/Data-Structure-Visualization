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
		new TextBox("Add Node", 100, UI::screenHeight * 6 / 10));
	Button* posX = new TextBox("PosX:");
	Button* posXInput = new NumberInputBox(4);
	Button* posY = new TextBox("PosY:");
	Button* posYInput = new NumberInputBox(4);
	Button* Enter = new TextBox(">");

	buttonsOnGraph[0]->insertSubButton(posX);
	buttonsOnGraph[0]->insertSubButton(posXInput);
	buttonsOnGraph[0]->insertSubButton(posY);
	buttonsOnGraph[0]->insertSubButton(posYInput);
	buttonsOnGraph[0]->insertSubButton(Enter, [this, posXInput, posYInput]() {
		graph->addNode(Vector2(posXInput->getNumber(), posYInput->getNumber()));
		static_cast<NumberInputBox*>(posXInput)->clear();
		static_cast<NumberInputBox*>(posYInput)->clear();
		});

	Button::insertHeadButton(buttonsOnGraph, new TextBox("Remove Node"));
	Button* id = new TextBox("ID:");
	Button* idInput = new NumberInputBox(3);
	Button* enter1 = new TextBox(">");

	buttonsOnGraph[1]->insertSubButton(id);
	buttonsOnGraph[1]->insertSubButton(idInput);
	buttonsOnGraph[1]->insertSubButton(enter1, [this, idInput]() {
		graph->removeNode(idInput->getNumber());
		static_cast<NumberInputBox*>(idInput)->clear();
		});

	Button::insertHeadButton(buttonsOnGraph, new TextBox("Add Edge"));
	Button* id1 = new TextBox("ID1:");
	Button* id1Input = new NumberInputBox(3);
	Button* id2 = new TextBox("ID2:");
	Button* id2Input = new NumberInputBox(3);
	Button* weight = new TextBox("Weight");
	Button* wInput = new NumberInputBox(3);
	Button* enter2 = new TextBox(">");

	buttonsOnGraph[2]->insertSubButton(id1);
	buttonsOnGraph[2]->insertSubButton(id1Input);
	buttonsOnGraph[2]->insertSubButton(id2);
	buttonsOnGraph[2]->insertSubButton(id2Input);
	buttonsOnGraph[2]->insertSubButton(weight);
	buttonsOnGraph[2]->insertSubButton(wInput);
	buttonsOnGraph[2]->insertSubButton(enter2, [this, id1Input, id2Input, wInput]() {
		graph->addEdge(id1Input->getNumber(), id2Input->getNumber(),
		(float)wInput->getNumber());
	static_cast<NumberInputBox*>(id1Input)->clear();
	static_cast<NumberInputBox*>(id2Input)->clear();
	static_cast<NumberInputBox*>(wInput)->clear();
		});

	Button::insertHeadButton(buttonsOnGraph, new TextBox("Remove Edge"));
	Button* id3 = new TextBox("ID1:");
	Button* id3Input = new NumberInputBox(3);
	Button* id4 = new TextBox("ID2:");
	Button* id4Input = new NumberInputBox(3);
	Button* enter3 = new TextBox(">");

	buttonsOnGraph[3]->insertSubButton(id3);
	buttonsOnGraph[3]->insertSubButton(id3Input);
	buttonsOnGraph[3]->insertSubButton(id4);
	buttonsOnGraph[3]->insertSubButton(id4Input);
	buttonsOnGraph[3]->insertSubButton(enter3, [this, id3Input, id4Input]() {
		graph->removeEdge(id3Input->getNumber(), id4Input->getNumber());
		static_cast<NumberInputBox*>(id3Input)->clear();
		static_cast<NumberInputBox*>(id3Input)->clear();
		});
	Button::insertHeadButton(buttonsOnGraph, new TextBox(" Clear "));
	buttonsOnGraph[4]->onClick = [this]() {
		this->clear();
		};
	Button::insertHeadButton(buttonsOnGraph, new TextBox("Hidden"));
	buttonsOnGraph[5]->onClick = [this]() {
		this->setHidden();
		};

}
void GraphUI::drawGraph() {
	Graph* g = this->graph;
	for (Node*& vertice : g->ListNodeOnGraph()) {
		UI::drawNode(vertice);
	}
	for (EdgeOfGraph*& edge : g->ListEdgeOnGraph()) {
		edge->drawEdgeOfGraph();
	}

}

void GraphUI::displaySceneInCamera() {
	if (!hidden) drawGraph();
	
}
void GraphUI::clear() {
	graph->clear();
}
void GraphUI::setHidden() {
	if (hidden) hidden = false;
	else hidden = true;
}