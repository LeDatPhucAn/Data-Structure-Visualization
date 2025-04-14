#include "../header/GraphUI.h"

void GraphUI::init() {
	//buttonsOnGraph.push_back(new TextBox("Menu", 50, 50));
	initButtons();
}
void GraphUI::displayScene() {
	Button::drawButtons<RectButton>(buttonsOnGraph);


}
void GraphUI::updateScene() {
	Button::updateButtons<RectButton>(buttonsOnGraph);
	if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}
void GraphUI::initButtons() {
	RectButton::insertHeadButton(buttonsOnGraph,
		new TextBox("Add Node", 100, UI::screenHeight * 6 / 10));
	RectButton* posX = new TextBox("PosX:");
	RectButton* posXInput = new NumberInputBox(4);
	RectButton* posY = new TextBox("PosY:");
	RectButton* posYInput = new NumberInputBox(4);
	RectButton* Enter = new TextBox(">");

	buttonsOnGraph[0]->insertSubButton(posX);
	buttonsOnGraph[0]->insertSubButton(posXInput);
	buttonsOnGraph[0]->insertSubButton(posY);
	buttonsOnGraph[0]->insertSubButton(posYInput);
	buttonsOnGraph[0]->insertSubButton(Enter, [this, posXInput, posYInput]() {
		graph->addNode(Vector2(posXInput->getNumber(), posYInput->getNumber()));
		static_cast<NumberInputBox*>(posXInput)->clear();
		static_cast<NumberInputBox*>(posYInput)->clear();
		});

	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("Remove Node"));
	RectButton* id = new TextBox("ID:");
	RectButton* idInput = new NumberInputBox(3);
	RectButton* enter1 = new TextBox(">");

	buttonsOnGraph[1]->insertSubButton(id);
	buttonsOnGraph[1]->insertSubButton(idInput);
	buttonsOnGraph[1]->insertSubButton(enter1, [this, idInput]() {
		graph->removeNode(idInput->getNumber());
		static_cast<NumberInputBox*>(idInput)->clear();
		});

	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("Add Edge"));
	RectButton* id1 = new TextBox("ID1:");
	RectButton* id1Input = new NumberInputBox(3);
	RectButton* id2 = new TextBox("ID2:");
	RectButton* id2Input = new NumberInputBox(3);
	RectButton* weight = new TextBox("Weight");
	RectButton* wInput = new NumberInputBox(3);
	RectButton* enter2 = new TextBox(">");

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

	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("Remove Edge"));
	RectButton* id3 = new TextBox("ID1:");
	RectButton* id3Input = new NumberInputBox(3);
	RectButton* id4 = new TextBox("ID2:");
	RectButton* id4Input = new NumberInputBox(3);
	RectButton* enter3 = new TextBox(">");

	buttonsOnGraph[3]->insertSubButton(id3);
	buttonsOnGraph[3]->insertSubButton(id3Input);
	buttonsOnGraph[3]->insertSubButton(id4);
	buttonsOnGraph[3]->insertSubButton(id4Input);
	buttonsOnGraph[3]->insertSubButton(enter3, [this, id3Input, id4Input]() {
		graph->removeEdge(id3Input->getNumber(), id4Input->getNumber());
		static_cast<NumberInputBox*>(id3Input)->clear();
		static_cast<NumberInputBox*>(id3Input)->clear();
		});
	RectButton::insertHeadButton(buttonsOnGraph, new TextBox(" Clear "));
	buttonsOnGraph[4]->onClick = [this]() {
		this->clear();
		};
	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("Hidden"));
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

