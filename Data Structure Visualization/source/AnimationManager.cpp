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

void AnimationManager::clear() {
	for (auto anim : animations) {
        anim->resetColor();
		delete anim;
	}
	animations.clear();
	startTimes.clear();
	totalDuration = 0;
	currentTime = 0;
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
    if (animations.empty())return;
    for (int i = 0; i < animations.size() - 1; ++i) {
        if (currentTime < startTimes[i + 1]) {
            animations[i]->makeComplete();
            seek(startTimes[i + 1]);
            return;
        }
    }
}

// Go to the start of the previous animation
void AnimationManager::goToPrevious() {
	if (animations.empty())return;  
    for (int i = 1; i < animations.size(); ++i) {
        if (currentTime <= startTimes[i]) {
            seek(startTimes[i - 1]);
            return;
        }
    }
    if (currentTime <= startTimes[0]) {
        seek(0);
    }
}

// Go to step k: state after animation k completes (step 0 is initial state)
void AnimationManager::goToStep(int k) {
    if (k < 0 || k > animations.size()) return;

    paused = true;

    // Reset all animations to their initial state
    for (auto anim : animations) {
        anim->reset();
    }

    // Apply animations 0 to k-1 fully
    for (int i = 0; i < k; ++i) {
        animations[i]->makeComplete();
    }

    // Update currentTime to the end of animation k-1 (or 0 if k == 0)
    if (k == 0) {
        currentTime = 0;
    }
    else {
        currentTime = startTimes[k - 1] + animations[k - 1]->duration;
    }
}

// Go to the first step (initial state)
void AnimationManager::goToFirstStep() {
    goToStep(0);
}

// Go to the final step (after all animations)
void AnimationManager::goToLastStep() {
    goToStep(animations.size());
}

// Go to the previous step
void AnimationManager::goToPreviousStep() {
    if (animations.empty()) return;
    // Find the current step based on currentTime
    int currentStep = 0;
    for (int i = 0; i < animations.size(); ++i) {
        if (currentTime < startTimes[i] + animations[i]->duration) {
            currentStep = i;
            break;
        }
        else if (i == animations.size() - 1 && currentTime >= startTimes[i] + animations[i]->duration) {
            currentStep = animations.size();
        }
    }
    goToStep(currentStep - 1);
}

// Go to the next step (modify existing goToNext for consistency)
void AnimationManager::goToNextStep() {
    if (animations.empty()) return;
    // Find the current step based on currentTime
    int currentStep = 0;
    for (int i = 0; i < animations.size(); ++i) {
        if (currentTime < startTimes[i] + animations[i]->duration) {
            currentStep = i;
            break;
        }
        else if (i == animations.size() - 1 && currentTime >= startTimes[i] + animations[i]->duration) {
            currentStep = animations.size();
        }
    }
    goToStep(currentStep + 1);
}

