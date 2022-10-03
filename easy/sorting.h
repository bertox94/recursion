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
        std::vector<std::pair<Node<T> *, int>> ll;
        for (auto &child: node->children)
            ll.emplace_back(child, sorted(child));

        std::sort(ll.begin(), ll.end(),
                  [](auto left, auto right) { return left.second > right.second; });
        node->children.clear();
        for (auto &child: ll) {
            node->children.push_back(child.first);
        }
        height = (*max_element(ll.begin(), ll.end(), [](auto l, auto r) { return l.second < r.second; })).second + 1;
    } else {
        height = 0;
    }
    return height;
}


#endif //RECURSION_SORTING_H
