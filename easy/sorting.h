//
// Created by Halib on 03.10.2022.
//

#ifndef RECURSION_SORTING_H
#define RECURSION_SORTING_H

#include "../Node.h"

template<typename T>
int sorted(Node<T> *node) {
    int height;
    if (node->has_children()) {
        std::sort(node->children.begin(), node->children.end(),
                  [&](auto left, auto right) {
                      auto l = sorted(left);
                      auto r = sorted(right);
                      height = std::max(l, r) + 1;
                      return l < r;
                  });
    } else {
        height = 0;
    }
    return height;
}


#endif //RECURSION_SORTING_H
