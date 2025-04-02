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
    button->setCenterX(EaseElasticIn(elapsed, startX, endX - startX, duration));
    button->setCenterY(EaseElasticIn(elapsed, startY, endY - startY, duration));
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
