#include "../header/Edge.h"
#include "../header/UI.h"
void Edge::drawEdge() {
	if (!from) {
		cout << "u done fucked up";
		return;
	}
	float fromX = from->position.x + from->radius;
	float fromY = from->position.y;
	if (!to) {
		DrawLineEx({fromX,fromY}, {fromX + 100,fromY}, thickness, BLACK);
		string message = "NULL";
		UI::drawtext2(message, fromX + 150, fromY, BLUE);
		return;
	}
	float toX = to->position.x - to->radius;
	float toY = to->position.y;
	DrawLineEx({fromX,fromY}, {toX,toY}, thickness, BLACK);
}

void Edge::addEdge(vector<Edge*>& Edges, Node* from, Node* to) {
	Edges.push_back(new Edge(from, to));
}
void Edge::removeEdge(vector<Edge*>& Edges, Node* from, Node* to) {
	for (int i = 0; i < Edges.size(); i++) {
		if (Edges[i]->from == from && Edges[i]->to == to) {
			Edges.erase(Edges.begin() + i);
			return;
		}
	}
}