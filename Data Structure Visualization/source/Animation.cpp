#include "../header/Animation.h"

void Animation::update(float deltaTime) {
    elapsed += deltaTime;
    clamp();
    applyState();
}
void Animation::setTime(float t) {
    elapsed = t;
    clamp();
    applyState();
}


void CircleHighLightAnim::applyState() {
    // fade in
    if(elapsed<=duration/2)
    {
        float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration/2);
        button->OgTextColor = UI::interpolateColors(startTC, endTC, easedT);
        button->OgFillColor = UI::interpolateColors(startFC, endFC, easedT);
        button->OgOutLineColor = UI::interpolateColors(startRC, endRC, easedT);
    }
    // fade out
    else {
        float easedT = EaseSineIn((elapsed - duration/2), 0.0f, 1.0f, duration/2);
		button->OgTextColor = UI::interpolateColors(endTC, startTC, easedT);
		button->OgFillColor = UI::interpolateColors(endFC, startFC, easedT);
		button->OgOutLineColor = UI::interpolateColors(endRC, startRC, easedT);
    }
}
void CBEdgeHighLightAnim::applyState() {
    // fade in
    if(elapsed<=duration/2)
    {
        float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration/2);
        edge->edgeColor = UI::interpolateColors(startC, endC, easedT);
    }
    // fade out
    else {
        float easedT = EaseSineIn((elapsed - duration/2), 0.0f, 1.0f, duration/2);
        edge->edgeColor = UI::interpolateColors(endC,startC, easedT);
    }
}


void CircleInitializeAnim::applyState() {
    button->setRadius(EaseBackOut(elapsed, startRadius, endRadius - startRadius, duration));
}

void NodeInitializeAnimation::applyState() {
    node->radius = EaseBackOut(elapsed, startRadius, endRadius - startRadius, duration);
}

void CircleMoveAnim::applyState() {
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