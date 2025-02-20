#include "../header/Animation.h"

void Animation::AnimateSprite(float X, float Y, Texture2D texture, int numframes, float frameindex) {
	//float frameX = frameindex * texture.width / numframes;
	Rectangle frameRec = { 0.0f, 0.0f, (float) frameindex * texture.width / numframes, (float)texture.height };
	DrawTextureRec(texture, frameRec, { X, Y }, WHITE);
}