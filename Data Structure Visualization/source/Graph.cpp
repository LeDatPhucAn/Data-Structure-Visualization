
#include "../header/Graph.h"
void EdgeOfGraph::drawEdgeOfGraph() {
	if (!from || !to) return;
	
	float a = from->position.x;
	float b = from->position.y;
	float c = to->position.x;
	float d = to->position.y;
	float AB = sqrt(pow(a - c, 2) + pow(d - b, 2));

	float fromX = a + (float)from->radius * (c - a) / AB;
	float fromY = b + (float)from->radius * (d - b) / AB;
	float toX = c - (float)to->radius * (c - a) / AB;
	float toY = d - (float)to->radius * (d - b) / AB;
	//draw edge
	
	DrawLineEx({ fromX,fromY }, { toX, toY }, thickness, BLACK);

	float midX = (fromX + toX) / 2.0f;
	float midY = (fromY + toY) / 2.0f;

	
	float dx = toX - fromX;
	float dy = toY - fromY;
	float len = sqrtf(dx * dx + dy * dy);
	float nx = -dy / len;
	float ny = dx / len;

	
	float offset = 16.0f; 
	float textX = midX + nx * offset;
	float textY = midY + ny * offset;

	
	std::string text = std::to_string((int)weight); 
	
	float angle = atan2f(dy, dx);  
	//if (angle > PI / 2 || angle < -PI / 2) angle += PI;

	Vector2 position = { textX, textY };
	int fontSize = 20;
	Font font = GetFontDefault(); 
	Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, 1);
	Vector2 origin = { textSize.x / 2, textSize.y / 2 };

	DrawTextPro(font, text.c_str(), position, origin, angle * 180 / PI, fontSize, 1, RED);
}
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
	int id;

	if (!deleteIds.empty()) {
		id = *deleteIds.begin();
		deleteIds.erase(deleteIds.begin());
	}
	else {
		id = ++maxID;
	}
	setNumberOfVertices(nodes.size() + 1);
	position.push_back(pos);
	nodes.push_back(new Node(id, pos, radiusNode));
}
void Graph::removeNode(int id) {
	edges.erase(std::remove_if(edges.begin(), edges.end(),
		[id](EdgeOfGraph* edge) {
			return edge->from->data == id ||
				edge->to->data == id;
		}),
		edges.end());

	auto posIt = position.begin();
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (nodes[i]->data == id) {
			posIt = position.begin() + i;
			break;
		}
	}
	if (posIt != position.end()) {
		position.erase(posIt);
	}
	auto iter = std::find_if(nodes.begin(), nodes.end(),
		[id](Node* node) { return node->data == id; });

	if (iter != nodes.end()) {
		deleteIds.insert(id);
		delete* iter;
		nodes.erase(iter);
	}
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
	nodes.clear();
	for (EdgeOfGraph* edge : edges) {
		delete edge;
	}
	edges.clear();
	position.clear();
	deleteIds.clear();
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
void Graph::printEdge() {
	for (auto edge : edges) {
		cout << edge->from->data << " " << edge->to->data << endl;
	}
}
void Graph::clear() {
	for (Node* node : nodes) {
		delete node;
	}
	nodes.clear();

	
	for (EdgeOfGraph* edge : edges) {
		delete edge;
	}
	edges.clear();

	
	position.clear();
	deleteIds.clear();

	
	numberVertices = 0;
	maxID = 0;
}