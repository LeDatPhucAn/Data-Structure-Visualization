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

class CircleMoveAnim : public Animation {
private:
    
protected:
    CircleButton* button;
    float startX, startY;
    float endX, endY;
public:
	virtual ~CircleMoveAnim() = default;
    CircleMoveAnim(CircleButton* btn, float duration)
        : Animation(duration), button(btn) {
        startX = 0;
        startY = 0;
        endX = btn->getCenterX();
        endY = btn->getCenterY();
    }
    CircleMoveAnim(CircleButton* btn, float sX, float sY, float duration)
        : Animation(duration), startX(sX), startY(sY), button(btn) {
        endX = btn->getCenterX();
        endY = btn->getCenterY();
    }
    CircleMoveAnim(CircleButton* btn, float sX, float sY, float eX, float eY, float duration)
        : Animation(duration), startX(sX), startY(sY), endX(eX), endY(eY), button(btn) {
    }
    
    void update(float deltaTime) override;
};
class CircleMoveAnimInCamera : public Animation {
private:
    
protected:
    CircleButton* button;
    float startX, startY;
    float endX, endY;
public:
	virtual ~CircleMoveAnimInCamera() = default;
    CircleMoveAnimInCamera(CircleButton* btn, float duration)
        : Animation(duration), button(btn) {
        startX = 0;
        startY = 0;
        endX = btn->getCenterX();
        endY = btn->getCenterY();
    }
    CircleMoveAnimInCamera(CircleButton* btn, float sX, float sY, float duration)
        : Animation(duration), startX(sX), startY(sY), button(btn) {
        endX = btn->getCenterX();
        endY = btn->getCenterY();
    }
    CircleMoveAnimInCamera(CircleButton* btn, float sX, float sY, float eX, float eY, float duration)
        : Animation(duration), startX(sX), startY(sY), endX(eX), endY(eY), button(btn) {
    }
    
    void update(float deltaTime) override;
};
class RectMoveAnim : public Animation {
private:
    
protected:
    RectButton* button;
    float startX, startY;
    float endX, endY;
public:

    virtual void HandleResize() override;
	virtual ~RectMoveAnim() = default;
    RectMoveAnim(RectButton* btn, float duration)
        : Animation(duration), button(btn) {
        startX = 0;
        startY = 0;
        endX = btn->rect.x;
        endY = btn->rect.y;
    }
    RectMoveAnim(RectButton* btn, float sX, float sY, float duration)
        : Animation(duration), startX(sX), startY(sY), button(btn) {
        endX = btn->rect.x;
        endY = btn->rect.y;
    }
    void update(float deltaTime) override;
};
class RectMoveXAnim : public RectMoveAnim {
public:
    RectMoveXAnim(RectButton* btn, float duration) : RectMoveAnim(btn, duration) {};
    RectMoveXAnim(RectButton* btn, float sX, float duration) : RectMoveAnim(btn, sX, 0, duration) {};
    void update(float deltaTime) override;
};
class RectMoveYAnim : public RectMoveAnim {
public:
    RectMoveYAnim(RectButton* btn, float duration) : RectMoveAnim(btn, duration) {};
    RectMoveYAnim(RectButton* btn, float sY, float duration) : RectMoveAnim(btn, 0, sY, duration) {};
    void update(float deltaTime) override;
};

class CircleInitializeAnim : public Animation {
private:
    CircleButton* button;
    float startRadius;
    float endRadius;
public:
    CircleInitializeAnim(CircleButton* btn, float duration) : button(btn), Animation(duration) {
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



class AnimationManager {
private:
    std::vector<Node*> Nodes;
    std::vector<Edge*> Edges;
    std::vector<Animation*> Animations;
    float speed;
    bool paused;

public:
    AnimationManager();

    // SceneComponent interface
    /*void init() override;
    void initButtons() override;
    void updateScene() override;
    void displayScene() override;
    void displaySceneInCamera() override;
    void updateButtonPositions() override;*/

    // Animation control
    void addAnimation(vector<Animation*> Animations);
    void clearAnimations();
    void setPaused(bool pause);
    void setSpeed(float newSpeed);
    bool isAnimating() const;


    void insertNodeToSLL(int value, int position = -1);
    void removeNodeFromSLL(int position);
    void highlightNodeAtPosition(int position, float duration = 0.5f);
    void animateTraversal(float duration = 0.5f);
    int searchValue(int value);
};
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