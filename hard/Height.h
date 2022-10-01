//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_HEIGHT_H
#define RECURSION_HEIGHT_H

#include "../Node.h"
#include "../Tree.h"

/**
 * HEIGHT
 * The height of a node is the maximum of the heights of its children +1. If it has no children, it is 0.
 */
// here you can see that the dealing with the father variable and the computation of the returned variable are split
// probably because we return a pair of two values
// height is computed in each branch, nodes once outside the branches
// note that it is superfluous to return the height at height 0, yet due to the mechanism of recursion used here,
// we need to return it anyway

// each one pass values about itself only, do not prepare nothing, what I get in curr, from below,
// is the height from the childrem I must add +1. Same for depth (adjust before). node is the only exception.
// It's like hook to the partner and pass them your values, without preparing anything for him.
// In a node, those operation are done before the recursive call (at the beginning, since an empty recursive call is done if it is a leaf),
// operation on values from children are done after the rec call (they are done only in the else branch since only there there is a rec. call.).
template<typename T>
std::pair<int, int> number_of_nodes_at_height_zero(Node<T> *node) {
    std::pair<int, int> L;
    if (node->has_children()) {
        std::list<std::pair<int, int>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = number_of_nodes_at_height_zero(child);
            Lchildren.push_back(Lchild);
        }
        int height, num; // instead of Ltemp
        height = (*max_element(Lchildren.begin(), Lchildren.end(),
                               [](auto &l, auto &r) { return l.first < r.first; })).first + 1;
        num = accumulate(
                Lchildren.begin(), Lchildren.end(), 0,
                [](auto acc, auto pair) {
                    return acc + pair.second;
                });
        L = {height, num};
    } else {
        L = {0, 1};
    }

    return L;
}

template<typename T>
std::pair<int, int> number_of_nodes_at_height_one(Node<T> *node) {
    std::pair<int, int> L;
    if (node->has_children()) {
        std::list<std::pair<int, int>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = number_of_nodes_at_height_zero(child);
            Lchildren.push_back(Lchild);
        }
        int height, num; // instead of Ltemp
        height = (*max_element(Lchildren.begin(), Lchildren.end(),
                               [](auto &l, auto &r) { return l.first < r.first; })).first + 1;
        num = accumulate(
                Lchildren.begin(), Lchildren.end(), 0,
                [](auto &acc, auto &pair) {
                    return acc + pair.second;
                });

        if (height == 1)
            num++;

        L = {height, num};
    } else {
        L = {0, 0};
    }

    return L;
}

//RightAttr: specified height
template<typename T>
std::pair<int, int> number_of_nodes_at_specific_height(Node<T> *node, int Rfather) {
    int R = Rfather;
    std::pair<int, int> L;
    if (node->has_children()) {
        std::list<std::pair<int, int>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = number_of_nodes_at_specific_height(child, R);
            Lchildren.push_back(Lchild);
        }
        int height, num; // instead of Ltemp
        height = (*max_element(Lchildren.begin(), Lchildren.end(),
                               [](auto &l, auto &r) { return l.first < r.first; })).first + 1;
        num = accumulate(
                Lchildren.begin(), Lchildren.end(), 0,
                [](auto acc, auto pair) {
                    return acc + pair.second;
                });

        if (height == R)
            num++;

        L = {height, num};
    } else {
        int num = 0;
        if (R == 0)
            num++;
        L = {0, num};
    }

    return L;
}





#endif //RECURSION_HEIGHT_H
