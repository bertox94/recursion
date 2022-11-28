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
    T item;
    std::vector<Node *> children;

    Node() = default;

    explicit Node(const T &item) : item(item) {}

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

};

template<typename T>
class _value {
public:
    explicit _value(T vv) : val(vv) {}

    T val;
};

class _depth {
public:
    explicit _depth(int vv) : val(vv) {}

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

class _num {
public:
    explicit _num(int vv) : val(vv) {}

    int val;
};


template<typename T>
class RightAttr {
public:
    RightAttr(_depth d, _targetdepth td) : depth(d.val), target_depth(td.val) {}

    RightAttr(_depth d) : depth(d.val) {}

    int depth;
    int target_depth;
    T value;
};

template<typename T>
class LeftAttr {
public:
    LeftAttr(_num n, _value<T> v) : num(n.val), value(v.val) {}

    LeftAttr() = default;

    bool valid;
    int num;
    int depth;
    T value;
    std::list<T> simpleList;
    std::list<LeftAttr<T>> compositeList;
};

int i1 = 0;
int i2 = 0;
int i3 = 0;
int i4 = 0;
int i5 = 0;

template<typename T>
unsigned long build_tree(Node<T> *node, int curr_depth, int max_depth, int max_breadth, int curr_nodes, int max_nodes) {
    if (curr_nodes >= max_nodes) {
        return curr_nodes;
    }
    if (curr_depth == max_depth) {
        return curr_nodes;
    }

    bool has_children = rand() % 2;
    if (has_children) {
        int n_children = 1 + (rand() % max_breadth);
        i1 = n_children == 1 ? i1 + 1 : i1;
        i2 = n_children == 1 ? i2 + 1 : i2;
        i3 = n_children == 1 ? i3 + 1 : i3;
        i4 = n_children == 1 ? i4 + 1 : i4;
        i5 = n_children == 1 ? i5 + 1 : i5;
        for (auto i = 1; i <= n_children /*&& curr_nodes < max_nodes*/; i++) {
            auto child = new Node<T>(std::rand());
            node->children.push_back(child);
            curr_nodes = build_tree(child,
                                    curr_depth + 1, max_depth, max_breadth,
                                    curr_nodes + 1, max_nodes);
        }
        return curr_nodes;
    } else {
        return curr_nodes;
    }
    cout<<i1<<endl;
    cout<<i2<<endl;
    cout<<i3<<endl;
    cout<<i4<<endl;
    cout<<i5<<endl;
}


#endif //RECURSION_NODE_H
