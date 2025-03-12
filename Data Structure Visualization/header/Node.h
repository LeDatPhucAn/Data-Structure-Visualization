#pragma once
#include <iostream>
#include <raylib.h>

using namespace std;

class Node {
public:
    int data;
    //Vector2 position;

    Node(int value) : data(value) {}
    virtual ~Node() {}
};
