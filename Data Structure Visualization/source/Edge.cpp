#include "../header/Edge.h"
#include "../header/UI.h"
#include "../header/Treap.h"

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
	float toY = -to->radius * sin(theta) + to->position.y;
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
	float arrowHeadLength = thickness*5;

	float theta = atan2(dy, dx);

	float fromX = from->radius * cos(theta) + from->position.x;
	float fromY = from->radius * sin(theta) + from->position.y;
	float toX =  to->position.x - to->radius * cos(theta);
	float toY =  to->position.y - to->radius * sin(theta);

	float EdgeEndX = toX - arrowHeadLength * cos(theta) * sqrt(3) / 2;
	float EdgeEndY = toY - arrowHeadLength * sin(theta) * sqrt(3) / 2;
	//draw edge
	
	DrawLineEx({ fromX,fromY }, { EdgeEndX, EdgeEndY }, thickness, BLACK);

	//draw arrow head

	float theta1 = theta + arrowHeadAngle;
	float theta2 = theta - arrowHeadAngle;

	Vector2 arrowPoint1 = { toX - arrowHeadLength * cos(theta1), toY - arrowHeadLength * sin(theta1) };
	Vector2 arrowPoint2 = { toX - arrowHeadLength * cos(theta2), toY - arrowHeadLength * sin(theta2) };

	DrawTriangle({toX,toY}, arrowPoint1, arrowPoint2, BLACK);
}
void Edge::drawTreapEdge() {
	if (!from || !to) return;

	TreapNode* fromNode = dynamic_cast<TreapNode*>(from);
	TreapNode* toNode = dynamic_cast<TreapNode*>(to);
	if (!fromNode || !toNode) return;

	Rectangle fromRect = fromNode->rect;
	Rectangle toRect = toNode->rect;

	// Use the actual center of each box
	Vector2 start = {
		fromRect.x + fromRect.width / 2,
		fromRect.y + fromRect.height       // bottom center of parent
	};
	Vector2 end = {
		toRect.x + toRect.width / 2,
		toRect.y                           // top center of child
	};

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
#include "../header/Button.h"
void CBEdge::drawArrowEdge()
{
	if (!from || !to) return;
	float dx = to->getCenterX() - from->getCenterX();
	float dy = to->getCenterY() - from->getCenterY();
	float arrowHeadAngle = PI / 6;
	float arrowHeadLength = thickness*5;

	float theta = atan2(dy, dx);

	float fromX = from->getRadius() * cos(theta) + from->getCenterX();
	float fromY = from->getRadius() * sin(theta) + from->getCenterY();
	float toX =  to->getCenterX() - to->getRadius() * cos(theta);
	float toY =  to->getCenterY() - to->getRadius() * sin(theta);

	float EdgeEndX = toX - arrowHeadLength * cos(theta) * sqrt(3)/2;
	float EdgeEndY = toY - arrowHeadLength * sin(theta) * sqrt(3)/2;
	//draw edge
	
	DrawLineEx({ fromX,fromY }, { EdgeEndX, EdgeEndY }, thickness, edgeColor);

	//draw arrow head

	float theta1 = theta + arrowHeadAngle;
	float theta2 = theta - arrowHeadAngle;

	Vector2 arrowPoint1 = { toX - arrowHeadLength * cos(theta1), toY - arrowHeadLength * sin(theta1) };
	Vector2 arrowPoint2 = { toX - arrowHeadLength * cos(theta2), toY - arrowHeadLength * sin(theta2) };

	DrawTriangle({toX,toY}, arrowPoint1, arrowPoint2, edgeColor);
}
void CBEdge::addEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to) {
	Edges.push_back(new CBEdge(from, to));
}
void CBEdge::removeEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to) {
	for (int i = 0; i < Edges.size(); i++) {
		if (Edges[i]->from == from && Edges[i]->to == to) {
			CBEdge* del = Edges[i];
			Edges.erase(Edges.begin() + i);
			delete del;
			del = nullptr;
			return;
		}
	}
}
