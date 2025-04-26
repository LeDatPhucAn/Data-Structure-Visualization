#include "../header/GraphUI.h"
#include "../header/Animation.h"
#include "../header/PseudoCode.h"
#include "../header/Graph.h"

bool GraphUI::isDijkstra = false;
bool GraphUI::isDijkstraTable = false;

void GraphUI::init() {
	//buttonsOnGraph.push_back(new TextBox("Menu", 50, 50));
	initButtons();
}
void GraphUI::Dijkstra(int n) {
	cleanUpForOperation();
	isDijkstra = true;
	isDijkstraTable = false;
	dijkstraParameters = n;
	graph->DijkstraAnim(CodeBlocks, animManager, n);
}
void GraphUI::DijkstraTable() {
	cleanUpForOperation();
	isDijkstra = false;
	isDijkstraTable = true;

	tableDijkParameters = graph->getCurrentStep();
	graph->drawDijkstraTable(tableDijkParameters);
}
void GraphUI::replayOperation() {
	if (isDijkstra) {
		animManager.goToLastStep();
		animManager.clear();
		graph->DijkstraAnim(CodeBlocks, animManager, dijkstraParameters);
	}
	//else if (isDijkstraTable) {
	//	animManager.goToLastStep();
	//	animManager.clear();
	//	graph->setCurrentStep();
	//	graph->drawDijkstraTable(graph->getCurrentStep());
	//}
}
void GraphUI::displayScene() {
	Button::drawButtons<RectButton>(buttonsOnGraph);
	Button::drawButtons<RectButton>(CodeBlocks);
	
	//cout << graph->getCurrentStep() << "\n";
	graph->drawDijkstraTable(graph->getCurrentStep());

}
void GraphUI::updateScene() {
	Button::updateButtons<RectButton>(buttonsOnGraph);
	Button::updateButtons<RectButton>(CodeBlocks);
	Graph* g = this->graph;
	for (GraphNode*& vertice : g->ListNodeOnGraph()) {
		vertice->update();
		if (vertice->animation) vertice->animation->update(GetFrameTime());
	}
	
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
		if (graph->numberOfVertices() > 0) {

			graph->drawDijkstra();
			Dijkstra(verticeInput2->getNumber());

			RectButton::insertPseudoCode(CodeBlocks, PseudoCode::GraphDijkstra);
			static_cast<NumberInputBox*>(verticeInput2)->clear();
		}
		});

	


	RectButton::insertHeadButton(buttonsOnGraph, new TextBox(" Clear "));
	buttonsOnGraph[3]->animation = new RectMoveXAnim(buttonsOnGraph[3], 0.5f);
	buttonsOnGraph[3]->onClick = [this]() {
		this->clear();
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
	//if (!hidden) drawGraph();
	drawGraph();
	
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

