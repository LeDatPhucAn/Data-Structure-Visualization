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
	Animation() : duration(0), elapsed(0), completed(false) {};
    Animation(float dur) : duration(dur), elapsed(0), completed(false) {};
    virtual ~Animation() = default;
    virtual void HandleResize() {};
    virtual void HandleReposition() {};
    virtual void update(float deltaTime);
    virtual void applyState() = 0;
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
    virtual void clamp() {
        if (elapsed >= duration) {
            elapsed = duration;
            completed = true;
        }
        else if (elapsed <= 0) {
            elapsed = 0;
            completed = false;
        }
        else {
            completed = false;
        }
    }
    // Set the animation to a specific time and apply the state immediately
    virtual void setTime(float t);
};
class CircleHighLightAnim : public Animation {
protected:
    CircleButton* button;
    Color startTC,endTC;
    Color startFC,endFC;
    Color startRC,endRC;
public:
    virtual ~CircleHighLightAnim() = default;
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
    void HandleReposition() {}
    void applyState() override;
};
class CircleHighLightAnimReverse : public Animation {
protected:
    CircleButton* button;
    Color startTC,endTC;
    Color startFC,endFC;
    Color startRC,endRC;
public:
    virtual ~CircleHighLightAnimReverse() = default;
    CircleHighLightAnimReverse(
        CircleButton* btn, float duration,
        Color sTC = ORANGE, 
        Color sFC = RAYWHITE, 
        Color sRC = ORANGE
        )
        : Animation(duration),
        startTC(sTC), startFC(sFC), startRC(sRC), button(btn) {
        endTC = btn->OgTextColor;
        endFC = btn->OgFillColor;
        endRC = btn->OgOutLineColor;
    }
    void HandleReposition() {}
    void applyState() override;
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
    void HandleReposition() override {
        endX = button->getCenterX();
        endY = button->getCenterY();
    }
    void applyState() override;
};
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
    CircleMoveXAnim(CircleButton* btn, float sX, float duration)
        : Animation(duration), startX(sX), button(btn) {
        endX = btn->getCenterX();
    }
    CircleMoveXAnim(CircleButton* btn, float sX, float eX, float duration)
        : Animation(duration), startX(sX), endX(eX), button(btn) {
    }
    void HandleReposition() override{
        endX = button->getCenterX();
    }
    void applyState() override;
};

class RectMoveAnim : public Animation {
private:
    
protected:
    RectButton* button;
    float startX, startY;
    float endX, endY;
public:

    void HandleResize() override;
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
    void applyState() override;
};
class RectMoveXAnim : public RectMoveAnim {
public:
    RectMoveXAnim(RectButton* btn, float duration) : RectMoveAnim(btn, duration) {};
    RectMoveXAnim(RectButton* btn, float sX, float duration) : RectMoveAnim(btn, sX, 0, duration) {};
    void applyState() override;
};
class RectMoveYAnim : public RectMoveAnim {
public:
    RectMoveYAnim(RectButton* btn, float duration) : RectMoveAnim(btn, duration) {};
    RectMoveYAnim(RectButton* btn, float sY, float duration) : RectMoveAnim(btn, 0, sY, duration) {};
    void applyState() override;
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
    void HandleResize() {};
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
    void HandleResize() {};
    void applyState() override;
};



