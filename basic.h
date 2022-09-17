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
    int m_depth;

    if (tree->children.empty()) {
        m_depth = 0; // from the children
        m_depth++; // for the father
    } else {
        std::list<int> depths;
        for (auto &child: tree->children) {
            auto ret = max_depth(child);
            depths.push_back(ret);
        }
        m_depth = max_utils(depths); // from the children
        m_depth++; // for the father
    }

    return m_depth;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 1
template<typename T>
int min_depth(Node<T> *tree) {
    int m_depth;
    if (tree->children.empty()) {
        m_depth = 0;
    } else {
        std::list<int> depths;
        for (auto &child: tree->children)
            depths.push_back(min_depth(child));
        m_depth = min_utils(depths);
    }
    m_depth++;
    return m_depth;
}

template<typename T>
int how_many(Node<T> *tree) {
    int h_many;
    if (tree->children.empty()) {
        h_many = 0;
    } else {
        std::list<int> nodes;
        for (auto &child: tree->children)
            nodes.push_back(how_many(child));
        h_many = sum_utils(nodes);
    }
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
    int m_val;
    if (tree->children.empty()) {
        //empty statement for the children
        m_val = *tree->item; // for the father
    } else {
        std::list<int> maxes;
        for (auto &child: tree->children)
            maxes.push_back(max_value(child));
        m_val = max_utils(maxes); // for the children
        m_val = std::max(m_val, *tree->item); // for the father
    }
    return m_val;
}

template<typename T>
T min_value(Node<T> *tree) {
    int m_val;
    if (tree->children.empty()) {
        m_val = *tree->item;
    } else {
        std::list<int> minima;
        for (auto &child: tree->children)
            minima.push_back(min_value(child));
        minima.push_back(*tree->item);
        m_val = min_utils(minima);
    }

    return m_val;
}

template<typename T>
T how_many_like_this(Node<T> *tree, T like) {
    int num_of_nodes;
    if (tree->children.empty()) {
        num_of_nodes = 0;
    } else {
        std::list<int> nodes;
        for (auto &child: tree->children)
            nodes.push_back(how_many_like_this(child, like));
        num_of_nodes = sum_utils(nodes);
    }
    if (*tree->item == like)
        num_of_nodes++;
    return num_of_nodes;
}

template<typename T>
list<T> list_nodes(Node<T> *tree) {
    std::list<int> nodes;
    if (tree->children.empty()) {
        // no need to do anything for the children, for the father will be done later once for this two cases
    } else {
        std::list<int> children_nodes;
        for (auto &child: tree->children)
            children_nodes.splice(children_nodes.end(), list_nodes(child));
        nodes = children_nodes;
    }
    nodes.push_back(*tree->item);
    return nodes;
}

//define the height of a node as the maximum of the heights of its children +1
template<typename T>
std::pair<int, int> number_of_nodes_at_depth_one(Node<T> *tree) {
    std::list<int> ll;
    for (auto &child: tree->children) {
        auto ret = number_of_fathers_with_single_child(child);
        ll.push_back(ret);
    }

    //Then, find a way to treat the father as the children
    if (tree->children.size() == 0) { // leaf (usually always present)
        ll.emplace_back(0);
    } else if (tree->children.size() == 1) //specific case that need attention
        ll.emplace_back(1);
    else {
        // nothing relevant here
    }

    //Compute what to return
    int num = sum_utils(ll);

    return {};
}

#endif //RECURSION_BASIC_H
