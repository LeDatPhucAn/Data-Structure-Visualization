#pragma once
#include "reasings.h"
#include "SceneManager.h"
#include "Button.h"
class Animation {
protected:
    float duration;
    float elapsed;
    bool completed;

public:
	Animation() : duration(0), elapsed(0), completed(false) {};
    Animation(float dur) : duration(dur), elapsed(0), completed(false) {};
    virtual ~Animation() = default;

    virtual void update(float deltaTime) = 0;
    bool isCompleted() {
        return completed;
    }
    void reset() {
		elapsed = 0.0f;
        completed = false;
    }
    float getProgress() const {
        return elapsed;
    }
    
};
class ButtonScaleAnimation : public Animation {
private:
    Button* button;
    float startWidth, startHeight;
    float endWidth, endHeight;
public:
    ButtonScaleAnimation(Button* btn, float duration)
        : Animation(duration), button(btn) {
        startWidth = 0;
        startHeight = 0;
        endWidth = btn->rect.width;
        endHeight = btn->rect.height;
    }
    void update(float deltaTime) override {
        if (completed) return;
        elapsed += deltaTime;
        float t = elapsed / duration;
        if (t >= 1.0f) { t = 1.0f; completed = true; }
        button->rect.width = EaseCubicIn(elapsed, startWidth, endWidth - startWidth, duration);
        button->rect.height = EaseCubicIn(elapsed, startHeight, endHeight - startHeight, duration);

    }
};
class ButtonMoveXAnimation : public Animation {
private:
    Button* button;
    float startX;
    float endX;
public:
    ButtonMoveXAnimation(Button* btn, float duration)
        : Animation(duration), button(btn) {
        startX = 0;
        endX = btn->rect.x;
    }
    ButtonMoveXAnimation(Button* btn, float sX, float duration)
        : Animation(duration), startX(sX), button(btn) {
        endX = btn->rect.x;
    }
    void update(float deltaTime) override {
        if (completed) return;
        elapsed += deltaTime;
        float t = elapsed / duration;
        if (t >= 1.0f) { t = 1.0f; completed = true; }
        button->rect.x = EaseBounceOut(elapsed, startX, endX - startX, duration);

    }
};
class ButtonMoveYAnimation : public Animation {
private:
    Button* button;
    float startY;
    float endY;
public:
    ButtonMoveYAnimation(Button* btn, float duration)
        : Animation(duration), button(btn) {
        startY = 0;
        endY = btn->rect.y;
    }
    ButtonMoveYAnimation(Button* btn, float sY, float duration)
        : Animation(duration), startY(sY), button(btn) {
        endY = btn->rect.y;
    }
    void update(float deltaTime) override {
        if (completed) return;
        elapsed += deltaTime;
        float t = elapsed / duration;
        if (t >= 1.0f) { t = 1.0f; completed = true; }
        button->rect.y = EaseBounceOut(elapsed, startY, endY - startY, duration);

    }
};
class AnimatedNode : public Node {
private:
    Color color;
    Color outlineColor;
    Color textColor;
    bool highlighted;

public:
    AnimatedNode(int val, Vector2 pos, float r) : Node(val,pos,r) {};

    void setPosition(Vector2 pos);
    void setHighlighted(bool highlight);

    Vector2 getPosition() const;
    int getValue() const;
    float getRadius() const;
};

class AnimatedEdge {
private:
    AnimatedNode* from;
    AnimatedNode* to;
    Color color;
    bool highlighted;
    bool directed;

public:
    AnimatedEdge(AnimatedNode* from, AnimatedNode* to,
        Color color = GRAY, bool directed = true);

    void setHighlighted(bool highlight);

    AnimatedNode* getSource();
    AnimatedNode* getTarget();
};



class AnimationManager : public SceneManager {
private:
    std::vector<std::unique_ptr<AnimatedNode>> nodes;
    std::vector<std::unique_ptr<AnimatedEdge>> edges;
    std::vector<std::unique_ptr<Animation>> animations;
    float speed;
    bool paused;
    Camera* camera;
    bool useCamera;

    // Utility functions
    Vector2 calculateCircularPosition(int totalNodes, int nodeIndex, float centerX, float centerY, float radius);
    void drawArrowHead(Vector2 start, Vector2 end, float length, float angle, Color color);
    void drawAnimationElements();

public:
    AnimationManager();

    // SceneComponent interface
    void init() override;
    void initButtons() override;
    void updateScene() override;
    void displayScene() override;
    void displaySceneInCamera() override;
    void updateButtonPositions() override;

    // Animation control
    void addAnimation(std::unique_ptr<Animation> animation);
    void clearAnimations();
    void setPaused(bool pause);
    void setSpeed(float newSpeed);
    bool isAnimating() const;
    void setCamera(Camera* cameraComponent);

    // Node management
    AnimatedNode* createNode(int value, Vector2 position);
    void removeNode(AnimatedNode* node);
    AnimatedEdge* createEdge(AnimatedNode* from, AnimatedNode* to, bool directed = true);
    void removeEdge(AnimatedEdge* edge);

    // Circular linked list animations
    void setupCircularLinkedList(const std::vector<int>& values, float centerX, float centerY, float radius);
    void insertNodeToCLL(int value, int position = -1);
    void removeNodeFromCLL(int position);
    void highlightNodeAtPosition(int position, float duration = 0.5f);
    void animateTraversal(float duration = 0.5f);
    int searchValue(int value);
};

class NodeMoveAnimation : public Animation {
private:
    AnimatedNode* Node;
    Vector2 startPos;
    Vector2 endPos;

public:
    NodeMoveAnimation(AnimatedNode* node, Vector2 end, float duration) : Animation(duration), Node(node), endPos(end) {};
    void update(float deltaTime) override;
};

class NodeHighlightAnimation : public Animation {
private:
    AnimatedNode* node;
    Color highlightColor;

public:
    NodeHighlightAnimation(AnimatedNode* node, Color highlightColor, float duration);
    void update(float deltaTime) override;
};

class EdgeHighlightAnimation : public Animation {
private:
    AnimatedEdge* edge;
    Color highlightColor;

public:
    EdgeHighlightAnimation(AnimatedEdge* edge, Color highlightColor, float duration);
    void update(float deltaTime) override;
};