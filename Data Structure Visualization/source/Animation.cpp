#include "../header/Animation.h"

void Animation::AnimateSprite(float X, float Y, Texture2D texture, int numframes, int frameindex) {
	float frameX = frameindex * texture.width / numframes;
	Rectangle frameRec = { frameX, 0.0f, (float)texture.width / numframes, (float)texture.height };
	DrawTextureRec(texture, frameRec, { X, Y }, WHITE);
}