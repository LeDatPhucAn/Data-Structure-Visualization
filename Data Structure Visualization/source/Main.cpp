// Data Structure Visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../header/Animation.h"
#include "../header/SinglyLinkedListUI.h"
#include "../header/TreapUI.h"
#include "../header/SceneHandler.h"
#include "../header/Button.h"
#include "../header/UI.h"
using namespace std;
int main()
{
	InitWindow(UI::screenWidth, UI::screenHeight, "Bruh");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	UI ui;
	ui.initTextures();
	SceneHandler scenehandler;
	Node* node1 = new Node(293, { 250, 250 }, 50);
	Node* node2 = new Node(201, { 400, 250 }, 50);

	Edge* edge1 = new Edge(node1, node2);
	/// main functions
	while (!WindowShouldClose()) {

		// Get screen values
		UI::screenWidth = GetScreenWidth();
		UI::screenHeight = GetScreenHeight();

		// Update
		//----------------------------------------------------------------------------------
		scenehandler.updateCurrentScene();

        //----------------------------------------------------------------------------------


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

		//Test
		/*UI::drawNode(node1);
		UI::drawNode(node2);
		edge1->drawArrowEdge();*/

		scenehandler.displayCurrentScene();
        EndDrawing();
		//----------------------------------------------------------------------------------
		
	}
	CloseWindow();
	ui.cleanup();
}




//
////Test for graph
//#include <iostream>
//#include "../header/Graph.h"
//int main() {
//	Graph graph(10);
//    graph.addEdge(1, 2);
//    graph.addEdge(1, 3);
//    graph.addEdge(2, 4);
//    graph.addEdge(3, 5);
//    graph.printGraph();
//
//    graph.calculatePositions();
//    graph.printPosition();
//
//    /*Vector2 pos = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    graph.addNode(pos);
//    graph.printGraph();
//    graph.addEdge(1, 4);
//    graph.addEdge(3, 6);
//    graph.printGraph();
//    graph.removeNode(1);
//    graph.printGraph();
//    graph.removeEdge(2, 4);
//    graph.printGraph();*/
//
//
//}