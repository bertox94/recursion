//
// Created by Halib on 9/9/2021.
//

#ifndef RECURSION_NODE_H
#define RECURSION_NODE_H

#include <random>
#include <ctime>
#include <iostream>

template<typename T>
class Node {
public:
    T *item;
    Node *left;
    Node *right;

    Node() : left(nullptr), right(nullptr) {}

    explicit Node(T &item) : item(new T(item)), left(nullptr), right(nullptr) {}

    explicit Node(T &&item) : Node(item) {}
};


#endif //RECURSION_NODE_H
