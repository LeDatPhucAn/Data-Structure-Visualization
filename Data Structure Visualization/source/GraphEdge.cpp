#include "../header/GraphEdge.h"
#include "../header/Button.h"


void EdgeOfGraph::drawEdge() {
	if (!from || !to) return;
	float a = from->getCenterX();
	float b = from->getCenterY();
	float c = to->getCenterX();
	float d = to->getCenterY();
	float AB = sqrt(pow(a - c, 2) + pow(d - b, 2));

	float fromX = a + (float)from->getRadius() * (c - a) / AB;
	float fromY = b + (float)from->getRadius() * (d - b) / AB;
	float toX = c - (float)to->getRadius() * (c - a) / AB;
	float toY = d - (float)to->getRadius() * (d - b) / AB;
	//draw edge

	DrawLineEx({ fromX,fromY }, { toX, toY }, thickness, edgeColor);

	float midX = (fromX + toX) / 2.0f;
	float midY = (fromY + toY) / 2.0f;


	float dx = toX - fromX;
	float dy = toY - fromY;
	float len = sqrtf(dx * dx + dy * dy);
	float nx = -dy / len;
	float ny = dx / len;


	float offset = 16.0f;
	float textX = midX + nx * offset;
	float textY = midY + ny * offset;


	std::string text = std::to_string((int)weight);

	float angle = atan2f(dy, dx);
	//if (angle > PI / 2 || angle < -PI / 2) angle += PI;
	if (angle > PI / 2 || angle < -PI / 2) {
		angle += PI;

		textX = midX - nx * offset;
		textY = midY - ny * offset;
	}
	Vector2 position = { textX, textY };
	int fontSize = 20;
	Font font = GetFontDefault();
	Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, 1);
	Vector2 origin = { textSize.x / 2, textSize.y / 2 };

	DrawTextPro(font, text.c_str(), position, origin, angle * 180 / PI, fontSize, 1, RED);
}
void EdgeOfGraph::removeEdge(vector<EdgeOfGraph*>& Edges, CircleButton* from, CircleButton* to) {
	for (int i = 0; i < Edges.size(); i++) {
		if (Edges[i]->from == from && Edges[i]->to == to) {
			
			EdgeOfGraph* del = Edges[i];
			Edges.erase(Edges.begin() + i);
			delete del;
			del = nullptr;
			return;
		}
	}
}
void EdgeOfGraph::addEdge(vector<EdgeOfGraph*>& Edges, CircleButton* from, CircleButton* to) {
	Edges.push_back(new EdgeOfGraph(from, to));
}
void EdgeOfGraph::addEdgeAndAnim(AnimationManager& animManager, vector<EdgeOfGraph*>& Edges, CircleButton* from, CircleButton* to) {
	//Edges.push_back(new EdgeOfGraph(from, to));
	EdgeOfGraph* edge;

	animManager.addAnimation(new GEdgeHighlightAnim(Edges.back(), 0.2f, PURPLE));
	animManager.addAnimation(new GEdgeHighlightAnim(Edges.back(), 1));
}
void GEdgeHighlightAnim::applyState() {
	edge->noDraw = false;
	float easedT = EaseSineIn(elapsed, 0, 1.0f, duration);
	edge->edgeColor = UI::interpolateColors(startC, endC, easedT);
}

