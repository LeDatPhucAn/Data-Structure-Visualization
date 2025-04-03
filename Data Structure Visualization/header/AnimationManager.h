#pragma once
#include <vector>
class Animation;
class AnimationManager {
private:
    std::vector<Animation*> animations; // Pointers to animations owned elsewhere
    float speed = 1.0f;                 // Speed multiplier (1.0 = normal)
    bool paused = false;                // Pause state
    int direction = 1;                  // 1 = forward, -1 = backward

public:
    AnimationManager() {
        speed = 1.0f;
        paused = false;
        direction = 1;
    }
    ~AnimationManager() {
        for (auto anim : animations) {
            if (anim) delete anim;
        }
    }
    // Add an animation to manage
    void addAnimation(Animation* anim);

    // Remove an animation
    void removeAnimation(Animation* anim);

    // Update all animations with adjusted deltaTime
    void update(float deltaTime);

    // Pause playback
    void pause();

    // Resume playback
    void resume();

    // Set playback speed (e.g., 2.0f = 2x speed, 0.5f = half speed)
    void setSpeed(float s);

    // Set playback direction (1 = forward, -1 = backward)
    void setDirection(int dir);

    // Play forward
    void playForward();

    // Play backward
    void playBackward();

    // Seek to a specific progress (0.0 to 1.0)
    void seek(float progress);
};