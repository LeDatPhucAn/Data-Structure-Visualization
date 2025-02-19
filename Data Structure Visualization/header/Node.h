#pragma once
template <typename T>
class Node {
public:
    T data;
    Node(T value) : data(value) {}
    virtual ~Node() {}
};