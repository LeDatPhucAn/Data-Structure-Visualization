#include "../header/Animation.h"


void Animation::Animate(float deltaTime) {
   //if (completed) return;
   elapsed += deltaTime;
   if (deltaTime >= 0) { // Playing forward
       if (elapsed >= duration) {
           elapsed = duration;
           completed = true;
       }
       else {
           completed = false;
       }
   }
   else { // Playing backward
       if (elapsed <= 0) {
           elapsed = 0;
           completed = false;
       }
       else {
           completed = false;
       }
   }
}
void CircleHighLightAnim::update(float deltaTime) {
    Animate(deltaTime);
    float easedT = EaseSineIn(elapsed / duration, 0.0f, 1.0f, duration);
    button->OgTextColor = UI::interpolateColors(startTC, endTC, easedT);
    button->OgFillColor = UI::interpolateColors(startFC, endFC, easedT);
    button->OgOutLineColor = UI::interpolateColors(startRC, endRC, easedT);
}
void CircleHighLightAnimReverse::update(float deltaTime) {
    Animate(deltaTime);
    float easedT = EaseSineIn(elapsed / duration, 0.0f, 1.0f, duration);
    button->OgTextColor = UI::interpolateColors(startTC, endTC, easedT);
    button->OgFillColor = UI::interpolateColors(startFC, endFC, easedT);
    button->OgOutLineColor = UI::interpolateColors(startRC, endRC, easedT);
}
void CircleInitializeAnim::update(float deltaTime) {
    Animate(deltaTime);
	button->setRadius(EaseBackOut(elapsed, startRadius, endRadius - startRadius, duration));
}
void NodeInitializeAnimation::update(float deltaTime) {
    Animate(deltaTime);
	node->radius = EaseBackOut(elapsed, startRadius, endRadius - startRadius, duration);
}
void CircleMoveAnim::update(float deltaTime) {
    Animate(deltaTime);
    button->setCenterX(EaseExpoOut(elapsed, startX, endX - startX, duration));
    button->setCenterY(EaseExpoOut(elapsed, startY, endY - startY, duration));
}
void CircleMoveXAnim::update(float deltaTime) {
    Animate(deltaTime);
    button->setCenterX(EaseExpoOut(elapsed, startX, endX - startX, duration));
}
void RectMoveAnim::HandleResize() {
	endX = button->rect.x;
	endY = button->rect.y;
}

void RectMoveAnim::update(float deltaTime) {
    Animate(deltaTime);
    button->rect.x = EaseSineOut(elapsed, startX, endX - startX, duration);
    button->rect.y = EaseSineOut(elapsed, startY, endY - startY, duration);
}
void RectMoveXAnim::update(float deltaTime)  {
    Animate(deltaTime);
    button->rect.x = EaseExpoOut(elapsed, startX, endX - startX, duration);
}
void RectMoveYAnim::update(float deltaTime)  {
    Animate(deltaTime);
    button->rect.y = EaseBounceOut(elapsed, startY, endY - startY, duration);
}
