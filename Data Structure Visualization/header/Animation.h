#pragma once
#include "UI.h"
#include "reasings.h"
class Animation : public UI {
private:
public:
	Animation();
	~Animation();
	void AnimateSprite(float X, float Y, Texture2D texture, int numframes, float frameindex);
};