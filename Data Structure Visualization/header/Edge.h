#pragma once
#include "Node.h"
class Edge {
protected:
	int thickness;
	Node* from;
	Node* to;
public:
	void drawEdge();
};