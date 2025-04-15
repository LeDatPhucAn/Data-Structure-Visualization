#pragma once
#include "Node.h"
#include "raylib.h"
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
	Edge(Node* f, Node* t) : from(f), to(t) {
		thickness = 5;
	}
	Edge(int th, Node* f, Node* t) : thickness(th), from(f), to(t) {}
	static void addEdge(vector<Edge*>& Edges, Node* from, Node* to);
	static void removeEdge(vector<Edge*>& Edges, Node* from, Node* to);
	void drawEdge();
	void drawArrowEdge();
};

class TreapNode;
class TreapEdge {
public:
	TreapNode* from;
	TreapNode* to;
	int thickness;
	bool noDraw;
	Color edgeColor;

	TreapEdge(TreapNode* f , TreapNode* t, Color c = BLACK, int th = 5) : from(f), to(t), edgeColor(c), thickness(th), noDraw(false){}

	void draw();
	static void addEdge(vector<TreapEdge*>& edges, TreapNode* from, TreapNode* to);
	static void removeEdge(vector<TreapEdge*>& edges, TreapNode* from, TreapNode* to);
};

// Circle Button Edge used for Circle Buttons
class CircleButton;
class AnimationManager;
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
	static CBEdge* findEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	static void addEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	static void removeEdge(vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	static void addEdgeAndAnim(AnimationManager& animManager, vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	static void removeEdgeAndAnim(AnimationManager& animManager, vector<CBEdge*>& Edges, CircleButton* from, CircleButton* to);
	void drawArrowEdge();
};