#include "../header/SceneHandler.h"

Button* SceneHandler::MenuButton = nullptr;

SceneHandler::SceneHandler() {

    // initialize menu button
    MenuButton = new TextBox("Menu", UI::screenWidth / 100, UI::screenHeight / 100);
    MenuButton->onClick = [this]() {
        this->changeScene(MENU);
        };

    camera.zoom = 1.0f;
    UI::screenWidth = GetScreenWidth();
    UI::screenHeight = GetScreenHeight();
    scenes[MENU] = new Menu(this);

    scenes[LINKEDLIST] = new SinglyLinkedListUI(this);
    scenes[HASHTABLE] = new HashTableUI(this);
    scenes[TREAP] = new TreapUI(this);
    scenes[GRAPH] = new GraphUI(this);

    // Initialize other scenes as needed
    changeScene(MENU);
}

SceneHandler::~SceneHandler() {
    for (int i = 0; i < 5; ++i) {
        delete scenes[i];
    }
    delete MenuButton;
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

void SceneHandler::updateCamera() {

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
}


void SceneHandler::updateCurrentScene() {
    if (currentSceneObject) {

        // update The Positions of all Scenes when there is a Window Resize
        if (UI::lastScreenWidth != UI::screenWidth || UI::lastScreenHeight != UI::screenHeight) {

            for (int i = 1; i < 5; i++) {
                scenes[i]->updateButtonPositions();
            }

            UI::lastScreenWidth = UI::screenWidth;
            UI::lastScreenHeight = UI::screenHeight;
        }

        
        if (getCurrentScene() != MENU) {

            updateCamera();
        
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
            currentSceneObject->displaySceneInCamera();
            EndMode2D();

            
        }
        else {
            UI::drawBackground();

            UI::drawLogo();
        }


        // display permanent objects
        currentSceneObject->displayScene();
    }

    // Draw mouse reference
    DrawCircleV(GetMousePosition(), 4, DARKGRAY);
    DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
    Vector2Add(GetMousePosition(), { -44, -24 }), 20, 2, BLACK);
}
