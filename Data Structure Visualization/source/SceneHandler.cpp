#include "../header/SceneHandler.h"
#include "../header/reasings.h"
#include "../header/Animation.h"
Vector2 SceneHandler::mouseWorldPos = GetMousePosition();
SceneHandler::SceneHandler() {

    // initialize Scene Buttons
    initButtons();


    camera.zoom = 1.0f;
    UI::screenWidth = GetScreenWidth();
    UI::screenHeight = GetScreenHeight();

    scenes[MENU] = new Menu(this);
    scenes[LINKEDLIST] = new SinglyLinkedListUI();
    scenes[HASHTABLE] = new HashTableUI();
    scenes[TREAP] = new TreapUI();
    scenes[GRAPH] = new GraphUI();

    // Initialize other scenes as needed
    changeScene(MENU);
}

SceneHandler::~SceneHandler() {
    for (int i = 0; i < 5; ++i) {
        delete scenes[i];
    }
    Button::deleteButtons<Button>(SceneButtons);
	Button::deleteButtons<RectButton>(rightSideButtons);
}

void SceneHandler::initButtons() {

    // menu button
    Button* MenuButton = new TextBox("Menu", UI::screenWidth / 100, UI::screenHeight / 100);
    MenuButton->onClick = [this]() {
        this->changeScene(MENU);
        };
    MenuButton->animation = new RectMoveXAnim(dynamic_cast<RectButton*>(MenuButton), 0.5);
    SceneButtons.push_back(MenuButton);
    
	// Pause animations
    CircleButton* Pause = new TextureCircle(UI::Icons[4], { (float)UI::screenWidth / 2 , (float)UI::screenHeight - 100 }, 60.0f);
    Pause->onClick = [this]() {
        if (!currentSceneObject->animManager.isPaused())currentSceneObject->animManager.pause();
        else currentSceneObject->animManager.resume();
        };
    SceneButtons.push_back(Pause);

    // go to the previous animation
    CircleButton* GoPrevious = new TextCircle("<",
        {
            Pause->getCenterX() - Pause->getRadius() - 55,
            Pause->getCenterY()
        },
        55.0f, BLACK, Pause->FillColor, Pause->OutLineColor);
    
    GoPrevious->onClick = [this]() {
        currentSceneObject->animManager.goToPrevious();
        };
    SceneButtons.push_back(GoPrevious);
    
	// go to the next animation
    CircleButton* GoNext = new TextCircle(">",
        {
            Pause->getCenterX() + Pause->getRadius() + 55,
            Pause->getCenterY()
        },
        55.0f, BLACK, Pause->FillColor, Pause->OutLineColor);
    
    GoNext->onClick = [this]() {
        currentSceneObject->animManager.goToNext();
        };
    SceneButtons.push_back(GoNext);

    // play forward
    RectButton* PlayForward = new TextBox("Play Forward", (float)UI::screenWidth * 3 / 4, (float)UI::screenHeight * 3 / 4);
    PlayForward->onClick = [this]() {
        currentSceneObject->animManager.playForward();
        };
	PlayForward->animation = new RectMoveXAnim(PlayForward, (float)UI::screenWidth, 0.5f);
    RectButton::insertHeadButton(rightSideButtons, PlayForward);

	// play backward
	RectButton* PlayBackward = new TextBox("Play Backward");
    PlayBackward->onClick = [this]() {
        currentSceneObject->animManager.playBackward();
        };
	RectButton::insertHeadButton(rightSideButtons, PlayBackward);
    PlayBackward->animation = new RectMoveXAnim(PlayBackward, (float)UI::screenWidth, 0.5f);


}
int SceneHandler::getCurrentScene() {
    return currentSceneObject->CurrentScene;
}

void SceneHandler::changeScene(Scene newScene) {
    Button::resetButtonsAnimations<Button>(SceneButtons);
    if (currentSceneObject) currentSceneObject->resetAnimations();
    currentSceneObject = scenes[newScene];
    currentSceneObject->CurrentScene = newScene;
    
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
        mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

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
    mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

}


void SceneHandler::updateCurrentScene() {
    if (currentSceneObject) {

        // update font size
        // update The Positions of all Scenes when there is a Window Resize
        if (UI::lastScreenWidth != UI::screenWidth || UI::lastScreenHeight != UI::screenHeight) {
            
            Button::resetButtonsAnimations<Button>(SceneButtons);
            dynamic_cast<RectButton*>(SceneButtons[0])->setPosition(UI::screenWidth / 100, UI::screenHeight / 100);
            dynamic_cast<CircleButton*>(SceneButtons[1])->setCenter(
                (float)UI::screenWidth / 2,
                (float)UI::screenHeight - 100
            );
			dynamic_cast<CircleButton*>(SceneButtons[2])->setCenter(
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterX() - dynamic_cast<CircleButton*>(SceneButtons[1])->getRadius() - 50,
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterY()
			);
			dynamic_cast<CircleButton*>(SceneButtons[3])->setCenter(
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterX() + dynamic_cast<CircleButton*>(SceneButtons[1])->getRadius() + 50,
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterY()
			);

            RectButton::setHeadPosition(rightSideButtons,(float)UI::screenWidth * 3 / 4, (float)UI::screenHeight * 3/4);
            Button::handleButtonsAnimReposition<RectButton>(rightSideButtons);
			Button::resetButtonsAnimations<RectButton>(rightSideButtons);

            for (int i = 1; i < 5; i++) {
                scenes[i]->updateButtonPositions();
            }

            UI::lastScreenWidth = UI::screenWidth;
            UI::lastScreenHeight = UI::screenHeight;
        }

        
        if (getCurrentScene() != MENU) {

            updateCamera();
            currentSceneObject->updateSceneInCamera(camera);

        }

        Button::isCollision = false;
        Button::updateButtons<Button>(SceneButtons);
		Button::updateButtons<RectButton>(rightSideButtons);

        currentSceneObject->animManager.update(GetFrameTime());
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
            currentSceneObject->displaySceneInCamera();

            EndMode2D();

            Button::drawButtons<Button>(SceneButtons);
			Button::drawButtons<RectButton>(rightSideButtons);
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
