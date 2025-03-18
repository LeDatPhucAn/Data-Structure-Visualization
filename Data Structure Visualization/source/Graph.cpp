#include "../header/Graph.h"
void Graph::calculatePositions() {
	position.clear();
	float width = UI::screenWidth, height = UI::screenHeight;

	std::vector<Vector2> predefinedPositions = {
		{width * 0.3f, height * 0.3f}, {width * 0.7f, height * 0.3f},
		{width * 0.5f, height * 0.5f}, {width * 0.3f, height * 0.7f},
		{width * 0.7f, height * 0.7f}
	};

	for (int i = 0; i < numberVertices; ++i) {
		position.push_back(predefinedPositions[i % predefinedPositions.size()]);
	}
}
void Graph::addNode(Vector2 pos) {
	int id = nodes.size() + 1;
	setNumberOfVertices(id);
	position.push_back(pos);
	nodes.push_back(new Node(id, pos, radiusNode));
}
void Graph::removeNode(int id) {
	nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
		[id](Node* node) { return node->data == id;  }), nodes.end());
	edges.erase(std::remove_if(edges.begin(), edges.end(),
		[id](EdgeOfGraph* edge) {
			return edge->from->data == id ||
				edge->to->data == id;
		}),
		edges.end());
}
void Graph::addEdge(int from, int to, float weight) {
	Node* nodeFrom = Graph::getNodeById(from);
	Node* nodeTo = Graph::getNodeById(to);
	if (nodeFrom && nodeTo) {
		edges.push_back(new EdgeOfGraph(weight, nodeFrom, nodeTo));
	}
}
void Graph::removeEdge(int from, int to) {
	edges.erase(std::remove_if(edges.begin(), edges.end(),
		[from, to](EdgeOfGraph* edge) {
			return (edge->from->data == from && edge->to->data == to) ||
				(edge->from->data == to && edge->to->data == from);
		}),
		edges.end());

}
Node* Graph::getNodeById(int id) {
	for (auto node : nodes) {
		if (node->data == id) return node;
	}
	return nullptr;
}
Graph::~Graph() {
	for (Node* node : nodes) {
		delete node;
	}
	for (EdgeOfGraph* edge : edges) {
		delete edge;
	}
}
void Graph::printGraph() {
	cout << "Graph Adjacency List: " << std::endl;
	for (Node* node : nodes) {
		int val = node->data;
		cout << "Node " << val << " -> ";
		bool hasEdge = false;
		for (EdgeOfGraph* edge : edges) {
			if (edge->from->data == val) {
				cout << edge->to->data << " ";
				hasEdge = true;
			}
			if (edge->to->data == val) {
				cout << edge->from->data << " ";
				hasEdge = true;
			}

		}
		if (!hasEdge) {
			cout << "no edges";
		}
		cout << endl;
		
	}
	cout << endl;
}
void Graph::printPosition() {
	for (Vector2 pos : position) {
		cout << pos.x << " " << pos.y << endl;
	}
}