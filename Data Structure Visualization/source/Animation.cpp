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
void NodeInitialAnimation::update(float deltaTime) {
    Animate(deltaTime);
	node->radius = EaseElasticOut(elapsed, startRadius, endRadius - startRadius, duration);
}
void ButtonMoveAnimation::HandleResize() {
	endX = button->rect.x;
	endY = button->rect.y;
}

void ButtonMoveAnimation::update(float deltaTime) {
    Animate(deltaTime);
    button->rect.x = EaseSineOut(elapsed, startX, endX - startX, duration);
    button->rect.y = EaseSineOut(elapsed, startY, endY - startY, duration);
}
void ButtonMoveXAnimation::update(float deltaTime)  {
    Animate(deltaTime);
    button->rect.x = EaseBounceOut(elapsed, startX, endX - startX, duration);
}
void ButtonMoveYAnimation::update(float deltaTime)  {
    Animate(deltaTime);
    button->rect.y = EaseBounceOut(elapsed, startY, endY - startY, duration);
}
