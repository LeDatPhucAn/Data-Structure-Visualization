#pragma once
#include <vector>
class Animation;
class AnimationManager {
private:
    std::vector<Animation*> animations; // List of animations in the sequence
    std::vector<float> startTimes;      // Start time of each animation on the timeline
    float totalDuration = 0;            // Total duration of the sequence
    float currentTime = 0;              // Current position on the timeline
    float speed = 1.0f;                 // Playback speed (default 1x)
    bool paused = true;                 // Playback state
    int direction = 1;                  // 1 for forward, -1 for backward
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


    bool isPaused() const { return paused; };

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

    // Go to the start of the next animation
    void goToNext();

    // Go to the start of the previous animation
    void goToPrevious();
private:
    // Update the state of the active animation based on currentTime
    void updateActiveAnimation();
};