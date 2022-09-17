//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

#include "Node.h"
#include "Tree.h"

template<typename T>
void scan(Node<T> *tree) {
    for (auto &child: tree->children)
        scan(child);
}

template<typename T>
int max_depth(Node<T> *tree) {
    std::list<int> depths;
    int m_depth;

    // data only from the children
    if (tree->children.empty()) {
        m_depth = 0; // this should be seen as depth only from the children
    } else {
        for (auto &child: tree->children) {
            auto ret = max_depth(child);
            depths.push_back(ret);
        }
        m_depth = max_utils(depths);
    }

    //for the father
    m_depth++;

    return m_depth;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 1
template<typename T>
int min_depth(Node<T> *tree) {
    std::list<int> depths;
    int m_depth;

    // the objective here is only to handle data that comes from children only, ignoring completely the father
    if (tree->children.empty()) {
        m_depth = 0; // this should be seen as depth only from the children
    } else {
        for (auto &child: tree->children) {
            auto ret = min_depth(child);
            depths.push_back(ret);
        }
        m_depth = min_utils(depths);
    }

    //for the father
    m_depth++;

    return m_depth;
}

template<typename T>
int how_many(Node<T> *tree) {
    std::list<int> nodes;
    int h_many;

    //the assumption is that behavior differs only in 2 cases, no children, one or more children
    // data only from the children
    if (tree->children.empty()) {
        h_many = 0; // see here, how many children below the current node
    } else {
        for (auto &child: tree->children) {
            auto ret = how_many(child);
            nodes.push_back(ret);
        }
        h_many = sum_utils(nodes);
    }

    //for the father
    h_many++;

    return h_many;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
template<typename T>
T max_value(Node<T> *tree) {
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = max_value(child);
        ll.push_back(ret);
    }
    ll.push_back(*tree->item);
    return max_utils(ll);
}

template<typename T>
T min_value(Node<T> *tree) {
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = min_value(child);
        ll.push_back(ret);
    }
    ll.push_back(*tree->item);
    return min_utils(ll);
}

#endif //RECURSION_BASIC_H
