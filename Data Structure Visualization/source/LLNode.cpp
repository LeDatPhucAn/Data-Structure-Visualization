#include "../header/LLNode.h"
#include "../header/Button.h"  
#include "../header/Animation.h"  

LLNode::LLNode(int value) : NumberInputCircleInCamera({ 0,0 }, 50, value, 3), next(nullptr) {
}

LLNode::LLNode(int value, Vector2 pos) : NumberInputCircleInCamera(pos, 50, value, 3), next(nullptr) {
}
LLNode::LLNode(int value, Vector2 pos,int r) : NumberInputCircleInCamera(pos, r, value, 3), next(nullptr) {
}

LLNode::LLNode(int value, float X, float Y) : NumberInputCircleInCamera({X,Y}, 50, value, 3), next(nullptr) {
}

LLNode::LLNode(int value, float X, float Y, int r) : NumberInputCircleInCamera({ X,Y }, r, value, 3), next(nullptr) {
}