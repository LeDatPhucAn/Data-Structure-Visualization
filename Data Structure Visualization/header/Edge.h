#pragma once
#include "Node.h"
#include <vector>
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
	static void addEdge(vector<Edge*>& Edges, Node* from, Node* to);
	static void removeEdge(vector<Edge*>& Edges, Node* from, Node* to);
	void drawEdge();
	void drawArrowEdge();
	void drawTreapEdge();
};

class CircleButton;
class CBEdge {
protected:
	
public:
	int thickness;
	CircleButton* from;
	CircleButton* to;
	CBEdge() {
		thickness = 5;
		from = nullptr;
		to = nullptr;
	}
	CBEdge(CircleButton* f, CircleButton* t) : from(f), to(t){
		thickness = 5;
	}
	CBEdge(int th, CircleButton* f, CircleButton* t) : thickness(th), from(f), to(t){}
	static void addEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	static void removeEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	void drawArrowEdge();
};