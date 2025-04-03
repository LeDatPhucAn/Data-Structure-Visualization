#include "../header/Animation.h"
#include "../header/AnimationManager.h"

void AnimationManager::addAnimation(Animation* anim) {
    if (anim) {
        animations.push_back(anim);
        startTimes.push_back(totalDuration);
        totalDuration += anim->duration;
    }
}

void AnimationManager::removeAnimation(Animation* anim) {
    auto it = std::find(animations.begin(), animations.end(), anim);
    if (it != animations.end()) {
        animations.erase(it);
    }
}
void AnimationManager::updateActiveAnimation() {
    for (size_t i = 0; i < animations.size(); ++i) {
        float start = startTimes[i];
        float end = start + animations[i]->duration;
        if (start <= currentTime && currentTime < end) {
            float localTime = currentTime - start;
            animations[i]->setTime(localTime);
            break;
        }
    }
}
void AnimationManager::update(float deltaTime) {
    if (paused) return;

    // Adjust current time based on speed and direction
    float effectiveDelta = deltaTime * speed * direction;
    currentTime += effectiveDelta;
    if (currentTime < 0) currentTime = 0;
    if (currentTime > totalDuration) currentTime = totalDuration;

    // Update the active animation
    updateActiveAnimation();
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
// Jump to a specific time in the sequence
void AnimationManager::seek(float time) {
    currentTime = std::max(0.0f, std::min(totalDuration, time));
    updateActiveAnimation();
}

// Go to the start of the next animation
void AnimationManager::goToNext() {
    for (size_t i = 0; i < animations.size() - 1; ++i) {
        if (currentTime < startTimes[i + 1]) {
            seek(startTimes[i + 1]);
            return;
        }
    }
}

// Go to the start of the previous animation
void AnimationManager::goToPrevious() {
    for (size_t i = 1; i < animations.size(); ++i) {
        if (currentTime <= startTimes[i]) {
            seek(startTimes[i - 1]);
            return;
        }
    }
    if (currentTime <= startTimes[0]) {
        seek(0);
    }
}
//void AnimationManager::seek(float progress) {
//    float clampedProgress = std::max(0.0f, std::min(1.0f, progress));
//    for (Animation* anim : animations) {
//        anim->elapsed = clampedProgress * anim->duration;
//        anim->completed = (clampedProgress >= 1.0f);
//        anim->update(0);
//    }
//}
