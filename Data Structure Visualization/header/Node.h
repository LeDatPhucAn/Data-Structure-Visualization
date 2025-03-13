#pragma once
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node(int value) : data(value) {}
    virtual ~Node() {}
    //vector2D position;
    //void connectnode(vector2D from, vector2D to);
};
