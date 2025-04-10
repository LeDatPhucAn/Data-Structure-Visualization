#pragma once
#include "reasings.h"
#include "SceneManager.h"
#include "Button.h"
class Animation {
protected:


public:
    float duration;
    float elapsed;
    bool completed;
    std::function<void()> Function;
	Animation() : duration(0), elapsed(0), completed(false) {};
    Animation(float dur) : duration(dur), elapsed(0), completed(false),Function(nullptr) {};
	Animation(float dur, std::function<void()> func) : duration(dur), elapsed(0), completed(false), Function(func) {};
    virtual ~Animation() = default;
    virtual void handleReposition() {};
    virtual void update(float deltaTime);
    virtual void applyState() {};
    virtual bool isCompleted() {
        return completed;
    }
    virtual void reset() {
        elapsed = 0.0f;
        completed = false;

    }
	virtual void makeComplete() {
		elapsed = duration;
		completed = true;
	}
    virtual float getProgress() const {
        return elapsed;
    }
    virtual void clamp();
    // Set the animation to a specific time and apply the state immediately
    virtual void setTime(float t);
};

// HighLight CircleButton Edge
class CBEdgeHighLightAnim : public Animation {
protected:
	CBEdge* edge;
	Color startC, endC;
public:
	virtual ~CBEdgeHighLightAnim() = default;

    // default color is orange
    CBEdgeHighLightAnim( CBEdge* e, float duration,Color eC = ORANGE)
		: Animation(duration),endC(eC), edge(e) 
    {
        startC = e->edgeColor;
	}
	void applyState() override;
};
class CBEdgeAddAnim : public Animation {
protected:
	CBEdge* edge;
    int startT, endT;
public:
	virtual ~CBEdgeAddAnim() = default;

    // default color is orange
    CBEdgeAddAnim(CBEdge* e, float duration)
		: Animation(duration) {
		edge = e;
		startT = 0;
		endT = e->thickness;
	}
	void applyState() override;
};
class CBEdgeRemoveAnim : public Animation {
protected:
	CBEdge* edge;
    int startT, endT;
public:
	virtual ~CBEdgeRemoveAnim() = default;

    // default color is orange
    CBEdgeRemoveAnim(CBEdge* e, float duration)
		: Animation(duration) {
		edge = e;
		startT = e->thickness;
		endT = 0;
	}
	void applyState() override;
};

// HighLight Circle Button
class CircleHighLightAnim : public Animation {
protected:
    CircleButton* button;
    Color startTC,endTC;
    Color startFC,endFC;
    Color startRC,endRC;
public:
    virtual ~CircleHighLightAnim() = default;

    // default color is orange
    CircleHighLightAnim(
        CircleButton* btn, float duration,
        Color eTC = ORANGE, 
        Color eFC = RAYWHITE, 
        Color eRC = ORANGE
        )
        : Animation(duration),
        endTC(eTC), endFC(eFC), endRC(eRC), button(btn) {
        startTC = btn->OgTextColor;
        startFC = btn->OgFillColor;
        startRC = btn->OgOutLineColor;
    }
    void applyState() override;
};

// Move CircleButton in both x and y directions
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

    // Constructor with start positions
    // sX is the start x position
    // sY is the start y position
	// the ending position is the original center of the circle (or circle position)
    CircleMoveAnim(CircleButton* btn, float duration, float sX, float sY)
        : Animation(duration), startX(sX), startY(sY), button(btn) {
        endX = btn->getCenterX();
        endY = btn->getCenterY();
    }

	// Constructor with start and end positions
	// sX is the start x position
	// sY is the start y position
	// eX is the end x position
	// eY is the end y position
    CircleMoveAnim(CircleButton* btn, float duration, float sX, float sY, float eX, float eY)
        : Animation(duration), startX(sX), startY(sY), endX(eX), endY(eY), button(btn) {
    }
    void handleReposition() override {
        endX = button->getCenterX();
        endY = button->getCenterY();
    }
    void applyState() override;
};

// Move CircleButton in x direction
class CircleMoveXAnim : public Animation {
private:
    
protected:
    CircleButton* button;
    float startX;
    float endX;
public:
	virtual ~CircleMoveXAnim() = default;
    CircleMoveXAnim(CircleButton* btn, float duration)
        : Animation(duration), button(btn) {
        startX = 0;
        endX = btn->getCenterX();
    }
	// Constructor with start position
	// sX is the start x position
	// the ending position is the original center of the circle (or circle position)
    CircleMoveXAnim(CircleButton* btn, float duration, float sX)
        : Animation(duration), startX(sX), button(btn) {
        endX = btn->getCenterX();
    }
	// Constructor with start and end positions
	// sX is the start x position
	// eX is the end x position

    CircleMoveXAnim(CircleButton* btn, float duration, float sX, float eX)
        : Animation(duration), startX(sX), endX(eX), button(btn) {
    }
    void handleReposition() override{
        endX = button->getCenterX();
    }
    void applyState() override;
};

// Move RectButton in both x and y directions
class RectMoveAnim : public Animation {
private:
    
protected:
    RectButton* button;
    float startX, startY;
    float endX, endY;
public:

    void handleReposition() override {
        endX = button->rect.x;
        endY = button->rect.y;
    }
	virtual ~RectMoveAnim() = default;


    RectMoveAnim(RectButton* btn, float duration)
        : Animation(duration), button(btn) {
        startX = 0;
        startY = 0;
        endX = btn->rect.x;
        endY = btn->rect.y;
    }
	// Constructor with start position
	// sX is the start x position
	// sY is the start y position
	// the ending position is the original rect position
    RectMoveAnim(RectButton* btn, float sX, float sY, float duration)
        : Animation(duration), startX(sX), startY(sY), button(btn) {
        endX = btn->rect.x;
        endY = btn->rect.y;
    }
    void applyState() override;
};

// Move RectButton in x direction
class RectMoveXAnim : public RectMoveAnim {
public:
    RectMoveXAnim(RectButton* btn, float duration) : RectMoveAnim(btn, duration) {};
	// Constructor with start position
	// sX is the start x position
	// the ending position is the original rect position
    RectMoveXAnim(RectButton* btn, float sX, float duration) : RectMoveAnim(btn, sX, 0, duration) {};
    void applyState() override;
};

// Move RectButton in y direction
class RectMoveYAnim : public RectMoveAnim {
public:
    RectMoveYAnim(RectButton* btn, float duration) : RectMoveAnim(btn, duration) {};

	// Constructor with start position
	// sY is the start y position
	// the ending position is the original rect position
    RectMoveYAnim(RectButton* btn, float sY, float duration) : RectMoveAnim(btn, 0, sY, duration) {};
    void applyState() override;
};

// Make CircleButton grow from 0 to its original size
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
    void applyState() override;
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
    void applyState() override;
};



