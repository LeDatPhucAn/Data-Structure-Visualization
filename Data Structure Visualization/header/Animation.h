#pragma once
#include "reasings.h"
#include "SceneManager.h"
#include "Button.h"
#include <stack>
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
    virtual void reset();
    virtual void makeComplete();
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
class RemoveEdgeInAnim: public Animation {
private:
    
public:
    CircleButton* from;
    CircleButton* to;
    RemoveEdgeInAnim(float dur,CircleButton* fromPtr, CircleButton* toPtr, std::function<void()> func)
        : Animation(dur,func),  from(fromPtr), to(toPtr) {
    }

    void applyState() override {
        // No visual state to apply; the removal is structural
    }
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
    CircleMoveAnim(CircleButton* btn, float duration, float sX, float sY, float eX, float eY, std::function<void()> func = nullptr)
        : Animation(duration,func), startX(sX), startY(sY), endX(eX), endY(eY), button(btn) {
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
class CircleMoveYAnim : public Animation {
private:
    
protected:
    CircleButton* button;
    float startY;
    float endY;
public:
	virtual ~CircleMoveYAnim() = default;
    CircleMoveYAnim(CircleButton* btn, float duration)
        : Animation(duration), button(btn) {
        startY = 0;
        endY = btn->getCenterY();
    }
	// Constructor with start position
	// sY is the start y position
	// the ending position is the original center of the circle (or circle position)
    CircleMoveYAnim(CircleButton* btn, float duration, float sY, std::function<void()> func = nullptr)
        : Animation(duration,func), startY(sY), button(btn) {
        endY = btn->getCenterY();
    }
	// Constructor with start and end positions
	// sY is the start y position
	// eY is the end y position

    CircleMoveYAnim(CircleButton* btn, float duration, float sY, float eY, std::function<void()> func = nullptr)
        : Animation(duration,func), startY(sY), endY(eY), button(btn) {
    }
    void handleReposition() override{
        endY = button->getCenterY();
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
    RectHighlightAnim(NumberInputBox* b, float duration, Color fill = ORANGE, Color outline = RED, Color text = BLACK, std::function<void()> func = nullptr) : Animation(duration, func), button(b) {
        startFill = b->FillColor;
        startOutline = b->OutLineColor;
        startText = b->TextColor;
        endFill = fill;
        endOutline = outline;
        endText = text;
    }
    void applyState() override;
    void resetColor() override;
};

class RectHighlight2Anim : public Animation {
public:
    NumberInputBox* button;
    Color startFill, endFill;
    Color startOutline, endOutline;
    Color startText, endText;
    RectHighlight2Anim(NumberInputBox* b, float duration, Color fill = ORANGE, Color outline = RED, Color text = BLACK, std::function<void()> func = nullptr) : Animation(duration, func), button(b) {
        startFill = b->FillColor;
        startOutline = b->OutLineColor;
        startText = b->TextColor;
        endFill = fill;
        endOutline = outline;
        endText = text;
    }
    void applyState() override;
};

class TreapEdgeHighlightAnim : public Animation {
public:
    TreapEdge* edge;
    Color start, end;
    TreapEdgeHighlightAnim(TreapEdge* e, float duration, Color ec = ORANGE, function<void()> func = nullptr) : Animation(duration, func), edge(e), start(e->edgeColor), end(ec) {}
    void applyState() override;
    void resetColor() override;
};

class TreapEdgeHighlight2Anim : public Animation {  
public:  
   TreapEdge* edge;  
   Color start, end;  
   TreapEdgeHighlight2Anim(TreapEdge* e, float duration, Color ec = ORANGE, function<void()> func = nullptr)  
       : Animation(duration, func), edge(e), start(e->edgeColor), end(ec) {}  
   void applyState() override;  
};

#include "Treap.h"
class TreapNodeMoveAnim : public Animation {
public:
    TreapNode* node;
    Vector2 startPos;
    Vector2 endPos;
    TreapNodeMoveAnim(TreapNode* n, float duration, Vector2 sp, Vector2 ep) : Animation(duration), node(n), startPos(sp), endPos(ep){}
    void applyState() override;
    void handleReposition() override;
};

class TreapNodeInitializeAnim : public Animation {
public:
    TreapNode* node;
    Vector2 startSize;
    Vector2 endSize;
    Color start;
    Color k_text, k_fill, k_outline;
    Color p_text, p_fill, p_outline;
    TreapNodeInitializeAnim(TreapNode* n, float duration, function<void()> func = nullptr): Animation(duration, func), node(n){
        startSize = { 0, 0 };
        endSize = { static_cast<float> (n->keyBox->getWidth()), static_cast<float> (n->keyBox->getHeight()) };
        start = { 255, 255, 255, 255 };
        k_text = n->keyBox->TextColor;
        k_fill = n->keyBox->FillColor;
        k_outline = n->keyBox->OutLineColor;
        p_text = n->priorityBox->TextColor;
        p_fill = n->priorityBox->FillColor;
        p_outline = n->priorityBox->OutLineColor;
    }
    void applyState() override;
};

class TreapNodeRemoveAnim : public Animation {
public:
    TreapNode* node;
    Vector2 startSize;
    Vector2 endSize;
    Color k_sText, k_sFill, k_sOutline;
    Color p_sText, p_sFill, p_sOutline;
    Color end;
    TreapNodeRemoveAnim(TreapNode* n, float duration, function<void()> func = nullptr) : Animation(duration, func), node(n) {
        startSize = { static_cast<float> (n->keyBox->getWidth()), static_cast<float> (n->keyBox->getHeight()) };
        endSize = { 0, 0 };
        k_sText = n->keyBox->TextColor;
        k_sFill = n->keyBox->FillColor;
        k_sOutline = n->keyBox->OutLineColor;
        p_sText = n->priorityBox->TextColor;
        p_sFill = n->priorityBox->FillColor;
        p_sOutline = n->priorityBox->OutLineColor;
        end = { 255, 255, 255, 255 };
    }
    void applyState() override;
};

class MoveMultipleTreapNodesAnim : public Animation {
public:
    vector<TreapNode*> nodesToMove;
    unordered_map<int, Vector2> positions;
    MoveMultipleTreapNodesAnim(vector<TreapNode*> v, unordered_map<int, Vector2> m, float duration, function<void()> func = nullptr) : Animation(duration, func), nodesToMove(v), positions(m){}
    void applyState() override;
};