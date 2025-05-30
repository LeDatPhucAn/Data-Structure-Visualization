#include "../header/Edge.h"
#include "../header/UI.h"
#include "../header/Treap.h"
#include "../header/Animation.h"
#include "../header/AnimationManager.h"
#include "../header/Button.h"

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
	DrawLineEx({ fromX,fromY }, { toX,toY }, thickness, BLACK);
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
	float arrowHeadLength = thickness * 5;

	float theta = atan2(dy, dx);

	float fromX = from->radius * cos(theta) + from->position.x;
	float fromY = from->radius * sin(theta) + from->position.y;
	float toX = to->position.x - to->radius * cos(theta);
	float toY = to->position.y - to->radius * sin(theta);

	float EdgeEndX = toX - arrowHeadLength * cos(theta) * sqrt(3) / 2;
	float EdgeEndY = toY - arrowHeadLength * sin(theta) * sqrt(3) / 2;
	//draw edge

	DrawLineEx({ fromX,fromY }, { EdgeEndX, EdgeEndY }, thickness, BLACK);

	//draw arrow head

	float theta1 = theta + arrowHeadAngle;
	float theta2 = theta - arrowHeadAngle;

	Vector2 arrowPoint1 = { toX - arrowHeadLength * cos(theta1), toY - arrowHeadLength * sin(theta1) };
	Vector2 arrowPoint2 = { toX - arrowHeadLength * cos(theta2), toY - arrowHeadLength * sin(theta2) };

	DrawTriangle({ toX,toY }, arrowPoint1, arrowPoint2, BLACK);
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

void TreapEdge::draw() {
	if (!from || !to || noDraw) return;

	Rectangle fromRect = from->keyBox->rect;
	Rectangle toRect = to->keyBox->rect;

	Vector2 start = {
		fromRect.x + fromRect.width / 2,
		fromRect.y + fromRect.height
	};
	Vector2 end = {
		toRect.x + toRect.width / 2,
		toRect.y
	};

	DrawLineEx(start, end, thickness, edgeColor);
}

void TreapEdge::addEdge(vector<TreapEdge*>& edges, TreapNode* from, TreapNode* to) {
	edges.push_back(new TreapEdge(from, to));
}

void TreapEdge::removeEdge(vector<TreapEdge*>& edges, TreapNode* from, TreapNode* to) {
	for (int i = 0; i < edges.size(); ++i) {
		if (edges[i]->from == from && edges[i]->to == to) {
			delete edges[i];
			edges.erase(edges.begin() + i);
			return;
		}
	}
}

void CBEdge::drawArrowEdge()
{
	if (noDraw || !from || !to) return;
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
CBEdge* CBEdge::findEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to) {
	if (!from)return nullptr;
	for (int i = 0; i < Edges.size(); i++) {
		if (Edges[i]->from == from && Edges[i]->to == to) {
			return Edges[i];
		}
	}
	return nullptr;
}

void CBEdge::addEdgeAndAnim(AnimationManager& animManager, vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to) {
	Edges.push_back(new CBEdge(from, to));
	animManager.addAnimation(new CBEdgeHighLightAnim(Edges.back(), 0.2f, PURPLE));
	animManager.addAnimation(new CBEdgeAddAnim(Edges.back(), 1));
}

void CBEdge::removeEdgeAndAnim(AnimationManager& animManager, vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to) {
	// highlight the edge before removing it, Also Animate the removal
	for (int i = 0; i < Edges.size(); i++) {
		if (Edges[i]->from == from && Edges[i]->to == to) {
			//highlight the edge
			animManager.addAnimation(new CBEdgeHighLightAnim(Edges[i], 0.5f, RED));

			//animate removal
			animManager.addAnimation(new CBEdgeRemoveAnim(Edges[i], 0.5f));
			break;
		}
	}

	 //remove the edge before operation
	animManager.addAnimation(new RemoveEdgeInAnim(0.5, from,to,[&Edges, from, to]() {
		removeEdge(Edges, from, to);
		}));
}
