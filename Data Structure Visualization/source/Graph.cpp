#include "fstream"
#include "sstream"
#include "../header/tinyfiledialogs.h"
#include "../header/Graph.h"
#include "../header/Animation.h"

void Graph::adjustPosWithAnim2(AnimationManager& animManager) {
	
}
void Graph::calculatePositions(int n) {
	position.clear();

	vector<Vector2> predefined = {
		{200, 100}, 
		{400, 0},
		{600, 200},
		{800, 100},
		{100, 300},
		{300, 1000},
		{600, 850},
		{900, 900},
		{400, 600},
		{750, 600}
	};
	if (n <= predefined.size()) {
		for (int i = 0; i < n; ++i) {
			position.push_back(predefined[i]);
		}
	}
	else {
		float centerX = UI::screenWidth / 2.0f;
		float centerY = UI::screenHeight / 2.0f;
		float radius = 800.0f;

		for (int i = 0; i < n; ++i) {
			float angle = 2 * PI * i / n;
			float x = centerX + radius * cosf(angle);
			float y = centerY + radius * sinf(angle);
			position.push_back({ x, y });
		}
	}
}
bool Graph::checkEdge(int id1, int id2) {
	GraphNode* node1 = getNodeById(id1);
	GraphNode* node2 = getNodeById(id2);
	if (!node1 || !node2) return false;

	for (auto& edge : edges) {
		if ((edge->from == node1 && edge->to == node2) ||
			(edge->from == node2 && edge->to == node1)) {
			return true;
		}
	}
	return false;
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
	nodes.push_back(new GraphNode(id, pos, radiusNode));
}
void Graph::removeNode(int id) {
	GraphNode* nodeRemove = getNodeById(id);
	if (!nodeRemove) return;
	// Remove edges connected to the node
	for (auto it = edges.begin(); it != edges.end(); ) {
		if ((*it)->from == nodeRemove || (*it)->to == nodeRemove) {
			delete* it;
			it = edges.erase(it); 
		}
		else {
			++it;
		}
	}

	
	auto posIt = position.begin();
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (nodes[i]->getNumber() == id) {
			posIt = position.begin() + i;
			break;
		}
	}
	if (posIt != position.end()) {
		position.erase(posIt);
	}
	auto iter = std::find_if(nodes.begin(), nodes.end(),
		[id](GraphNode* node) { return node->getNumber() == id; });

	if (iter != nodes.end()) {
		deleteIds.insert(id);
		delete* iter;
		nodes.erase(iter);
	}
}
void Graph::addEdge(int from, int to, float weight) {
	GraphNode* nodeFrom = Graph::getNodeById(from);
	GraphNode* nodeTo = Graph::getNodeById(to);
	if (nodeFrom && nodeTo) {
		edges.push_back(new EdgeOfGraph(weight, nodeFrom, nodeTo));
	}
}
void Graph::removeEdge(int from, int to) {
	GraphNode* nodeFrom = getNodeById(from);
	GraphNode* nodeTo = getNodeById(to);
	if (!nodeFrom || !nodeTo) return;
	for (auto it = edges.begin(); it != edges.end(); ) {
		if (((*it)->from == nodeFrom && (*it)->to == nodeTo) ||
			((*it)->from == nodeTo && (*it)->to == nodeFrom)) {
			delete* it;
			it = edges.erase(it);
		}
		else {
			++it;
		}
	}
}
GraphNode* Graph::getNodeById(int id) {
	for (auto node : nodes) {
		if (node->getNumber() == id) return node;
	}
	return nullptr;
}
Graph::~Graph() {
	for (GraphNode* node : nodes) {
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
	for (int i = 0; i < nodes.size(); ++i) {
		for (int j = i; j < nodes.size(); ++j) {
			if (checkEdge(i, j)) {
				cout << nodes[i]->getNumber() << " " << nodes[j]->getNumber() << endl;
			}
		}
	}
	cout << endl;
}
void Graph::drawMatrixTable(int n, const vector<vector<string>>& inputs, int selectedRow, int selectedCol) {
	// Draw the table
	float screenWidth = UI::screenWidth;
	float screenHeight = UI::screenHeight;

	float cellSize = 60.0f;
	float tableWidth = cellSize * n;
	float tableHeight = cellSize * n;
	float startX = (screenWidth - tableWidth) / 2.0f;
	float startY = (screenHeight - tableHeight) / 2.0f;

	Font font = GetFontDefault();
	int fontSize = 20;

	for (int row = 0; row < n; ++row) {
		for (int col = 0; col < n; ++col) {
			float x = startX + col * cellSize;
			float y = startY + row * cellSize;
			Rectangle cellRect = { x, y, cellSize, cellSize };

			if (row == selectedRow && col == selectedCol) {
				DrawRectangleRec(cellRect, LIGHTGRAY);
			}
			else {
				DrawRectangleLinesEx(cellRect, 2, DARKGRAY);
			}

			std::string content = inputs[row][col];
			Vector2 textSize = MeasureTextEx(font, content.c_str(), fontSize, 1);
			float textX = x + (cellSize - textSize.x) / 2;
			float textY = y + (cellSize - textSize.y) / 2;

			DrawText(content.c_str(), textX, textY, fontSize, BLACK);
		}
	}
	for (int i = 0; i < n; ++i) {
		std::string index = std::to_string(i);
		Vector2 size = MeasureTextEx(font, index.c_str(), fontSize, 1);

		DrawText(index.c_str(),
			startX + i * cellSize + (cellSize - size.x) / 2,
			startY - cellSize * 0.8f,
			fontSize, DARKGRAY);

		DrawText(index.c_str(),
			startX - cellSize * 0.8f,
			startY + i * cellSize + (cellSize - size.y) / 2,
			fontSize, DARKGRAY);
	}

	DrawRectangleLines(startX - 2, startY - 2, tableWidth + 4, tableHeight + 4, GRAY);
}
void Graph::initGraph(int n) {
	const float screenWidth = UI::screenWidth;
	const float screenHeight = UI::screenHeight;
	const float cellSize = 60.0f;

	float tableWidth = n * cellSize;
	float tableHeight = n * cellSize;
	float startX = (screenWidth - tableWidth) / 2.0f;
	float startY = (screenHeight - tableHeight) / 2.0f;

	Rectangle okButton = { screenWidth / 2.0f - 50, startY + tableHeight + 40, 100, 40 };

	vector<vector<string>> inputs(n, vector<string>(n, ""));
	int selectedRow = 0;
	int selectedCol = 0;
	bool confirmed = false;

	SetTargetFPS(60);
	
	while (!WindowShouldClose() && !confirmed) {
		
		// input number
		int key = GetCharPressed();
		while (key > 0) {
			if ((key >= '0' && key <= '9') || key == '-') {
				if (inputs[selectedRow][selectedCol].length() < 3)
					inputs[selectedRow][selectedCol] += static_cast<char>(key);
			}
			key = GetCharPressed();
		}
		//delete
		if (IsKeyPressed(KEY_BACKSPACE)) {
			if (!inputs[selectedRow][selectedCol].empty())
				inputs[selectedRow][selectedCol].pop_back();
		}
		//move cell (keyboard)
		if (IsKeyPressed(KEY_RIGHT)) selectedCol = (selectedCol + 1) % n;
		if (IsKeyPressed(KEY_LEFT)) selectedCol = (selectedCol - 1 + n) % n;
		if (IsKeyPressed(KEY_DOWN)) selectedRow = (selectedRow + 1) % n;
		if (IsKeyPressed(KEY_UP)) selectedRow = (selectedRow - 1 + n) % n;
		//move cell (mouse)
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse = GetMousePosition();
			float mouseX = mouse.x;
			float mouseY = mouse.y;

			if (mouseX >= startX && mouseX < startX + tableWidth &&
				mouseY >= startY && mouseY < startY + tableHeight) {
				int colClicked = (int)((mouseX - startX) / cellSize);
				int rowClicked = (int)((mouseY - startY) / cellSize);

				selectedRow = rowClicked;
				selectedCol = colClicked;
			}

			if (CheckCollisionPointRec(mouse, okButton)) {
				confirmed = true;
			}
		}
		//check ok
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse = GetMousePosition();
			if (CheckCollisionPointRec(mouse, okButton)) {
				confirmed = true;
			}
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);

		drawMatrixTable(n, inputs, selectedRow, selectedCol);

		DrawRectangleRec(okButton, DARKGREEN);
		DrawText("OK", okButton.x + 30, okButton.y + 10, 20, RAYWHITE);

		EndDrawing();
	}
	clear();
	setNumberOfVertices(n);
	calculatePositions(n);
	for (int i = 0; i < n; ++i) {
		nodes.push_back(new GraphNode(i, position[i], radiusNode));
		maxID = std::max(maxID, i);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i < j && !inputs[i][j].empty()) {
				int id1 = i;
				int id2 = j;
				float weight = std::stof(inputs[i][j]);
				if (weight > 0) {
					addEdge(id1, id2, weight);
				}
				
			}
		}
	}

}
void Graph::loadFromFile() {
	const char* filterPatterns[1] = { "*.txt" };
	const char* filePath = tinyfd_openFileDialog(
		"Choose graph file", "", 1, filterPatterns, "Text files", 0);

	if (!filePath) {
		std::cout << "Don't choose any files." << std::endl;
		return;
	}

	std::ifstream infile(filePath);
	if (!infile.is_open()) {
		std::cout << "Don't open file: " << filePath << std::endl;
		return;
	}

	std::vector<std::vector<float>> weights;
	std::string line;

	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		std::vector<float> row;
		float w;
		while (iss >> w) {
			row.push_back(w);
		}
		if (!row.empty()) {
			weights.push_back(row);
		}
	}

	infile.close();

	int n = weights.size();
	if (n == 0 || weights[0].size() != n) {
		std::cout << "Invalid Matric (must be n x n)." << std::endl;
		return;
	}

	clear();

	setNumberOfVertices(n);
	calculatePositions(n); 

	for (int i = 0; i < n; ++i) {
		nodes.push_back(new GraphNode(i, position[i], radiusNode));
		maxID = std::max(maxID, i);
	}

	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i < j && weights[i][j] > 0) {
				addEdge(i, j, weights[i][j]);
			}
		}
	}

	std::cout << "Load file success: " << filePath << std::endl;
}
void Graph::DijkstraAnim(vector<RectButton*>& CodeBlocks, AnimationManager& animManager, int startID) {
	// Reset the Dijkstra algorithm
	clearIndicates();
	resetDijkstra();
	dijkstraHistory.clear();
	currentStep = 0;

	int n = nodes.size();
	cost[startID] = 0;
	path[startID].push_back(nodes[startID]->getNumber());

	
	

	for (int i = 0; i < n; ++i) {
		//Find node with min cost
		animManager.addAnimation(new Animation(0.1f, [&CodeBlocks, this] {
			CodeBlocks[1]->highlight();
			}));
		for (int j = 0; j < n; ++j) {
			if (!visited[j]) {
				animManager.addAnimation(new DijkstraCellHighlightAnim(j, 2, 0.3f, RED, [this]() {
					//currentStep++;
					}));
				//saveDijkstraState(j);
			}
		}
		animManager.addAnimation(new Animation(0.1f, [&CodeBlocks, this] {
			CodeBlocks[1]->unhighlight();
			}));
		int u = -1;
		float minCost = INF;
		for (int j = 0; j < n; ++j) {

			if (!visited[j]){
				if (cost[j] < minCost) {
					minCost = cost[j];
					u = j;
				}
			}
		}
		if (u == -1) {
			break;
		}
		//Highlight node u
		

		Animation* nodeU = new CircleHighLightAnim(nodes[u], 0.5f, RED, RAYWHITE, RED, [&CodeBlocks, u, this]() {
			CodeBlocks[2]->highlight();
			nodes[u]->indicateNode = "Current";
			nodes[u]->animation->reset();
			nodes[u]->noDraw = false;
			currentStep++; 
			});
		saveDijkstraState(u);
		
		animManager.addAnimation(new DijkstraCellHighlightAnim(u, 2, 0.3f, RED));
		animManager.addAnimation(nodeU);

		Animation* CellU = new DijkstraCellHighlightAnim(u, 1, 0.3f, RED, [&CodeBlocks, this]() {
			CodeBlocks[2]->unhighlight();
			CodeBlocks[3]->highlight();
			currentStep++;
			});
		
		saveDijkstraState(u);
		animManager.addAnimation(CellU);

		//saveDijkstraState(u);
		//animManager.addAnimation(new DijkstraCellHighlightAnim(u, 1, 0.3f, RED));
		visited[u] = true;
		// Mark visited
		/*
		animManager.addAnimation(new Animation(0.5f, [&CodeBlocks, this]() {
			CodeBlocks[2]->unhighlight();
			CodeBlocks[3]->highlight();
			}));
		*/
			
		animManager.addAnimation(new Animation(0.1f, [&CodeBlocks, this]() {
			CodeBlocks[3]->unhighlight();
			}));
		
		
		// Traverse all neighbors
		for (auto& edge : edges) {
			
			int v = -1;
			float weight = edge->weight;

			if (edge->from == nodes[u]) {
				for (int k = 0; k < n; ++k) {
					if (nodes[k] == edge->to) {
						v = k;
						break;
					}
				}
			}
			else if (edge->to == nodes[u]) {
				for (int k = 0; k < n; ++k) {
					if (nodes[k] == edge->from) {
						v = k;
						break;
					}
				}
			}
			
			if (v != -1 && !visited[v]) {
			
				//highlight edge u-v
				
				animManager.addAnimation(new GEdgeHighlightAnim(edge, 0.75f, RED, [&CodeBlocks, v, this]() {
					
					
					nodes[v]->indicateNode = "v";
					nodes[v]->animation->reset();
					nodes[v]->noDraw = false;
					currentStep++;
				
					}));
				saveDijkstraState(v);
				

				animManager.addAnimation(new DijkstraCellHighlightAnim(u, 2, 0.3f, RED, [&CodeBlocks, this]() {
					CodeBlocks[4]->highlight();
					//currentStep++;
					}));
				//saveDijkstraState(u);
		
				animManager.addAnimation(new DijkstraCellHighlightAnim(v, 2, 0.3f, RED, [this]() {
					//currentStep++;
					}));
				//saveDijkstraState(v);
				

				//animManager.addAnimation(new GEdgeHighlightAnim(edge, 0.5f, RED));
				//animManager.addAnimation(new GEdgeHighlightAnim(edge, 1));
				//EdgeOfGraph::addEdgeAndAnim(animManager, edges, nodes[u], nodes[v]);
				//edges.back()->noDraw = true;
				/*
				animManager.addAnimation(new Animation(0.5f, [&CodeBlocks, this]() {
					
					CodeBlocks[4]->highlight();
					}));
					*/

				if (cost[u] + weight < cost[v]) {
					
					cost[v] = cost[u] + weight;
					path[v] = path[u];
					path[v].push_back(nodes[v]->getNumber());
					
					
					

				}

				// Unhighlight edge + node v
				
				animManager.addAnimation(new Animation(0.1f, [&CodeBlocks, v, this]() {
					CodeBlocks[4]->unhighlight(); 
					nodes[v]->indicateNode = "";
					
					}));
				//edge->setEdgeColor(RED);
				
			}
			// Reset ColorEdge
			animManager.addAnimation(new Animation(0.1f, [edge]() {
				edge->setEdgeColor(BLACK); 
				}));

		}
		animManager.addAnimation(new CircleHighLightAnim(nodes[u], 0.5f, GREEN, RAYWHITE, GREEN, [u, this]() {
			nodes[u]->indicateNode = "Visited";
			currentStep++;
			}));
		saveDijkstraState(u);
		/*
		animManager.addAnimation(new Animation(0.1f, [u, this]() {
			nodes[u]->indicateNode = "";
			
			}));
			*/
		/*
		animManager.addAnimation(new CircleHighLightAnim(nodes[u], 0.5f, GREEN, RAYWHITE, GREEN, [u, this]() {
			nodes[u]->indicateNode = "Visited";
			currentStep++;
			}));
		saveDijkstraState(u);
		*/
	}
	
	
}
void Graph::Dijkstra(int startID) {
	resetDijkstra();
	int n = nodes.size();
	
	cost[startID] = 0;
	path[startID].push_back(nodes[startID]->getNumber());

	for (int i = 0; i < n; ++i) {
		//Find node with min cost
		int u = -1;
		float minCost = INF;
		for (int j = 0; j < n; ++j) {
			if (!visited[j] && cost[j] < minCost) {
				minCost = cost[j];
				u = j;
			}
		}
		if (u == -1) break;
		visited[u] = true;

		//traversal all edges from u
		for (auto& edge : edges) {
			int v = -1;
			float weight = edge->weight;

			if (edge->from == nodes[u]) {
				for (int k = 0; k < n; ++k) {
					if (nodes[k] == edge->to) {
						v = k;
						break;
					}
				}
			}
			else if (edge->to == nodes[u]) {
				for (int k = 0; k < n; ++k) {
					if (nodes[k] == edge->from) {
						v = k;
						break;
					}
				}
			}
			if (v != -1 && !visited[v]) {
				if (cost[u] + weight < cost[v]) {
					cost[v] = cost[u] + weight;
					path[v] = path[u];
					path[v].push_back(nodes[v]->getNumber());
				}
			}
		}
	}


}

void Graph::drawDijkstraTable(int current) {
	//if (drawDijk && !dijkstraHistory.empty()) 
	if (drawDijk && !dijkstraHistory.empty())
	{
		//std::cout << "[Draw] Drawing Step: " << currentStep << std::endl;
		if (current >= dijkstraHistory.size()) {
			current = dijkstraHistory.size() - 1; 
		}
		const DijkstraState& state = dijkstraHistory[current];

		int n = state.cost.size();
		const float cellWidth = 100;
		const float cellHeight = 40;
		const float tableWidth = cellWidth * 4;
		const float tableHeight = cellHeight * (n + 1);

		float startX = 150.0f;
		float startY = 10.0f;

		Font font = GetFontDefault();
		int fontSize = 20;
		//header
		std::vector<std::string> headers = { "Vertex", "Known", "Cost", "Path" };
		for (int col = 0; col < 4; ++col) {
			float x = startX + col * cellWidth;
			DrawRectangleLinesEx({ x, startY, cellWidth, cellHeight }, 2, BLACK);
			Vector2 size = MeasureTextEx(font, headers[col].c_str(), fontSize, 1);
			DrawText(headers[col].c_str(), x + (cellWidth - size.x) / 2, startY + (cellHeight - size.y) / 2, fontSize, BLACK);
		}

		//rows
		for (int i = 0; i < n; ++i) {
			float rowY = startY + (i + 1) * cellHeight;
			Color textColor = (i == state.current ? BLACK : BLACK);
			// Column: Vertex
			{
				std::string txt = std::to_string(i);
				float x = startX;
				DrawRectangleLinesEx({ x, rowY, cellWidth, cellHeight }, 1, BLUE);
				DrawText(txt.c_str(), x + 40, rowY + 10, fontSize, BLUE);
			}

			// Column: Known (visited)
			{
				std::string txt = state.visited[i] ? "T" : "F";
				float x = startX + cellWidth;
				DrawRectangleLinesEx({ x, rowY, cellWidth, cellHeight }, 1, DARKGRAY);
				DrawText(txt.c_str(), x + 40, rowY + 10, fontSize, textColor);
			}

			// Column: Cost
			{
				std::string txt = (state.cost[i] >= INF) ? "INF" : std::to_string((int)state.cost[i]);
				float x = startX + 2 * cellWidth;
				DrawRectangleLinesEx({ x, rowY, cellWidth, cellHeight }, 2, RED);
				DrawText(txt.c_str(), x + 30, rowY + 10, fontSize, textColor);
			}

			// Column: Parent (last node before current)
			{
				std::string txt = "-1";
				if (!state.path[i].empty() && state.path[i].size() > 1) {
					txt = std::to_string((int)state.path[i][state.path[i].size() - 2]);
				}
				else if (!state.path[i].empty()) {
					txt = "-1";
				}
				float x = startX + 3 * cellWidth;
				DrawRectangleLinesEx({ x, rowY, cellWidth, cellHeight }, 1, DARKGRAY);
				DrawText(txt.c_str(), x + 30, rowY + 10, fontSize, textColor);
			}
			// Draw full path string on the right

			{
				std::string fullPathStr;
				for (int j = 0; j < state.path[i].size(); ++j) {
					fullPathStr += std::to_string((int)state.path[i][j]);
					if (j != state.path[i].size() - 1) fullPathStr += " ";
				}
				float x = startX + 4 * cellWidth + 20;
				DrawText(fullPathStr.c_str(), x, rowY + 10, fontSize, BLACK);
			}
		}
		DrawRectangleLines(startX - 2, startY - 2, tableWidth + 4, tableHeight + 4, GRAY);
	}
}
void Graph::snapshot(int current) {
	saveDijkstraState(current);
	currentStep++;
	//currentStep = (int)dijkstraHistory.size() - 1;
}
void Graph::saveDijkstraState(int current) {
	DijkstraState state;

	state.cost = std::vector<float>(cost.begin(), cost.end());
	state.visited = std::vector<bool>(visited.begin(), visited.end());
	state.path.resize(path.size());

	for (size_t i = 0; i < path.size(); ++i) {
		state.path[i] = std::vector<float>(path[i].begin(), path[i].end());
	}

	state.current = current;

	dijkstraHistory.push_back(state);

	std::cout << "[Snapshot] Step " << dijkstraHistory.size() - 1 << ": ";
	for (size_t i = 0; i < state.visited.size(); ++i) {
		if (state.visited[i])
			std::cout << "T ";
		else
			std::cout << "F ";
	}
	std::cout << "| Current: " << current << std::endl;
}
void Graph::clearIndicates() {
	for (auto& node : nodes) {
		node->indicateNode = "";
	}
}
void Graph::printPosition() {
	for (Vector2 pos : position) {
		cout << pos.x << " " << pos.y << endl;
	}
}
void Graph::printEdge() {
	printGraph();
}
void Graph::clear() {
	for (GraphNode* node : nodes) {
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