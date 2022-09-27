#ifndef RECURSION_NODE_H
#define RECURSION_NODE_H

#include <random>
#include <ctime>
#include <iostream>
#include <list>

using namespace std;

template<typename T>
class Node {
public:
    T *item;
    list<Node *> children;

    Node() = default;

    explicit Node(const T &item) : item(new T(item)) {}

    explicit Node(T &&item) : Node(item) {}

    bool is_leaf() const{
        return children.size() == 0;
    }

    ~Node() {
        for (auto &child: children)
            delete child;
        delete item;
    }

};

#endif //RECURSION_NODE_H
