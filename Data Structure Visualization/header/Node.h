#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Node {
public:
    T data;
    Node(T value) : data(value) {}
    virtual ~Node() {}
};