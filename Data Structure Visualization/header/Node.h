#pragma once
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node(int value) : data(value) {}
    virtual ~Node() {}
};
