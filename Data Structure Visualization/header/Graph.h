#pragma once
#include <vector>
#include <set>
#include "Edge.h"
#include "Node.h"
#include "raylib.h"
#include "UI.h"
#include "Button.h"
#include "GraphEdge.h"
#include "PseudoCode.h"
#include "Animation.h"
/*
enum class InitStateOfGraph {
	InputMatrix,
	Confirmed
};
InitStateOfGraph state = InitStateOfGraph::InputMatrix;
*/
const int INF = 1e9;
class GraphNode : public NumberInputCircleInCamera {
public:
	GraphNode() : NumberInputCircleInCamera(3) {}
	
	GraphNode(int value) : NumberInputCircleInCamera({ 0,0 }, 50, value, 3) {
	}

	GraphNode(int value, Vector2 pos) : NumberInputCircleInCamera(pos, 50, value, 3) {
	}
	GraphNode(int value, Vector2 pos, int r) : NumberInputCircleInCamera(pos, r, value, 3) {
	}

	GraphNode(int value, float X, float Y) : NumberInputCircleInCamera({ X,Y }, 50, value, 3) {
	}

	GraphNode(int value, float X, float Y, int r) : NumberInputCircleInCamera({ X,Y }, r, value, 3) {
	}
};
class EdgeOfGraph;
class Graph {
private:
	int numberVertices;
	std::vector<GraphNode*> nodes;
	std::vector<EdgeOfGraph*> edges;
	vector<vector<int>> adjMatrix;
	std::vector<Vector2> position;
	vector<vector<float>> path;
	
	vector<float> cost;
	vector<bool> visited;
	bool drawDijk = false;
	struct DijkstraState {
		std::vector<float> cost;
		std::vector<bool> visited;
		std::vector<std::vector<float>> path;
		int current = -1;
	};
	std::vector<DijkstraState> dijkstraHistory;
	
	bool isDijkstraPlaying = false;
	int currentStep = 0;
	float radiusNode = 50.0f;
	int maxID = 0;
	set<int> deleteIds; // luu danh sach cac node bi xoa.
public:
	
	Graph() : numberVertices(0), maxID(0), visited(numberVertices, false), cost(numberVertices, INF),
		path(numberVertices, {}) {}
	Graph(int numVertices) : numberVertices(numVertices), maxID(0) {
		calculatePositions(numberVertices);

		for (int i = 0; i < numVertices; ++i) {
			int id = i + 1;
			nodes.push_back(new GraphNode(i + 1, position[i], radiusNode));
			maxID = std::max(maxID, id);
		}
	}
	void calculatePositions(int n);
	bool checkEdge(int id1, int id2);
	void addNode(Vector2 position);
	void removeNode(int id);
	void addEdge(int from, int to, float weight = -1);
	void removeEdge(int from, int to);
	void clear();
	GraphNode* getNodeById(int id);
	void printGraph();
	void printPosition();
	void printEdge();

	void clearIndicates();
	void adjustPos(GraphNode* head) {};
	void adjustPosWithAnim2(AnimationManager& animManager);

	void DijkstraAnim(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int startID);
	void loadFromFile() ;
	void setRadiusNode(int newR) { radiusNode = newR; }
	void setNumberOfVertices(int newV) { numberVertices = newV; }

	void drawMatrixTable(int n, const vector<vector<string>>& inputs, int selectedRow, int selectedCol);
	void initGraph(int n);

	void Dijkstra(int startID);
	void saveDijkstraState(int current);
	void snapshot(int current);
	void resetDijkstra() {
		int n = numberVertices;
		cost.assign(n, INF);
		visited.assign(n, false);
		path.assign(n, {});
	}
	void drawDijkstraTable(int current);
	void drawDijkstra() {
		if (!drawDijk) {
			drawDijk = true;
		}
		else {
			drawDijk = false;
		}
	}
	void setCurrentStep() { currentStep--; }
	int getCurrentStep() { return currentStep; }
	bool getDrawDijkstra() { return drawDijk; }
	vector<GraphNode*> ListNodeOnGraph() { return nodes; }
	vector<EdgeOfGraph*> ListEdgeOnGraph() { return edges; }
	int numberOfVertices() const { return numberVertices; }
	float radiusOfNode() const { return radiusNode; }
	~Graph();

};