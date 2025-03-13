#include "../header/Edge.h"
#include "../header/UI.h"
void Edge::drawEdge() {
	int fromX = from->position.x + from->radius;
	int fromY = from->position.y;
	if (!to) {
		DrawLine(fromX, fromY, fromX + 200, fromY, BLACK);
		UI::drawtext2("NULL",fromX, fromY, BLUE);
		return;
	}
	int toX = to->position.x - to->radius;
	int toY = to->position.y;
	DrawLine(fromX, fromY, toX, toY, BLACK);
}