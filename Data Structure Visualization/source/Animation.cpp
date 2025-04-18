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
void Animation::makeComplete() {
    elapsed = duration;
    completed = true; 
    if (Function && !FunctionActivated) {
        Function();           // Execute lambda only if not already activated
        FunctionActivated = true;
    }
    applyState();
}
void Animation::update(float deltaTime) {
    elapsed += deltaTime;
    if (!FunctionActivated && Function) {
        Function();
        FunctionActivated = true;
    }
    clamp();
    applyState();
}
void Animation::setTime(float t) {
    elapsed = t;
    if (!FunctionActivated && Function) {
        Function();
        FunctionActivated = true;
    }
    clamp();
    applyState();
}

void Animation::reset() {
    elapsed = 0.0f;
    completed = false;
    FunctionActivated = false;
    resetColor();
}
void CircleHighLightAnim::applyState() {
    button->noDraw = false;
    float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration);
    button->OgTextColor = UI::interpolateColors(startTC, endTC, easedT);
    button->OgFillColor = UI::interpolateColors(startFC, endFC, easedT);
    button->OgOutLineColor = UI::interpolateColors(startRC, endRC, easedT);
}

RectHighlightAnim::RectHighlightAnim(NumberInputBox* b, float duration, Color fill = ORANGE, Color outline = RED, Color text = BLACK) : Animation(duration), button(b) {
    startFill = b->FillColor;
    startOutline = b->OutLineColor;
    startText = b->TextColor;
    endFill = fill;
    endOutline = outline;
    endText = text;
}

void RectHighlightAnim::applyState() {
    button->noDraw = false;
    float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration);
    button->TextColor = UI::interpolateColors(startText, endText, easedT);
    button->FillColor = UI::interpolateColors(startFill, endFill, easedT);
    button->OutLineColor = UI::interpolateColors(startOutline, endOutline, easedT);
}

void RectHighlightAnim::resetColor() {
    button->FillColor = startFill;
    button->OutLineColor = startOutline;
    button->TextColor = startText;
}

void TreapEdgeHighlightAnim::applyState() {
    edge->noDraw = false;
    float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration);
    edge->edgeColor = UI::interpolateColors(start, end, easedT);
}

void TreapEdgeHighlightAnim::resetColor() {
    edge->edgeColor = start;
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
void CircleRemoveAnim::applyState() {
    button->setRadius(EaseElasticIn(elapsed, startRadius, endRadius - startRadius, duration));
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
void CircleMoveYAnim::applyState() {
    button->setCenterY(EaseExpoOut(elapsed, startY, endY - startY, duration));
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