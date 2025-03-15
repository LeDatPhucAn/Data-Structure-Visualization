#pragma once
#include "Node.h"
#include <vector>
class Edge {
protected:
	
public:
	Node* from;
	Node* to;
	Edge() {
		from = nullptr;
		to = nullptr;
	}
	Edge(Node* f, Node* t) : from(f), to(t){
	}

	Edge(int th, Node* f, Node* t) : thickness(th), from(f), to(t){}
	//bool operator==(const Edge& other) const {
	//	return (from == other.from && to == other.to);
	//}
	static void addEdge(vector<Edge*>& Edges, Node* from, Node* to);
	static void removeEdge(vector<Edge*>& Edges, Node* from, Node* to);

	void drawEdge();
};