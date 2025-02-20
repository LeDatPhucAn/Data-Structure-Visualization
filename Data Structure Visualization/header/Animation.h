#include "UI.h"

class Animation : public UI {
private:
public:
	void AnimateSprite(float X, float Y, Texture2D texture, int numframes, float frameindex);
};