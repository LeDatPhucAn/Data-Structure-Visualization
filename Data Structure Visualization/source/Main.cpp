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
	SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	SetTargetFPS(60);
	UI ui;
	ui.initTextures();
	SceneHandler scenehandler;
	
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
		


		scenehandler.displayCurrentScene();
        EndDrawing();
		//----------------------------------------------------------------------------------
		
	}
	CloseWindow();
	ui.cleanup();
}



//
//
////Test for graph
//#include <iostream>
//#include "../header/Graph.h"
//int main() {
//	Graph* graph = new Graph();
//    Vector2 pos1 = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    Vector2 pos2 = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    Vector2 pos3 = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    Vector2 pos4 = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    Vector2 pos5 = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    Vector2 pos6 = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//
//    graph->addNode(pos1);
//    graph->addNode(pos2);
//    graph->addNode(pos3);
//    graph->addNode(pos4);
//    graph->addNode(pos5);
//    graph->addEdge(1, 2);
//    graph->addEdge(2, 3);
//    graph->removeNode(1);
//    graph->addNode(pos6);
//    graph->addEdge(1, 5);
//    graph->removeEdge(5, 1);
//    graph->printGraph();
//    graph->printPosition();
//    graph->printEdge();
//
//    /*graph.addEdge(1, 2);
//    graph.addEdge(1, 3);
//    graph.addEdge(2, 4);
//    graph.addEdge(3, 5);
//    graph.printGraph();
//    graph.printPosition();*/
//    /*graph.calculatePositions();
//    graph.printPosition();*/
//
//    /*Vector2 pos = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    graph.addNode(pos);
//    graph.printGraph();
//    graph.printPosition();
//
//    graph.addEdge(1, 4);
//    graph.addEdge(3, 6);
//    graph.printGraph();
//    graph.printPosition();
//
//    graph.removeNode(1);
//    graph.printGraph();
//    graph.printPosition();
//    
//    Vector2 pos2 = { GetRandomValue(100, 1500), GetRandomValue(100, 800) };
//    graph.addNode(pos2);
//    graph.printGraph();
//    graph.printPosition();*/
//
//    /*graph.removeEdge(2, 4);
//    graph.printGraph();
//    graph.printPosition();*/
//
//
//}