#pragma once
#include <vector>
#include "Edge.h"
#include "Node.h"
#include "raylib.h"
#include "UI.h"
class EdgeOfGraph : public Edge {
private:
	float weight;
public:
	EdgeOfGraph(int weight) : Edge(), weight(weight) {}
	EdgeOfGraph(int weight, Node* f, Node* t) : weight(weight), 
		Edge(f, t) {}
	EdgeOfGraph(int weight, int th, Node* f, Node* t) : weight(weight), 
		Edge(th, f, t) {}
};
class Graph {
private:
	int numberVertices;
	std::vector<Node*> nodes;
	std::vector<EdgeOfGraph*> edges;
	std::vector<Vector2> position;
	float radiusNode = 50.0f;
public:
	Graph(int numVertices) : numberVertices(numVertices) {
		calculatePositions();
		for (int i = 0; i < numVertices; ++i) {
			nodes.push_back(new Node(i + 1, position[i], radiusNode));
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
	void setRadiusNode(int newR) { radiusNode = newR; }
	void setNumberOfVertices(int newV) { numberVertices = newV; }
	int numberOfVertices() const { return numberVertices; }
	float radiusOfNode() const { return radiusNode; }
	~Graph();

};