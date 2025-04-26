#pragma once
#include "Graph.h"
#include "raylib.h"
#include "reasings.h"
#include <vector>
#include "Animation.h"
class CircleButton;
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
	static void addEdgeAndAnim(AnimationManager& animManager, vector<EdgeOfGraph*>& Edges, CircleButton* from, CircleButton* to);
	void drawEdge();
	//void drawArrowEdge();
	void setEdgeColor(Color c) { edgeColor = c; }

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
class DijkstraCellHighlightAnim : public Animation {
public:
	int row, col;
	float cellWidth, cellHeight;
	float startX, startY;
	Color color;
	double startTime;
	float durationReal;
	bool started = false;
	DijkstraCellHighlightAnim(int r, int c, float dur, Color col, 
		std::function<void()> callback = nullptr,
		float cellW = 150, float cellH = 50,
		float originX = 150, float originY = 10
		)
		: Animation(dur, callback), row(r), col(c),
		cellWidth(cellW), cellHeight(cellH),
		startX(originX), startY(originY), color(col) {
	}

	
	void applyState() override {
		float x = startX + col * cellWidth;
		float y = startY + (row + 1) * cellHeight;

		float alpha = 1.0f - getProgress(); // fade out
		DrawRectangleRec({ x, y, cellWidth, cellHeight }, Fade(color, alpha));
	}
	void update(float deltaTime) override {
		if (!started) {
			startTime = GetTime();
			started = true;
		}

		double elapsedTime = GetTime() - startTime;

		if (elapsedTime >= durationReal) {
			completed = true;
			if (Function && !FunctionActivated) {
				Function();
				FunctionActivated = true;
			}
		}
	}
};
