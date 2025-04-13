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
    bool FunctionActivated;
	Animation() : duration(0), elapsed(0), completed(false), FunctionActivated(false){};
    Animation(float dur) : duration(dur), elapsed(0), completed(false),Function(nullptr), FunctionActivated(false) {};
	Animation(float dur, std::function<void()> func) : duration(dur), elapsed(0), completed(false), Function(func), FunctionActivated(false) {};
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
	virtual void resetColor() {};
    //clamp elapsed to duration
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
    CBEdgeHighLightAnim( CBEdge* e, float duration,Color eC = ORANGE, std::function<void()> func = nullptr)
		: Animation(duration,func),endC(eC), edge(e) 
    {
        startC = e->edgeColor;
	}
	void resetColor() override{
		edge->edgeColor = startC;
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

class CircleRemoveAnim : public Animation {
private:
    CircleButton* button;
    float startRadius;
    float endRadius;
public:
    CircleRemoveAnim(CircleButton* btn, float duration) : button(btn), Animation(duration) {
        startRadius = btn->getRadius();
        endRadius = 0;
    };
    void applyState() override;
};
// HighLight Circle Button
class CircleHighLightAnim : public Animation {
protected:
    CircleButton* button;
    Color startTC, endTC;
    Color startFC, endFC;
    Color startRC, endRC;
public:
    
    virtual ~CircleHighLightAnim() = default;

    // default color is orange
    CircleHighLightAnim(
        CircleButton* btn, float duration,
        Color eTC = ORANGE, 
        Color eFC = RAYWHITE, 
        Color eRC = ORANGE, std::function<void()> func = nullptr
        )
        : Animation(duration,func),
        endTC(eTC), endFC(eFC), endRC(eRC), button(btn) {
        startTC = btn->OgTextColor;
        startFC = btn->OgFillColor;
        startRC = btn->OgOutLineColor;
    }
    void resetColor() override{
		button->OgTextColor = startTC;
		button->OgFillColor = startFC;
		button->OgOutLineColor = startRC;
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
    CircleMoveAnim(CircleButton* btn, float duration, std::function<void()> func = nullptr)
        : Animation(duration,func), button(btn) {
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
    CircleMoveXAnim(CircleButton* btn, float duration, float sX, std::function<void()> func = nullptr)
        : Animation(duration,func), startX(sX), button(btn) {
        endX = btn->getCenterX();
    }
	// Constructor with start and end positions
	// sX is the start x position
	// eX is the end x position

    CircleMoveXAnim(CircleButton* btn, float duration, float sX, float eX, std::function<void()> func = nullptr)
        : Animation(duration,func), startX(sX), endX(eX), button(btn) {
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

class RectHighlightAnim : public Animation {
public:
    NumberInputBox* button;
    Color startFill, endFill;
    Color startOutline, endOutline;
    Color startText, endText;
    RectHighlightAnim(NumberInputBox*, float, Color, Color, Color);
    void applyState() override;
    void resetColor() override;
};

class TreapEdgeHighlightAnim : public Animation {
public:
    TreapEdge* edge;
    Color start, end;
    TreapEdgeHighlightAnim(TreapEdge* e, float duration, Color ec = ORANGE) : Animation(duration), edge(e), start(edge->edgeColor), end(ec) {}
    void applyState() override;
    void resetColor() override;
};

#include "Treap.h" // Add this include to resolve the incomplete type error
class TreapNodeMoveAnim : public Animation {
public:
    TreapNode* node;
    Vector2 startPos;
    Vector2 endPos;
    TreapNodeMoveAnim(TreapNode* n, float duration, Vector2 sp, Vector2 ep) : Animation(duration), node(n), startPos(sp), endPos(ep){}
    void applyState() override;
    void handleReposition() override;
};

