#include "../header/Edge.h"
#include "../header/UI.h"

void Edge::drawEdge() {
	if (!from) {
		cout << "u done fucked up";
		return;
	}
	
	if (!to) {
		/*float fromX = from->position.x + from->radius;
		float fromY = from->position.y;
		DrawLineEx({fromX,fromY}, {fromX + 100,fromY}, thickness, BLACK);
		string message = "NULL";
		UI::drawtext2(message, fromX + 150, fromY, BLUE);*/
		return;
	}
	float theta = atan2(to->position.y - from->position.y, to->position.x - from->position.x);

	float fromX = from->radius * cos(theta) + from->position.x;
	float fromY = from->radius * sin(theta) + from->position.y;
	float toX = -to->radius * cos(theta) + to->position.x;
	float toY = to->radius * sin(theta) + to->position.y;
	DrawLineEx({fromX,fromY}, {toX,toY}, thickness, BLACK);
}
void Edge::drawTreapEdge() {
	if (!from || !to) return;  

	static const float nodeWidth = 60.0f;
	static const float nodeHeight = 30.0f;
	float lineThickness = max(nodeWidth / 20, 2.0f);

	Vector2 start = from->position;
	Vector2 end = to->position;

	if (start.x > end.x) start.x -= nodeWidth / 4;  // Left child
	else start.x += nodeWidth / 4;  // Right child

	start.y += nodeHeight / 2 - 2;
	end.y -= nodeHeight / 2 - 2;

	DrawLineEx(start, end, lineThickness, BLACK);
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