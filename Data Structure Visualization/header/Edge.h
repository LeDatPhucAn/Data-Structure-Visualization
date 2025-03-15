#pragma once
#include "Node.h"
#include <vector>
class Edge {
protected:
	
public:
	Node* from;
	Node* to;
	int thickness;
	Edge() {
		from = nullptr;
		to = nullptr;
	}
	Edge(Node* f, Node* t) : from(f), to(t){}

	Edge(int th, Node* f, Node* t) : thickness(th), from(f), to(t){}
	static void addEdge(vector<Edge*>& Edges, Node* from, Node* to);
	static void removeEdge(vector<Edge*>& Edges, Node* from, Node* to);

	void drawEdge();
	void drawTreapEdge();
};