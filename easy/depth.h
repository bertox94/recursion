//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_DEPTH_H
#define RECURSION_DEPTH_H

#include "../Node.h"
#include "../Tree.h"
/**
 * DEPTH
 * The depth of a node is the depth of the father +1. The father has depth 0.
 */
// here you can see that the dealing with the father variable and the computation of the returned variable are split
// probably because we return a pair of two values
// height is computed in each branch, nodes once outside the branches
// note that it is superfluous to return the height, yet in this case we need to return it anyway
template<typename T>
std::pair<int, int> number_of_nodes_at_depth_zero(Node<T> *node, int current_depth) {
    return {};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_depth_one(Node<T> *node, int current_depth) {
    return {};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_specific_depth(Node<T> *node, int current_depth, int target_depth) {
    return {};
}

#endif //RECURSION_DEPTH_H
