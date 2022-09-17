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
    if (tree->children.empty()) {
        m_depth = 0; // from the children
        m_depth++; // for the father
    } else {
        for (auto &child: tree->children) {
            auto ret = max_depth(child);
            depths.push_back(ret);
        }
        m_depth = max_utils(depths);
        m_depth++;
    }
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
        m_depth++; // for the father (preparing the value to be return on top arrow of the diagram)
    } else {
        for (auto &child: tree->children) {
            auto ret = min_depth(child);
            depths.push_back(ret);
        }
        m_depth = min_utils(depths);
        m_depth++;
    }

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
        h_many++; // for the father
    } else {
        for (auto &child: tree->children) {
            auto ret = how_many(child);
            nodes.push_back(ret);
        }
        h_many = sum_utils(nodes); // from the children
        h_many++; // for the father
    }

    return h_many;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
template<typename T>
T max_value(Node<T> *tree) {
    std::list<int> maxes;
    int m_val;

    // the objective here is to prepare data from the children to be assimilated as the father in the computation phase
    // ideally we should make two separate computation, if the node has no child and if it does,
    // but when possible to have just one computation phase I think it's better
    // out of this if else we should have set all the variables of before ready to be returned
    if (tree->children.empty()) {
        m_val = *tree->item; // this should be seen as depth only from the children
    } else {
        for (auto &child: tree->children) {
            auto ret = min_depth(child);
            maxes.push_back(ret);
        }
        maxes.push_back(*tree->item);
        m_val = max_utils(maxes);
    }

    return m_val;
}

template<typename T>
T min_value(Node<T> *tree) {
    std::list<int> minima;
    int m_val;

    if (tree->children.empty()) {
        m_val = *tree->item; // this should be seen as depth only from the children
    } else {
        for (auto &child: tree->children) {
            auto ret = min_depth(child);
            minima.push_back(ret);
        }
        minima.push_back(*tree->item);
        m_val = min_utils(minima);
    }

    return m_val;
}

template<typename T>
T how_many_like_this(Node<T> *tree, T like) {
    std::list<int> nodes;
    int num_of_nodes;

    if (tree->children.empty()) {
        num_of_nodes = 0;
    } else {
        for (auto &child: tree->children) {
            auto ret = how_many_like_this(child, like);
            nodes.push_back(ret);
        }
        num_of_nodes = sum_utils(nodes);
    }

    if (*tree->item == like)
        num_of_nodes++;

    return num_of_nodes;
}

#endif //RECURSION_BASIC_H
