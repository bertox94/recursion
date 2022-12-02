//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_FATHERS_H
#define RECURSION_FATHERS_H

#include "../Node.h"

/**
 * Number of fathers with a specified number of children
 */
template<typename T>
int number_of_fathers_with_no_child(Node<T> *node) {
    if (node->has_children()) {
        int count = 0;
        for (auto &child: node->children) {
            auto child_count = number_of_fathers_with_no_child(child);
            count += child_count;
        }
        return count;
    } else {
        return 1;
    }
}

template<typename T>
int number_of_fathers_with_single_child(Node<T> *node) {
    if (node->has_children()) {
        int count = 0;
        for (auto &child: node->children) {
            auto child_count = number_of_fathers_with_no_child(child);
            count += child_count;
        }
        count += node->children.size == 1 ? 1 : 0;
        return count;
    } else {
        return 0;
    }
}

template<typename T>
int number_of_fathers_with_specified_number_of_children(Node<T> *node, int num_of_children) {
    if (node->has_children()) {
        int count = 0;
        for (auto &child: node->children) {
            auto child_count = number_of_fathers_with_specified_number_of_children(child, num_of_children);
            count += child_count;
        }
        count += node->children.size() == num_of_children ? 1 : 0;
        return count;
    } else {
        if (node->children.size() == num_of_children) {
            return 1;
        } else {
            return 0;
        }
    }
}

/**
 * Number of fathers with a specified number of children
 */
template<typename T>
std::pair<bool, int> depth_of_the_deepest_father_with_at_least_one_child(Node<T> *node, int curr_depth) {

    if (node->has_children()) {
        int max_depth = -1;
        bool valid = false;
        for (auto &child: node->children) {
            auto [child_valid, child_max_depth] = depth_of_the_deepest_father_with_at_least_one_child(child,
                                                                                                      curr_depth + 1);
            valid |= child_valid;
            max_depth = child_valid ? std::max(max_depth, child_max_depth) : max_depth;
        }
        if (valid) {
            //even if curr has childre, curr_depth is less than children's depth
            return {true, max_depth};
        } else {
            // we are in the branch node->has_children() == true, so at least one child is verified.
            return {true, curr_depth};
        }
    } else {
        // we are in the branch node->has_children() == false;
        return {false, std::rand()};
    }
}

// do also by passing depth as parameter, but leave also those here with height so you can see the differences
// father must be treated differently of the children
template<typename T>
std::pair<bool, int> depth_of_the_deepest_father_with_single_child(Node<T> *node, int curr_depth) {

    if (node->has_children()) {
        int max_depth = -1;
        bool valid = false;
        for (auto &child: node->children) {
            auto [child_valid, child_max_depth] = depth_of_the_deepest_father_with_single_child(child,
                                                                                                curr_depth + 1);
            valid |= child_valid;
            max_depth = child_valid ? std::max(max_depth, child_max_depth) : max_depth;
        }
        if (valid) {
            // curr is uninfluential here, either it has a single child or not,
            // its depth is surely less than that from the children
            return {true, max_depth};
        } else {
            //all children has no father with single child
            if (node->children.size() == 1) {
                return {true, curr_depth};
            } else {
                //nope, not even curr
                return {false, std::rand()};
            }
        }
    } else {
        return {false, std::rand()};
    }
}

template<typename T>
std::pair<bool, int>
depth_of_the_deepest_father_with_specified_number_of_children(Node<T> *node, int current_depth, int children) {

    if (node->has_children()) {
        int max_depth = -1;
        bool valid = false;
        for (auto &child: node->children) {
            auto [child_valid, child_max_depth] = depth_of_the_deepest_father_with_specified_number_of_children(child,
                                                                                                                current_depth +
                                                                                                                1);
            valid |= child_valid;
            max_depth = child_valid ? std::max(max_depth, child_max_depth) : max_depth;
        }
        if (valid) {
            // curr is uninfluential here, either it has a single child or not,
            // its depth is surely less than that from the children.
            return {true, max_depth};
        } else {
            //all children has no father with specified num. of child
            if (node->children.size() == children) {
                return {true, current_depth};
            } else {
                //nope, not even curr
                return {false, std::rand()};
            }
        }
    } else {
        if (node->children.size() == children) {
            return {true, current_depth};
        } else {
            return {false, std::rand()};
        }
    }
}

template<typename T>
std::tuple<bool, int, int> //do the same also with min, so that you test all properties (i.e. testproperty on children branch)
number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(Node<T> *node, int current_depth,
                                                                                   int children) {
    std::list<std::tuple<bool, int, int>> ll;
    for (auto &child: node->children) {
        auto ret = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(child,
                                                                                                      current_depth + 1,
                                                                                                      children);
        ll.emplace_back(ret);
    }

    if (node->children.size() == children)
        ll.emplace_back(true, current_depth, 1);

    bool found;
    int depth;
    int number;

    ll.erase(std::remove_if(ll.begin(), ll.end(), [](auto &el) { return !std::get<0>(el); }), ll.end());
    if (!ll.empty()) {
        found = true;
        depth = std::get<1>(*max_element(ll.begin(), ll.end(),
                                         [](auto &l, auto &r) { return get<1>(l) < get<1>(r); }));
        number = accumulate(
                ll.begin(), ll.end(), 0,
                [&](auto acc, auto tpl) {
                    return std::get<1>(tpl) == depth ? acc + std::get<2>(tpl) : acc;
                }
        );
    } else
        found = false;

    return {found, depth, number};
}

#endif //RECURSION_FATHERS_H
