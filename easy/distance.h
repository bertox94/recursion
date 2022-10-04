//
// Created by Halib on 03.10.2022.
//

#ifndef RECURSION_DISTANCE_H
#define RECURSION_DISTANCE_H

#include <tuple>
#include "../Node.h"

//it would be nice to know those two leafs, maybe identify them with the path from root to them
template<typename T>
std::tuple<int, int, int> max_distance(Node<T> *node, int depth) {
    std::vector<int> max_depths;
    std::vector<int> max_distances;
    std::vector<int> deepest_common_father;
    if (node->has_children()) {

    }
}

#endif //RECURSION_DISTANCE_H
