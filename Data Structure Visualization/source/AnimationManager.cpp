#include "../header/Animation.h"
#include "../header/AnimationManager.h"

void AnimationManager::addAnimation(Animation* anim) {
    if (anim) {
        animations.push_back(anim);
    }
}

void AnimationManager::removeAnimation(Animation* anim) {
    auto it = std::find(animations.begin(), animations.end(), anim);
    if (it != animations.end()) {
        animations.erase(it);
    }
}

void AnimationManager::update(float deltaTime) {
    if (paused) return;
    float effectiveDelta = deltaTime * speed * direction;
    for (Animation* anim : animations) {
        anim->update(effectiveDelta);
    }
}

void AnimationManager::pause() {
    paused = true;
}

void AnimationManager::resume() {
    paused = false;
}

void AnimationManager::setSpeed(float s) {
    speed = s > 0 ? s : 0;
}

void AnimationManager::setDirection(int dir) {
    if (dir == 1 || dir == -1) {
        direction = dir;
    }
}

void AnimationManager::playForward() {
    setDirection(1);
    resume();
}

void AnimationManager::playBackward() {
    setDirection(-1);
    resume();
}

void AnimationManager::seek(float progress) {
    float clampedProgress = std::max(0.0f, std::min(1.0f, progress));
    for (Animation* anim : animations) {
        anim->elapsed = clampedProgress * anim->duration;
        anim->completed = (clampedProgress >= 1.0f);
        anim->update(0);
    }
}
