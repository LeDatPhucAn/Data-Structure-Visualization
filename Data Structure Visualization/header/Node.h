#pragma once
#include <iostream>
#include <raylib.h>

using namespace std;

class Node {
public:
    int data;
    Vector2 position;
    int radius;
    Node(int value,Vector2 pos, int r): data(value), position(pos), radius(r) {}
    virtual ~Node() {}
};
