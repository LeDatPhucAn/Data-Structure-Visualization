#pragma once
#include <vector>
class Animation;
class AnimationManager {
private:
    std::vector<float> startTimes;      // Start time of each animation on the timeline
    float totalDuration = 0;            // Total duration of the sequence
    float currentTime = 0;              // Current position on the timeline
    float speed = 1.0f;                 // Playback speed (default 1x)
    bool paused = true;                 // Playback state
    int direction = 1;                  // 1 for forward, -1 for backward
public:
    std::vector<Animation*> animations; // List of animations in the sequence

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

    // remove every animation
	void clear();
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


    int getStep();                 // get step 

    void goToStep(int k);          // Go to step k

    void goToFirstStep();          // Go to initial state

    void goToLastStep();           // Go to final state

    void goToPreviousStep();       // Go to previous step

    void goToNextStep();           // Go to next step
private:
    // Update the state of the active animation based on currentTime
    void updateActiveAnimation();
};