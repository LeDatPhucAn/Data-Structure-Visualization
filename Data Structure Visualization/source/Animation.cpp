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
	cout << "elapsed: " << elapsed << "\n";
	cout << "duration: " << duration << "\n";
    if(elapsed<=duration/2)
    {
        float easedT = EaseSineIn(elapsed / (duration/2), 0.0f, 1.0f, duration/2);
        cout << easedT << "\n";
        button->OgTextColor = UI::interpolateColors(startTC, endTC, easedT);
        button->OgFillColor = UI::interpolateColors(startFC, endFC, easedT);
        button->OgOutLineColor = UI::interpolateColors(startRC, endRC, easedT);
    }
    else {
        float easedT = EaseSineIn((elapsed-duration/2) / (duration/2), 0.0f, 1.0f, duration/2);
		cout << easedT << "\n";
		button->OgTextColor = UI::interpolateColors(endTC, startTC, easedT);
		button->OgFillColor = UI::interpolateColors(endFC, startFC, easedT);
		button->OgOutLineColor = UI::interpolateColors(endRC, startRC, easedT);
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