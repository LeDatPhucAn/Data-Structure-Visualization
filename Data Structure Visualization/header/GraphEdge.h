#pragma once
#include "Graph.h"
#include "raylib.h"
#include "Button.h"
#include "Animation.h"
#include <vector>

class CircleButton;
class Animation;
class EdgeOfGraph {
protected:
	

public:
	bool noDraw;
	int thickness;
	float weight;
	CircleButton* from;
	CircleButton* to;
	Color edgeColor;
	EdgeOfGraph() {
		edgeColor = BLACK;
		thickness = 5;
		weight = 0;
		from = nullptr;
		to = nullptr;
		noDraw = false;
	}
	EdgeOfGraph(CircleButton* f, CircleButton* t) : noDraw(false), from(f), to(t), edgeColor(BLACK) {

		thickness = 5;
		weight = 0;
	}
	EdgeOfGraph(float weight, CircleButton* f, CircleButton* t, Color c = BLACK) : noDraw(false), weight(weight), from(f), to(t), edgeColor(c) {
		thickness = 5;
	}
	EdgeOfGraph(int th, float weight, CircleButton* f, CircleButton* t, Color c = BLACK) : 
		thickness(th), weight(weight), from(f), to(t), noDraw(false), edgeColor(c) {}
	static void addEdge(vector<EdgeOfGraph*>& Edges, 
		CircleButton* from, CircleButton* to);
	static void removeEdge(vector<EdgeOfGraph*>& Edges, 
		CircleButton* from, CircleButton* to);
	void drawEdge();
	//void drawArrowEdge();
	

};
class GEdgeHighlightAnim : public Animation {
protected:
	EdgeOfGraph* edge;
	Color startC, endC;
public:
	virtual ~GEdgeHighlightAnim() = default;

	// default color is orange
	GEdgeHighlightAnim(EdgeOfGraph* e, float duration, Color eC = ORANGE, std::function<void()> func = nullptr)
		: Animation(duration, func), endC(eC), edge(e)
	{
		startC = e->edgeColor;
	}
	void resetColor() override {
		edge->edgeColor = startC;
	}
	void applyState() override;
};