#pragma once
#include "Node.h"
class UI;
class Edge {
protected:
	
public:
	Node* from;
	Node* to;
	Edge() {
		from = nullptr;
		to = nullptr;
	}
	Edge(Node* f, Node* t) : from(f), to(t){
	}
	bool operator==(const Edge& other) const {
		return (from == other.from && to == other.to);
	}
	void drawEdge();
};