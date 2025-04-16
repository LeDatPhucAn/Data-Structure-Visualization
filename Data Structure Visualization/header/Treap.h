#pragma once

#include "Button.h"
#include "Node.h"
#include "Edge.h"
#include <cstdlib>
#include <ctime>

class TreapNode : public Node {
public:
    TreapEdge* leftEdge;
    TreapEdge* rightEdge;
    int subtreeWidth;
    bool noDraw = false;
	NumberInputBox* keyBox = nullptr;
    NumberInputBox* priorityBox = nullptr;

    TreapNode(int key, int priority, Vector2 pos);
    ~TreapNode();

    int getKey() const;
    void setKey(int key);
    int getPriority() const;
    void setPriority(int p);

    void syncPosition();
	void setVisualPosition(float x, float y);
    void update();
	void draw();
    Vector2 getMousePos() const;
};
