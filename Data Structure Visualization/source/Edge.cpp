#include "../header/Edge.h"
#include "../header/UI.h"

void Edge::drawEdge() {
	if (!from) {
		cout << "u done fucked up";
		return;
	}
	
	if (!to) {
		return;
	}
	float theta = atan2(to->position.y - from->position.y, to->position.x - from->position.x);

	float fromX = from->radius * cos(theta) + from->position.x;
	float fromY = from->radius * sin(theta) + from->position.y;
	float toX = -to->radius * cos(theta) + to->position.x;
	float toY = to->radius * sin(theta) + to->position.y;
	DrawLineEx({fromX,fromY}, {toX,toY}, thickness, BLACK);
}
//---------------------------------------------------------------------
// Helper: Draw Edge With arrow
// Description: this Function draws an edge with an arrow head to any position
//---------------------------------------------------------------------
void Edge::drawArrowEdge()
{
	if (!from || !to) return;
	float dx = to->position.x - from->position.x;
	float dy = to->position.y - from->position.y;

	float arrowHeadAngle = PI / 6;
	float arrowHeadLength = sqrt(dx * dx + dy * dy) / 10;

	float theta = atan2(dy, dx);

	float fromX = from->radius * cos(theta) + from->position.x;
	float fromY = from->radius * sin(theta) + from->position.y;
	float toX = -to->radius * cos(theta) + to->position.x;
	float toY = to->radius * sin(theta) + to->position.y;

	//draw edge
	
	DrawLineEx({ fromX,fromY }, { toX - arrowHeadLength*sin(arrowHeadAngle),toY}, thickness, BLACK);

	//draw arrow head

	float theta1 = theta + arrowHeadAngle;
	float theta2 = theta - arrowHeadAngle;

	Vector2 arrowPoint1 = { toX - arrowHeadLength * cos(theta1), toY - arrowHeadLength * sin(theta1) };
	Vector2 arrowPoint2 = { toX - arrowHeadLength * cos(theta2), toY - arrowHeadLength * sin(theta2) };

	DrawTriangle({toX,toY}, arrowPoint1, arrowPoint2, BLACK);
}

void Edge::drawTreapEdge() {
	if (!from || !to) return;

	static const float nodeWidth = 120.0f;
	static const float nodeHeight = 100.0f;

	Vector2 start = from->position;
	Vector2 end = to->position;

	if (start.x > end.x) start.x -= nodeWidth / 4;  // Left child
	else start.x += nodeWidth / 4;  // Right child

	start.y += nodeHeight / 2 - 2;
	end.y -= nodeHeight / 2 - 2;

	DrawLineEx(start, end, thickness, BLACK);
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