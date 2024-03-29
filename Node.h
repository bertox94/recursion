#ifndef RECURSION_NODE_H
#define RECURSION_NODE_H

#define MAX_RAND RAND_MAX

#include <random>
#include <ctime>
#include <iostream>
#include <list>

using namespace std;

/**
                                          read L for 1 ←|← written R for 1
                                  passed above L for 1 ↑|↓ passed below R for 1
                        used L for 2, computed L for 1 |1| used R for 1, computed R for 2
                                  passed above L for 2 ↑|↓ passed below R for 2
                        used L for 3, computed L for 2 |2| used R for 2, computed R for 3
                                  passed above L for 3 ↑|↓ passed below R for 3
                                       written L for 3 |3| read R for 3
                                                        ←
*/

template<typename T>
class Node {
public:
    int id;
    T item;
    std::vector<Node *> children;

    Node() = default;

    explicit Node(int id, const T &item) : id(id), item(item) {}

    explicit Node(int id, T &&item) : Node(id, item) {}

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
};

template<typename T>
class value_ {
public:
    explicit value_(T vv) : val(vv) {}

    T val;
};

class depth_ {
public:
    explicit depth_(int vv) : val(vv) {}

    int val;
};

class height_ {
public:
    explicit height_(int vv) : val(vv) {}

    int val;
};

class _targetdepth {
public:
    explicit _targetdepth(int vv) : val(vv) {}

    int val;
};

class _valid {
public:
    bool val;
};

class num_ {
public:
    explicit num_(int vv) : val(vv) {}

    int val;
};


template<typename T>
class RightAttr {
public:
    RightAttr(depth_ d, _targetdepth td) : depth(d.val), target_depth(td.val) {}

    RightAttr(depth_ d) : depth(d.val) {}

    RightAttr(value_<T> v) : value(v.val) {}

    int depth;
    int target_depth;
    T value;
};

template<typename T>
class LeftAttr {
public:
    LeftAttr(num_ n, value_<T> v) : num(n.val), value(v.val) {}

    LeftAttr(depth_ d) : depth(d.val) {}

    LeftAttr(height_ h) : height(h.val) {}

    LeftAttr(num_ n) : num(n.val) {}

    LeftAttr(value_<T> v) : value(v.val) {}

    LeftAttr() = default;

    bool valid;
    int num;
    int depth;
    int height;
    T value;
    std::list<T> simpleList;
    std::list<LeftAttr<T>> compositeList;
};

// min_breadth of course doesn't mean that every node has at least min_breadth children,
// but the nodes that have children, they have at least min_breadth children
template<typename T>
int
build_tree(Node<T> *node, int curr_depth, int max_depth, int min_breadth, int max_breadth, int curr_nodes) {

    bool make_children = (rand() % 2) && curr_depth < max_depth;
    if (make_children) {
        int n_children = std::max(1 + (rand() % max_breadth), min_breadth);
        for (auto i = 1; i <= n_children /*&& curr_nodes < max_nodes*/; i++) {
            auto child = new Node<T>(curr_nodes + 1, std::rand());
            curr_nodes++;
            node->children.push_back(child);
            curr_nodes = build_tree(child,
                                    curr_depth + 1, max_depth,
                                    min_breadth, max_breadth, curr_nodes);
        }
        return curr_nodes;
    } else {
        return curr_nodes;
    }
}

template<typename T>
int
build_tree(Node<T> *node, int curr_depth, int max_depth, int min_breadth, int max_breadth) {
    if (curr_depth == max_depth) {
        return 1;
    }

    bool make_children = (rand() % 2);
    if (make_children) {
        int direct_children = std::max(1 + (rand() % max_breadth), min_breadth);
        int num_of_children = 0;
        for (auto i = 1; i <= direct_children /*&& curr_nodes < max_nodes*/; i++) {
            auto child = new Node<T>(std::rand());
            node->children.push_back(child);
            num_of_children += build_tree(child,
                                          curr_depth + 1, max_depth,
                                          min_breadth, max_breadth);
        }
        return num_of_children + 1;
    } else {
        return 1;
    }
}

template<typename T>
int build_list(Node<T> *node, int curr_nodes, int exact_nodes) {
    if (curr_nodes == exact_nodes) {
        return curr_nodes;
    } else {
        auto child = new Node<T>(std::rand());
        node->children.push_back(child);
        curr_nodes = build_list(child, curr_nodes + 1, exact_nodes);
        return curr_nodes;
    }
}

#endif //RECURSION_NODE_H
