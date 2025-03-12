#pragma once
#include "Node.h"
class UI;
class Edge {
protected:
	
public:
	int thickness;
	Node* from;
	Node* to;
	Edge() {
		thickness = 5;
		from = nullptr;
		to = nullptr;
	}
	Edge(Node* f, Node* t) : from(f), to(t){
		thickness = 5;
	}
	Edge(int th, Node* f, Node* t) : thickness(th), from(f), to(t){}
	bool operator==(const Edge& other) const {
		return (from == other.from && to == other.to);
	}
	void drawEdge();
};