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

// Circle Button Edge used for Circle Buttons
class CircleButton;
class CBEdge {
protected:
	
public:
	bool noDraw;
	int thickness;
	Color edgeColor;
	CircleButton* from;
	CircleButton* to;
	CBEdge() {
		edgeColor = BLACK;
		thickness = 5;
		from = nullptr;
		to = nullptr;
		noDraw = false;
	}
	CBEdge(CircleButton* f, CircleButton* t) :noDraw(false), from(f), to(t), edgeColor(BLACK){
		thickness = 5;
	}
	CBEdge(int th, CircleButton* f, CircleButton* t, Color c = BLACK) : noDraw(false), thickness(th), from(f), to(t), edgeColor(c){}
	static void addEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	static void removeEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	void drawArrowEdge();
};