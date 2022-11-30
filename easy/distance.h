//
// Created by Halib on 07.10.2022.
//

#ifndef RECURSION_DISTANCE_H
#define RECURSION_DISTANCE_H

#include <tuple>
#include "../Node.h"

// it would be nice to know those two leafs, maybe identify them with the path from root to them
// each node must have exactly 2 direct children
template<typename T>
LeftAttr<T> max_distance(Node<T> *node, RightAttr<T> R) {
    LeftAttr<T> L;
    if (node->has_children()) {
        std::vector<LeftAttr<T>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = max_distance(child, RightAttr<T>(_depth(R.depth + 1)));
            Lchildren.push_back(Lchild);
        }
        // if child1.max_distance + child2.max_distance > max of children.max_distance_between_a_pair_of_leaves
        //L.max_distance = *max_element(Lchildren.begin(), Lchildren.end(),
        //                              [](auto l, auto r) { l->max_distance < r->max_distance; });
    }
}

#endif //RECURSION_DISTANCE_H
