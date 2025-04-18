#include "../header/GraphUI.h"
#include "../header/Animation.h"
#include "../header/PseudoCode.h"
#include "../header/Graph.h"
void GraphUI::init() {
	//buttonsOnGraph.push_back(new TextBox("Menu", 50, 50));
	initButtons();
}
void GraphUI::Dijkstra(int n) {
	animManager.clear();
	graph->DijkstraAnim(CodeBlocks, animManager, n);
}
void GraphUI::displayScene() {
	Button::drawButtons<RectButton>(buttonsOnGraph);
	Button::drawButtons<RectButton>(CodeBlocks);
	
	graph->drawDijkstraTable();

}
void GraphUI::updateScene() {
	Button::updateButtons<RectButton>(buttonsOnGraph);
	Button::updateButtons<RectButton>(CodeBlocks);
	if (!Button::isCollision) SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}
void GraphUI::resetAnimations() {
	Button::resetButtonsAnimations<RectButton>(buttonsOnGraph);
	Button::resetButtonsAnimations<RectButton>(CodeBlocks);
}
void GraphUI::initButtons() {
	//CodeBlocks
	RectButton* OpenCodeBlocks = new TextBox("<");
	OpenCodeBlocks->rect.x = UI::screenWidth - OpenCodeBlocks->rect.width;
	OpenCodeBlocks->rect.y = UI::screenHeight / 4;
	OpenCodeBlocks->rect.height = 0;
	OpenCodeBlocks->isActivated = true;
	RectButton::insertCodeBlock(CodeBlocks, OpenCodeBlocks);

	//Buttons
	RectButton::insertHeadButton(buttonsOnGraph,
		new TextBox("INIT GRAPH", 100, UI::screenHeight * 6 / 10));
	buttonsOnGraph[0]->animation = new RectMoveXAnim(buttonsOnGraph[0], 0.5f);
	RectButton* vertice = new TextBox("Input n:");
	RectButton* verticeInput = new NumberInputBox(4);
	RectButton* Enter = new TextBox(">");

	buttonsOnGraph[0]->insertSubButton(vertice);
	buttonsOnGraph[0]->insertSubButton(verticeInput);
	
	buttonsOnGraph[0]->insertSubButton(Enter, [this, verticeInput]() {
		graph->initGraph(verticeInput->getNumber());
		RectButton::insertPseudoCode(CodeBlocks, PseudoCode::GraphAddNode);
		static_cast<NumberInputBox*>(verticeInput)->clear();
		});

	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("LOAD FILE"));
	buttonsOnGraph[1]->animation = new RectMoveXAnim(buttonsOnGraph[1], 0.5f);
	buttonsOnGraph[1]->onClick = [this]() {
		graph->loadFromFile();
		RectButton::insertPseudoCode(CodeBlocks, PseudoCode::GraphAddNode);
		};
	

	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("DIJKSTRA"));
	buttonsOnGraph[2]->animation = new RectMoveXAnim(buttonsOnGraph[2], 0.5f);

	RectButton* vertice2 = new TextBox("Input n:");
	RectButton* verticeInput2 = new NumberInputBox(4);
	RectButton* Enter2 = new TextBox(">");

	buttonsOnGraph[2]->insertSubButton(vertice2);
	buttonsOnGraph[2]->insertSubButton(verticeInput2);
	buttonsOnGraph[2]->insertSubButton(Enter2, [this, verticeInput2]() {
		graph->drawDijkstra();
		Dijkstra(verticeInput2->getNumber());
		
		RectButton::insertPseudoCode(CodeBlocks, PseudoCode::GraphAddNode);
		static_cast<NumberInputBox*>(verticeInput2)->clear();
		});

	

	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("Remove Edge"));
	buttonsOnGraph[3]->animation = new RectMoveXAnim(buttonsOnGraph[3], 0.5f);
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
		RectButton::insertPseudoCode(CodeBlocks, PseudoCode::GraphRemoveEdge);
		static_cast<NumberInputBox*>(id3Input)->clear();
		static_cast<NumberInputBox*>(id3Input)->clear();
		});
	RectButton::insertHeadButton(buttonsOnGraph, new TextBox(" Clear "));
	buttonsOnGraph[4]->animation = new RectMoveXAnim(buttonsOnGraph[4], 0.5f);
	buttonsOnGraph[4]->onClick = [this]() {
		this->clear();
		};
	RectButton::insertHeadButton(buttonsOnGraph, new TextBox("Hidden"));
	buttonsOnGraph[5]->animation = new RectMoveXAnim(buttonsOnGraph[5], 0.5f);
	buttonsOnGraph[5]->onClick = [this]() {
		this->setHidden();
		};
	updateButtonPositions();
}
void GraphUI::drawGraph() {
	Graph* g = this->graph;
	for (GraphNode*& vertice : g->ListNodeOnGraph()) {
		vertice->draw();
	}
	for (EdgeOfGraph*& edge : g->ListEdgeOnGraph()) {
		edge->drawEdge();
	}

}

void GraphUI::displaySceneInCamera() {
	if (!hidden) drawGraph();
	//graph->drawDijkstraTable();
}
void GraphUI::updateButtonPositions() {

	RectButton::setHeadPosition(buttonsOnGraph, 100, UI::screenHeight * 3 / 5);
	RectButton::setCodeBlockPosition(CodeBlocks, UI::screenWidth - CodeBlocks[0]->rect.width, UI::screenHeight / 4);
}

void GraphUI::clear() {
	graph->clear();
}
void GraphUI::setHidden() {
	if (hidden) hidden = false;
	else hidden = true;
}

