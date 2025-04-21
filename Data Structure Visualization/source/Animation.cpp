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

void RectHighlightAnim::applyState() {
    float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration);
    button->TextColor = UI::interpolateColors(startText, endText, easedT);
    button->FillColor = UI::interpolateColors(startFill, endFill, easedT);
    button->OutLineColor = UI::interpolateColors(startOutline, endOutline, easedT);
}

void RectHighlight2Anim::applyState() {
    float easedT = EaseSineInOut(elapsed, 0.0f, 1.0f, duration);

    if (easedT <= 0.5f) {
        float progress = easedT * 2.0f;
        button->FillColor = UI::interpolateColors(startFill, endFill, progress);
        button->OutLineColor = UI::interpolateColors(startOutline, endOutline, progress);
        button->TextColor = UI::interpolateColors(startText, endText, progress);
    }
    else {
        float progress = (easedT - 0.5f) * 2.0f;
        button->FillColor = UI::interpolateColors(endFill, startFill, progress);
        button->OutLineColor = UI::interpolateColors(endOutline, startOutline, progress);
        button->TextColor = UI::interpolateColors(endText, startText, progress);
    }
}

void RectHighlightAnim::resetColor() {
    if (!button) return;
    button->FillColor = startFill;
    button->OutLineColor = startOutline;
    button->TextColor = startText;
}

void TreapEdgeHighlightAnim::applyState() {
    float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration);
    edge->edgeColor = UI::interpolateColors(start, end, easedT);
}

void TreapEdgeHighlightAnim::resetColor() {
    if (!edge) return;
    edge->edgeColor = start;
}

void TreapEdgeHighlight2Anim::applyState() {
    float easedT = EaseSineInOut(elapsed, 0.0f, 1.0f, duration);

    if (easedT <= 0.5f) {
        float progress = easedT * 2.0f;
        edge->edgeColor = UI::interpolateColors(start, end, progress);
    }
    else {
        float progress = (easedT - 0.5f) * 2.0f;
        edge->edgeColor = UI::interpolateColors(end, start, progress);
    }
}

void TreapNodeMoveAnim::applyState() {
    node->position.x = EaseExpoOut(elapsed, startPos.x, endPos.x - startPos.x, duration);
    node->position.y = EaseExpoOut(elapsed, startPos.y, endPos.y - startPos.y, duration);
    node->syncPosition();
}

void TreapNodeMoveAnim::handleReposition() {
    endPos = node->position;
}

void TreapNodeInitializeAnim::applyState() {
    float easedT = EaseSineIn(elapsed, 0.0f, 1.0f, duration);
    node->keyBox->rect.x = EaseBackOut(elapsed, startSize.x, endSize.x - startSize.x, duration);
    node->priorityBox->rect.x = EaseBackOut(elapsed, startSize.x, endSize.x - startSize.x, duration);
    node->keyBox->rect.y = EaseBackOut(elapsed, startSize.y, endSize.y - startSize.y, duration);
    node->priorityBox->rect.y = EaseBackOut(elapsed, startSize.y, endSize.y - startSize.y, duration);
    node->keyBox->TextColor = UI::interpolateColors(start, k_text, easedT);
    node->keyBox->FillColor = UI::interpolateColors(start, k_fill, easedT);
    node->keyBox->OutLineColor = UI::interpolateColors(start, k_outline, easedT);
    node->priorityBox->TextColor = UI::interpolateColors(start, p_text, easedT);
    node->priorityBox->FillColor = UI::interpolateColors(start, p_fill, easedT);
    node->priorityBox->OutLineColor = UI::interpolateColors(start, p_outline, easedT);
}

void TreapNodeRemoveAnim::applyState() {
    float easedT = EaseSineIn(elapsed, 0.0, 1.0f, duration);
    node->keyBox->rect.x = EaseBackOut(elapsed, startSize.x, endSize.x - startSize.x, duration);
    node->priorityBox->rect.x = EaseBackOut(elapsed, startSize.x, endSize.x - startSize.x, duration);
    node->keyBox->rect.y = EaseBackOut(elapsed, startSize.y, endSize.y - startSize.y, duration);
    node->priorityBox->rect.y = EaseBackOut(elapsed, startSize.y, endSize.y - startSize.y, duration);
    node->keyBox->TextColor = UI::interpolateColors(k_sText, end, easedT);
    node->keyBox->FillColor = UI::interpolateColors(k_sFill, end, easedT);
    node->keyBox->OutLineColor = UI::interpolateColors(k_sOutline, end, easedT);
    node->priorityBox->TextColor = UI::interpolateColors(p_sText, end, easedT);
    node->priorityBox->FillColor = UI::interpolateColors(p_sFill, end, easedT);
    node->priorityBox->OutLineColor = UI::interpolateColors(p_sOutline, end, easedT);
}

//  node->position.x = EaseExpoOut(elapsed, startPos.x, endPos.x - startPos.x, duration);
void MoveMultipleTreapNodesAnim::applyState() {
    for (TreapNode* n : nodesToMove) {
        n->position.x = EaseExpoOut(elapsed, n->position.x, positions[n->getKey()].x - n->position.x, duration);
        n->position.y = EaseExpoOut(elapsed, n->position.y, positions[n->getKey()].y - n->position.y, duration);
        n->syncPosition();
    }
}
