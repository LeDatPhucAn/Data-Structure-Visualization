#include "../header/Animation.h"
void Animation::clamp() {
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
void Animation::update(float deltaTime) {
    elapsed += deltaTime;
    if (Function) Function();
    clamp();
    applyState();
}
void Animation::setTime(float t) {
    elapsed = t;
    if (Function) Function();
    clamp();
    applyState();
}


void CircleHighLightAnim::applyState() {
        float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration);
        button->OgTextColor = UI::interpolateColors(startTC, endTC, easedT);
        button->OgFillColor = UI::interpolateColors(startFC, endFC, easedT);
        button->OgOutLineColor = UI::interpolateColors(startRC, endRC, easedT);
}

void CBEdgeHighLightAnim::applyState() {
	edge->noDraw = false; 
    float easedT = EaseSineIn(elapsed, 0, 1.0f, duration);
    edge->edgeColor = UI::interpolateColors(startC, endC, easedT);
}
void CBEdgeAddAnim::applyState() {
    edge->thickness = EaseElasticOut(elapsed, startT, endT-startT, duration);
}

void CBEdgeRemoveAnim::applyState() {
    edge->thickness = EaseElasticIn(elapsed, startT, endT-startT, duration);
}



void CircleInitializeAnim::applyState() {
    button->setRadius(EaseBackOut(elapsed, startRadius, endRadius - startRadius, duration));
}

void NodeInitializeAnimation::applyState() {
    node->radius = EaseBackOut(elapsed, startRadius, endRadius - startRadius, duration);
}

void CircleMoveAnim::applyState() {
	button->noDraw = false;
    button->setCenterX(EaseExpoOut(elapsed, startX, endX - startX, duration));
    button->setCenterY(EaseExpoOut(elapsed, startY, endY - startY, duration));
}

void CircleMoveXAnim::applyState() {
    button->setCenterX(EaseExpoOut(elapsed, startX, endX - startX, duration));
}

void RectMoveAnim::applyState() {
    button->rect.x = EaseSineOut(elapsed, startX, endX - startX, duration);
    button->rect.y = EaseSineOut(elapsed, startY, endY - startY, duration);
}

void RectMoveXAnim::applyState() {
    button->rect.x = EaseExpoOut(elapsed, startX, endX - startX, duration);
}
void RectMoveYAnim::applyState() {
    button->rect.y = EaseExpoOut(elapsed, startY, endY - startY, duration);
}