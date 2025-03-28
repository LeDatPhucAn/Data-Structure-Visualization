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

    virtual void Animate(float deltaTime);
    virtual void HandleResize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual bool isCompleted() {
        return completed;
    }
    virtual void reset() {
        elapsed = 0.0f;
        completed = false;

    }
    virtual float getProgress() const {
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
	void HandleResize() override {
		startWidth = 0;
		startHeight = 0;
		endWidth = button->rect.width;
		endHeight = button->rect.height;
	}
};

class ButtonMoveAnimation : public Animation {
private:
    
protected:
    Button* button;
    float startX, startY;
    float endX, endY;
public:

    virtual void HandleResize() override;
	virtual ~ButtonMoveAnimation() = default;
    ButtonMoveAnimation(Button* btn, float duration)
        : Animation(duration), button(btn) {
        startX = 0;
        startY = 0;
        endX = btn->rect.x;
        endY = btn->rect.y;
    }
    ButtonMoveAnimation(Button* btn, float sX, float sY, float duration)
        : Animation(duration), startX(sX), startY(sY), button(btn) {
        endX = btn->rect.x;
        endY = btn->rect.y;
    }
    void update(float deltaTime) override;
};
class ButtonMoveXAnimation : public ButtonMoveAnimation {
public:
    ButtonMoveXAnimation(Button* btn, float duration) : ButtonMoveAnimation(btn, duration) {};
	ButtonMoveXAnimation(Button* btn, float sX, float duration) : ButtonMoveAnimation(btn, sX, 0, duration) {};
    void update(float deltaTime) override;
};
class ButtonMoveYAnimation : public ButtonMoveAnimation {
public:
    ButtonMoveYAnimation(Button* btn, float duration) : ButtonMoveAnimation(btn, duration) {};
    ButtonMoveYAnimation(Button* btn, float sY, float duration) : ButtonMoveAnimation(btn, 0, sY, duration) {};
    void update(float deltaTime) override;
};

class CircleButtonInitializeAnimation : public Animation {
private:
    CircleButton* button;
    float startRadius;
    float endRadius;
public:
    CircleButtonInitializeAnimation(CircleButton* btn, float duration) : button(btn), Animation(duration) {
        startRadius = 0;
        endRadius = btn->getRadius();
    };
    void update(float deltaTime) override;
    void HandleResize() {};
};
class NodeInitializeAnimation : public Animation {
private:
	Node* node;
	float startRadius;
	float endRadius;
public:
	NodeInitializeAnimation(Node* n, float duration) : node(n), Animation(duration) {
		startRadius = 0;
        endRadius = node->radius;
    };
    void update(float deltaTime) override;
    void HandleResize() {};
};


//class AnimatedNode : public Node {
//private:
//    Color color;
//    Color outlineColor;
//    Color textColor;
//    bool highlighted;
//
//public:
//    AnimatedNode(Node n) : Node(n) {};
//    AnimatedNode(int val, Vector2 pos, float r) : Node(val,pos,r) {};
//
//    void setPosition(Vector2 pos);
//    void setHighlighted(bool highlight);
//
//    Vector2 getPosition() const;
//    int getValue() const;
//    float getRadius() const;
//};
//
//class AnimatedEdge {
//private:
//    AnimatedNode* from;
//    AnimatedNode* to;
//    Color color;
//    bool highlighted;
//    bool directed;
//
//public:
//    AnimatedEdge(AnimatedNode* from, AnimatedNode* to,
//        Color color = GRAY, bool directed = true);
//
//    void setHighlighted(bool highlight);
//
//    AnimatedNode* getSource();
//    AnimatedNode* getTarget();
//};



//class AnimationManager : public SceneManager {
//private:
//    std::vector<AnimatedNode*> Nodes;
//    std::vector<AnimatedEdge*> Edges;
//    std::vector<Animation*> Animations;
//    float speed;
//    bool paused;
//
//public:
//    AnimationManager();
//
//    // SceneComponent interface
//    void init() override;
//    void initButtons() override;
//    void updateScene() override;
//    void displayScene() override;
//    void displaySceneInCamera() override;
//    void updateButtonPositions() override;
//
//    // Animation control
//    void addAnimation(vector<Animation*> Animations);
//    void clearAnimations();
//    void setPaused(bool pause);
//    void setSpeed(float newSpeed);
//    bool isAnimating() const;
//
//    // Node management
//    AnimatedNode* createNode(int value, Vector2 position);
//    void removeNode(AnimatedNode* node);
//    AnimatedEdge* createEdge(AnimatedNode* from, AnimatedNode* to, bool directed = true);
//    void removeEdge(AnimatedEdge* edge);
//
//    // Circular linked list animations
//    void setupCircularLinkedList(const std::vector<int>& values, float centerX, float centerY, float radius);
//    void insertNodeToSLL(int value, int position = -1);
//    void removeNodeFromSLL(int position);
//    void highlightNodeAtPosition(int position, float duration = 0.5f);
//    void animateTraversal(float duration = 0.5f);
//    int searchValue(int value);
//};
//
//class NodeMoveAnimation : public Animation {
//private:
//    AnimatedNode* Node;
//    Vector2 startPos;
//    Vector2 endPos;
//
//public:
//    NodeMoveAnimation(AnimatedNode* node, Vector2 end, float duration) : Animation(duration), Node(node), endPos(end) {};
//    void update(float deltaTime) override;
//};
//
//class NodeHighlightAnimation : public Animation {
//private:
//    AnimatedNode* node;
//    Color highlightColor;
//
//public:
//    NodeHighlightAnimation(AnimatedNode* node, Color highlightColor, float duration);
//    void update(float deltaTime) override;
//};
//
//class EdgeHighlightAnimation : public Animation {
//private:
//    AnimatedEdge* edge;
//    Color highlightColor;
//
//public:
//    EdgeHighlightAnimation(AnimatedEdge* edge, Color highlightColor, float duration);
//    void update(float deltaTime) override;
//};
