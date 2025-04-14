#include "../header/SceneHandler.h"
#include "../header/reasings.h"
#include "../header/Animation.h"
Vector2 SceneHandler::mouseWorldPos = { 0, 0 };
SceneHandler::SceneHandler() {

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

    // initialize Scene Buttons
    initButtons();
}

SceneHandler::~SceneHandler() {
    for (int i = 0; i < 5; ++i) {
        delete scenes[i];
    }
    Button::deleteButtons<Button>(SceneButtons);
}

void SceneHandler::initButtons() {

    // menu button 0
    Button* MenuButton = new TextBox("Menu", UI::screenWidth / 100, UI::screenHeight / 100);
    MenuButton->onClick = [this]() {
        this->changeScene(MENU);
        };
    MenuButton->animation = new RectMoveXAnim(dynamic_cast<RectButton*>(MenuButton), 0.5);
    SceneButtons.push_back(MenuButton);
    
	// Pause or play animations 1
    CircleButton* Pause = new PlayButton(this,UI::Icons[4], { (float)UI::screenWidth / 2 , (float)UI::screenHeight - 100 }, 60.0f);
    Pause->onClick = [this]() {
        if (!currentSceneObject->animManager.isPaused())currentSceneObject->animManager.pause();
        else currentSceneObject->animManager.resume();
        };
    SceneButtons.push_back(Pause);

    // go to the previous animation 2
    CircleButton* GoPrevious = new TextCircle("<",
        {
            Pause->getCenterX() - Pause->getRadius() - 55,
            Pause->getCenterY()
        },
        55.0f, BLACK, Pause->FillColor, Pause->OutLineColor);
    
    GoPrevious->onClick = [this]() {


        int step = currentSceneObject->animManager.getStep();
        cout << step << "\n";
        // complete the operation to get final state
        currentSceneObject->animManager.goToLastStep();
        currentSceneObject->clearIndicatesAndHighlights();

        // restore the initial state and get to the previous state
        currentSceneObject->replayOperation();
        if (step == -1)step++;
        currentSceneObject->animManager.goToStep(step - 1);
        };
    SceneButtons.push_back(GoPrevious);
    
    // go to the first animation 3
    CircleButton* GoFirst = new TextCircle("<<",
        {
            GoPrevious->getCenterX() - GoPrevious->getRadius() - 50,
            GoPrevious->getCenterY()
        },
        50, BLACK, Pause->FillColor, Pause->OutLineColor);
    GoFirst->onClick = [this]() {
        int step = currentSceneObject->animManager.getStep();

        // complete the operation to get final state
        currentSceneObject->animManager.goToLastStep();
        currentSceneObject->clearIndicatesAndHighlights();

        // restore the initial state and get to the previous state
        currentSceneObject->replayOperation();
        currentSceneObject->animManager.goToFirstStep();
        };
    SceneButtons.push_back(GoFirst);
	// go to the next animation 4
    CircleButton* GoNext = new TextCircle(">",
        {
            Pause->getCenterX() + Pause->getRadius() + 55,
            Pause->getCenterY()
        },
        55.0f, BLACK, Pause->FillColor, Pause->OutLineColor);
    
    GoNext->onClick = [this]() {
        currentSceneObject->clearIndicatesAndHighlights();
        cout<< currentSceneObject->animManager.getStep()<<"\n";
        currentSceneObject->animManager.goToNextStep();
        };
    SceneButtons.push_back(GoNext);
    // go to the last animation 5
    CircleButton* GoLast = new TextCircle(">>",
        {
            GoNext->getCenterX() + GoNext->getRadius() + 50,
            GoNext->getCenterY()
        },
        50, BLACK, Pause->FillColor, Pause->OutLineColor);
    GoLast->onClick = [this]() {
        currentSceneObject->clearIndicatesAndHighlights();
        currentSceneObject->animManager.goToLastStep();
        };
    SceneButtons.push_back(GoLast);
    
    

    // set speed                                     
    RectButton* SetSpeed = new ScrollyAndButton(
     GoLast->getCenterX() + 100,   // x position
      GoLast->getCenterY() - 10,   // y position
                            400,   // length
                             20,   // thickness
                             60,   // Moveable Button size
                           BLUE,   // Moveable Button color
                          WHITE,   // Scrolly's FillColor 
                          BLACK,   // Scrolly's outline color
                              1,   // current value
                           0.5f,   // Min value
                              2    // Max value
    );

    SceneButtons.push_back(SetSpeed);
    SetSpeed->animation = new RectMoveXAnim(SetSpeed, (float)UI::screenWidth, 0.5f);
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
    // Move camera with drag
    if (!Button::isClicking && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }

    // Handle zoom with scroll wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        SceneHandler::mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera); // update position
        camera.offset = GetMousePosition();
        camera.target = SceneHandler::mouseWorldPos;

        float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
        if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
        camera.zoom = Clamp(camera.zoom * scaleFactor, 0.25f, 10.0f);
    }

    // Always keep it up-to-date, even without zoom
    SceneHandler::mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
}



void SceneHandler::updateCurrentScene() {
    if (currentSceneObject) {

        if (getCurrentScene() != MENU) {
            updateCamera();  // <-- move this up here
        }

        // update font size
        // update The Positions of all Scenes when there is a Window Resize
        if (UI::lastScreenWidth != UI::screenWidth || UI::lastScreenHeight != UI::screenHeight) {
            
            //////// reposition 

            // Menu Button
            dynamic_cast<RectButton*>(SceneButtons[0])->setPosition(UI::screenWidth / 100, UI::screenHeight / 100);
            
            // Pause
            dynamic_cast<CircleButton*>(SceneButtons[1])->setCenter(
                (float)UI::screenWidth / 2,
                (float)UI::screenHeight - 100
            );

            // Go to Previous
			dynamic_cast<CircleButton*>(SceneButtons[2])->setCenter(
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterX() - dynamic_cast<CircleButton*>(SceneButtons[1])->getRadius() - 55,
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterY()
			);
            
            // Go to First
			dynamic_cast<CircleButton*>(SceneButtons[3])->setCenter(
                dynamic_cast<CircleButton*>(SceneButtons[2])->getCenterX() - dynamic_cast<CircleButton*>(SceneButtons[2])->getRadius() - 50,
                dynamic_cast<CircleButton*>(SceneButtons[2])->getCenterY()
			);

            // Go to Next
			dynamic_cast<CircleButton*>(SceneButtons[4])->setCenter(
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterX() + dynamic_cast<CircleButton*>(SceneButtons[1])->getRadius() + 55,
                dynamic_cast<CircleButton*>(SceneButtons[1])->getCenterY()
			);
            // Go to Last
			dynamic_cast<CircleButton*>(SceneButtons[5])->setCenter(
                dynamic_cast<CircleButton*>(SceneButtons[4])->getCenterX() + dynamic_cast<CircleButton*>(SceneButtons[4])->getRadius() + 50,
                dynamic_cast<CircleButton*>(SceneButtons[4])->getCenterY()
			);

            // Set Speed
            dynamic_cast<RectButton*>(SceneButtons[6])->setPosition(
                dynamic_cast<CircleButton*>(SceneButtons[5])->getCenterX()+100, 
                dynamic_cast<CircleButton*>(SceneButtons[5])->getCenterY()-10);
            

            // Animation resets
            dynamic_cast<RectButton*>(SceneButtons[6])->animation->handleReposition();

            Button::resetButtonsAnimations<Button>(SceneButtons);



            for (int i = 1; i < 5; i++) {
                scenes[i]->updateButtonPositions();
            }

            UI::lastScreenWidth = UI::screenWidth;
            UI::lastScreenHeight = UI::screenHeight;
        }

        Button::isCollision = false;
        Button::updateButtons<Button>(SceneButtons);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            Button::isClicking = false;
        }
        if (getCurrentScene() != MENU) {
            updateCamera();
            currentSceneObject->updateSceneInCamera(camera);

        }

        
        currentSceneObject->animManager.setSpeed(dynamic_cast<ScrollyAndButton*>(SceneButtons.back())->getValue());
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
