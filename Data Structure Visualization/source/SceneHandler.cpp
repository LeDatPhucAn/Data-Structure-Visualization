#include "../header/SceneHandler.h"


SceneHandler::SceneHandler() {
    camera.zoom = 1.0f;
    scenes[MENU] = new Menu(this);
    scenes[LINKEDLIST] = new SinglyLinkedListUI(this);
    scenes[HASHTABLE] = new HashTableUI();
    scenes[TREAP] = new TreapUI();
    scenes[GRAPH] = new GraphUI();
    // Initialize other scenes as needed
    currentSceneObject = scenes[MENU];
}

SceneHandler::~SceneHandler() {
    for (int i = 0; i < 5; ++i) {
        delete scenes[i];
    }
}

int SceneHandler::getCurrentScene() {
    return currentSceneObject->CurrentScene;
}

void SceneHandler::changeScene(Scene newScene) {
    currentSceneObject = scenes[newScene];
    if (currentSceneObject) {
        currentSceneObject->CurrentScene = newScene;
    }
}

void SceneHandler::drawButtontoMenu(float X, float Y) {
    BacktoMenu.x = X;
    BacktoMenu.y = Y;
    float roundness = 0.5f;
    float segments = 10.0f;
    float lineThick = 12.0f;
    Rectangle rec2 = { BacktoMenu.x + BacktoMenu.width, BacktoMenu.y + BacktoMenu.height / 2, (float)BacktoMenu.width, (float)BacktoMenu.height };

    DrawRectangleRounded(BacktoMenu, roundness, (int)segments, Fade(BacktoMenuColor, 0.6f));
    DrawRectangleRoundedLinesEx(BacktoMenu, roundness, (int)segments, lineThick, Fade(BacktoMenuColor, 0.8f));
    DrawTexturePro(Icons[0], { 0,0,(float)Icons[0].width,(float)Icons[0].height }, rec2, { 0,(float)Icons[0].height / 2 }, 180, WHITE);
}

void SceneHandler::updateCurrentScene() {
    if (currentSceneObject) {
        if (getCurrentScene() != MENU) {
            float width = 200.0f;
            float height = 100.0f;
            BacktoMenu = { 20, 20, (float)width, (float)height };

            // Translate based on mouse right click
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f / camera.zoom);
                camera.target = Vector2Add(camera.target, delta);
            }

            // Zoom based on mouse wheel
            float wheel = GetMouseWheelMove();
            if (wheel != 0) {
                // Get the world point that is under the mouse
                Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                // Set the offset to where the mouse is
                camera.offset = GetMousePosition();

                // Set the target to match, so that the camera maps the world space point 
                // under the cursor to the screen space point under the cursor at any zoom
                camera.target = mouseWorldPos;

                // Zoom increment
                float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
                if (wheel < 0) scaleFactor = 1.0f / scaleFactor;

                // limit the values of zoom
                camera.zoom = Clamp(camera.zoom * scaleFactor, 0.25f, 10.0f);
            }

            // go back to menu
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, BacktoMenu)) {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    changeScene(MENU);
                }
                BacktoMenuColor = BLUE;
            }
            else BacktoMenuColor = LIGHTGRAY;
        }
        currentSceneObject->updateScene();
    }
}

void SceneHandler::displayCurrentScene() {
    if (currentSceneObject) {
        //apply camera to data structures
        if (getCurrentScene() != MENU) {
            BeginMode2D(camera);
            // Draw the 3d grid, rotated 90 degrees and centered around 0,0 
            // just so we have something in the XY plane
            rlPushMatrix();
            rlTranslatef(0, 10000, 0);
            rlRotatef(90, 1, 0, 0);
            DrawGrid(1000, 100);
            rlPopMatrix();

            // Draw a reference circle
            DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);
            currentSceneObject->displayScene();
            EndMode2D();

            // draw things that stay permanent on screen
            drawButtontoMenu(20, 20);
        }


        else currentSceneObject->displayScene();
    }
}
