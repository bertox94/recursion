//
// Created by Halib on 03.10.2022.
//

#ifndef RECURSION_PRINTING_H
#define RECURSION_PRINTING_H

#include "../Node.h"

//here you see that they were right, right is prepared to be what is needed for the current by the parent
//here you see how thr right param is correctly used
// so right is used in the curr node as it is passed from the parent, then changed only to be passed to its child
template<typename T>
void print(Node<T> *node, int spacing = 0) {
    if (node->has_children()) {
        std::cout << std::string(spacing, ' ') << (spacing > 0 ? "+ " : "") << node->item << ":" << std::endl;
        for (auto &child: node->children) {
            print(child, spacing + 3);
        }
    } else {
        std::cout << std::string(spacing, ' ') << "- " << node->item << std::endl;
    }
}

// S-> num|num[( S)+]
template<typename T>
void to_string(Node<T> *node) {
    std::cout << node->item;
    if (node->has_children()) {
        std::cout << "[";
        bool flag = true;
        for (auto &child: node->children) {
            std::cout << " "; // what will follow will be either (1): X[... or X
            to_string(child);
            flag = false;
        }
        std::cout << "]";
    }
}


#endif //RECURSION_PRINTING_H
