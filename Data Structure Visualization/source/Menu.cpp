#include "../header/Menu.h"
#include "../header/SceneHandler.h"
void Menu::updateScene() {
	sourceRec = { 0, 0, (float)Buttons[0].width, (float)Buttons[0].height };

	// Calculate the total width of all buttons and the spacing between them
    float totalWidth = Buttons[0].width * 4 + spacing * 3;

    // Calculate the starting x position to center the buttons
    float startX = (screenWidth - totalWidth) / 2.0f;

    // Set the positions of each button
    linkedlist = { startX,
                   (float)(screenHeight / 2.0f - Buttons[0].height / 2.0f),
                   (float)Buttons[0].width,
                   (float)Buttons[0].height };

    hashtable = { startX + Buttons[0].width + spacing,
                  linkedlist.y,
                  linkedlist.width,
                  linkedlist.height };

    treap = { startX + (Buttons[0].width + spacing) * 2,
              linkedlist.y,
              linkedlist.width,
              linkedlist.height };

    graph = { startX + (Buttons[0].width + spacing) * 3,
              linkedlist.y,
              linkedlist.width,
              linkedlist.height };

	rectangles[0] = linkedlist;
	rectangles[1] = hashtable;
	rectangles[2] = treap;
	rectangles[3] = graph;



    // clicking
	Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, linkedlist)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            sceneHandler->changeScene(LINKEDLIST);
        }
        selected = MENU_LINKEDLIST;
    }
    else if (CheckCollisionPointRec(mousePoint, hashtable)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            sceneHandler->changeScene(HASHTABLE);
        }
        selected = MENU_HASHTABLE;
    }
    else if (CheckCollisionPointRec(mousePoint, treap)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            sceneHandler->changeScene(TREAP);
        }
        selected = MENU_TREAP;
    }
    else if (CheckCollisionPointRec(mousePoint, graph)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            sceneHandler->changeScene(GRAPH);
        }
        selected = MENU_GRAPH;
    }
	else selected = NONE;
}

void Menu::displayScene() {
	for(int i = 0 ; i < 4; i++){

		if (selected == i) {
			DrawTextureRec(selectedButtons[i], sourceRec, {rectangles[i].x, rectangles[i].y}, WHITE);
		}
		else DrawTextureRec(Buttons[i], sourceRec, { rectangles[i].x, rectangles[i].y }, WHITE);
	}
}