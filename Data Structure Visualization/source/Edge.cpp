#include "../header/Edge.h"
#include "../header/UI.h"
void Edge::drawEdge() {
	int fromX = from->position.x + from->radius;
	int fromY = from->position.y;
	if (!to) {
		DrawLineEx({static_cast<float>(fromX),static_cast<float>(fromY)}, {static_cast<float>(fromX) + 100, static_cast<float>(fromY)}, static_cast<float>(thickness), BLACK);
		string message = "NULL";
		UI::drawtext2(message, fromX + 150, fromY, BLUE);
		return;
	}
	float toX = to->position.x - to->radius;
	float toY = to->position.y;
	DrawLineEx({static_cast<float>(fromX), static_cast<float>(fromY)}, {toX,toY}, thickness, BLACK);
}

void Edge::drawTreapEdge(){
	if (!from || !to) return;  // ✅ Safety check

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