#pragma once
#include "Node.h"
#include <vector>
class Edge {
protected:
	
public:
	int thickness;
	Node* from;
	Node* to;
	int thickness;
	Edge() {
		thickness = 5;
		from = nullptr;
		to = nullptr;
	}
<<<<<<< HEAD
	Edge(Node* f, Node* t) : from(f), to(t){}

=======
	Edge(Node* f, Node* t) : from(f), to(t){
		thickness = 5;
	}
>>>>>>> master
	Edge(int th, Node* f, Node* t) : thickness(th), from(f), to(t){}
	static void addEdge(vector<Edge*>& Edges, Node* from, Node* to);
	static void removeEdge(vector<Edge*>& Edges, Node* from, Node* to);
	void drawEdge();
	void drawTreapEdge();
};