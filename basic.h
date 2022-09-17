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
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = min_depth(child);
        ll.push_back(ret);
    }

    int min_depth_as_children_were_root;
    if (tree->children.empty())
        min_depth_as_children_were_root = 0;
    else
        min_depth_as_children_were_root = min_utils(ll);
    return 1 + min_depth_as_children_were_root;
}

template<typename T>
int how_many(Node<T> *tree) {
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = how_many(child);
        ll.push_back(ret);
    }

    int how_many_below_curr;
    if (tree->children.empty())
        how_many_below_curr = 0;
    else
        how_many_below_curr = std::accumulate(ll.begin(), ll.end(), 0);
    return 1 + how_many_below_curr;
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
