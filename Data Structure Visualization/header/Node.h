#pragma once
#include <iostream>
#include <raylib.h>
using namespace std;
class Animation;
class Node {
public:
    int data;
    Vector2 position;
    Animation* animation;
    float radius;
    Node(int value, Vector2 pos, float r);
    virtual ~Node() {
        if (animation)delete animation;
    }
};
