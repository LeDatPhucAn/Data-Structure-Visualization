#include "../header/Animation.h"


void Animation::Animate(float deltaTime) {
   if (completed) return;
   elapsed += deltaTime;
   float t = elapsed / duration;
   if (t >= 1.0f) { 
       t = 1.0f; 
       elapsed = duration;
       completed = true; 
   }
}
void CircleHighLightAnim::update(float deltaTime) {
    Animate(deltaTime);
    float easedT = EaseSineIn(elapsed / duration, 0.0f, 1.0f, duration);
    Color tc = UI::interpolateColors(startTC, endTC, easedT);
    Color fc = UI::interpolateColors(startFC, endFC, easedT);
    Color rc = UI::interpolateColors(startRC, endRC, easedT);
    button->setOgColors(tc, fc, rc);
}
void CircleHighLightAnimReverse::update(float deltaTime) {
    Animate(deltaTime);
    float easedT = EaseSineIn(elapsed / duration, 0.0f, 1.0f, duration);
    Color tc = UI::interpolateColors(startTC, endTC, easedT);
    Color fc = UI::interpolateColors(startFC, endFC, easedT);
    Color rc = UI::interpolateColors(startRC, endRC, easedT);
    button->setOgColors(tc, fc, rc);
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
