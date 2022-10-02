#ifndef RECURSION_NODE_H
#define RECURSION_NODE_H

#define MAX_RAND RAND_MAX

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

    Node<T> *next() {
        switch (children.size()) {
            case 0:
                throw runtime_error("The current node has no child.");
                break;
            case 1:
                return children.front();
                break;
            default:
                throw runtime_error("Node was expected to be in a list.");
                break;
        }
    }

    bool is_leaf() const {
        return children.size() == 0;
    }

    bool has_children() const {
        return children.size() > 0;
    }

    void add_children(int big, int max_children = 0) {
        buildtree(this, 1, big, max_children);
    }

    void buildtree(Node<T> *root, int curr, int big, int max_children) {
        //higher the number to the right, the bigger the root
        int num = curr;
        while (std::rand() % (2 * curr) <= big) {
            if (max_children && (curr - num) >= max_children)
                break;
            root->children.push_back(new Node<T>(std::rand() % MAX_RAND));
            curr++;
        }

        for (auto &child: root->children)
            buildtree(child, curr + 1, big, max_children);
    }

    ~Node() {
        for (auto &child: children)
            delete child;
        delete item;
    }

};

template<typename T>
class RightAttr {
public:
    RightAttr(int depth, int target) : depth(depth), target(target) {}

    int depth;
    int target;
    T value;
};

template<typename T>
class LeftAttr {
public:
    LeftAttr(int num, int value) : num(num), value(value) {}

    LeftAttr() = default;

    bool valid;
    int num;
    T value;
    std::list<T> simpleList;
    std::list<LeftAttr<T>> compositeList;
};


#endif //RECURSION_NODE_H
