#pragma once
#include <vector>
#include <set>
#include "Edge.h"
#include "Node.h"
#include "raylib.h"
#include "UI.h"

class EdgeOfGraph : public	Edge {
private:
	float weight;
public:
	EdgeOfGraph() : Edge(), weight(-1) {}
	EdgeOfGraph(int weight) : Edge(), weight(weight) {}
	EdgeOfGraph(int weight, Node* f, Node* t) : weight(weight), 
		Edge(f, t) {}
	EdgeOfGraph(int weight, int th, Node* f, Node* t) : weight(weight), 
		Edge(th, f, t) {}
	void setWeight(float weight) {
		weight = weight;
	}
	float getWeight() const { return weight; }
};
class Graph {
private:
	int numberVertices;
	std::vector<Node*> nodes;
	std::vector<EdgeOfGraph*> edges;
	std::vector<Vector2> position;
	float radiusNode = 50.0f;
	int maxID = 0;
	set<int> deleteIds; // luu danh sach cac node bi xoa.
public:
	Graph() : numberVertices(0), maxID(0) {}
	Graph(int numVertices) : numberVertices(numVertices), maxID(0) {
		calculatePositions();

		for (int i = 0; i < numVertices; ++i) {
			int id = i + 1;
			nodes.push_back(new Node(i + 1, position[i], radiusNode));
			maxID = std::max(maxID, id);
		}
	}
	void calculatePositions();
	void addNode(Vector2 position);
	void removeNode(int id);
	void addEdge(int from, int to, float weight = -1);
	void removeEdge(int from, int to);
	Node* getNodeById(int id);
	void printGraph();
	void printPosition();
	void printEdge();

	void setRadiusNode(int newR) { radiusNode = newR; }
	void setNumberOfVertices(int newV) { numberVertices = newV; }

	vector<Node*> ListNodeOnGraph() { return nodes; }
	vector<EdgeOfGraph*> ListEdgeOnGraph() { return edges; }
	int numberOfVertices() const { return numberVertices; }
	float radiusOfNode() const { return radiusNode; }
	~Graph();

};