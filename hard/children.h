//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_CHILDREN_H
#define RECURSION_CHILDREN_H

#include <utility>

#include "../Node.h"

// R takes care of preparing the right value for the children, L do not need to
// param need to be right, returned values are right for the function itself, not the function and the caller (usually)

template<typename T>
unsigned long max_num_of_direct_children(Node<T> *node) {

    unsigned long max_num;
    if (node->has_children()) {
        std::list<unsigned long> children_max_nums;
        for (auto &child: node->children) {
            auto child_max_num = max_num_of_direct_children(child);
            children_max_nums.push_back(child_max_num);
        }
        auto children_max_num = *max_element(children_max_nums.begin(), children_max_nums.end());
        max_num = std::max(children_max_num, (unsigned long) node->children.size());
    } else {
        max_num = 0;
    }

    return max_num;
}

template<typename T>
std::tuple<bool, unsigned long>
max_num_of_direct_children_at_depth(Node<T> *node, unsigned long depth, unsigned long t_depth) {
    unsigned long max_num;
    bool valid;

    if (node->has_children()) {
        if (depth == t_depth) {
            max_num = node->children.size();
            valid = true;
        } else if (depth > t_depth) {
            valid = false;
        } else {
            std::list<unsigned long> children_max_nums;
            for (auto &child: node->children) {
                auto [child_valid, child_max_num] = max_num_of_direct_children_at_depth(child, depth + 1, t_depth);
                if (child_valid)
                    children_max_nums.push_back(child_max_num);
            }
            if (children_max_nums.empty()) {
                valid = false;
            } else {
                max_num = *max_element(children_max_nums.begin(), children_max_nums.end());
                valid = true;
            }
        }
    } else {
        if (depth == t_depth) {
            valid = true;
            max_num = 0;
        } else
            valid = false;
    }

    return {valid, max_num};
}

// min_num_of_direct_children_at_depth(node,1) should be 0
// be useful to test there there are leaf at depth one, as usually shown in min_dept(...)
template<typename T>
std::tuple<bool, unsigned long>
min_num_of_direct_children_at_depth(Node<T> *node, unsigned long depth, unsigned long t_depth) {
    unsigned long min_num;
    bool valid;

    if (node->has_children()) {
        if (depth == t_depth) {
            min_num = node->children.size();
            valid = true;
        } else if (depth > t_depth) {
            valid = false;
        } else {
            std::list<unsigned long> children_min_nums;
            for (auto &child: node->children) {
                auto [child_valid, child_min_num] = min_num_of_direct_children_at_depth(child, depth + 1, t_depth);
                if (child_valid)
                    children_min_nums.push_back(child_min_num);
            }
            if (children_min_nums.empty()) {
                valid = false;
            } else {
                min_num = *min_element(children_min_nums.begin(), children_min_nums.end());
                valid = true;
            }
        }
    } else {
        if (depth == t_depth) {
            valid = true;
            min_num = 0;
        } else
            valid = false;
    }

    return {valid, min_num};
}

template<typename T>
std::tuple<bool, unsigned long>
max_size_of_subtrees_from_depth_and_below(Node<T> *node, unsigned long depth, unsigned long t_depth) {

    if (node->has_children()) {
        if (depth >= t_depth) {
            unsigned long max_num = 0;
            for (auto &child: node->children) {
                auto [_, child_max_num] = max_size_of_subtrees_from_depth_and_below(child, depth + 1,
                                                                                    t_depth);
                max_num += child_max_num;
            }
            return {true, max_num + 1};
        } else {
            std::list<unsigned long> children_max_nums;
            bool valid = false;
            for (auto &child: node->children) {
                auto [child_valid, child_max_num] = max_size_of_subtrees_from_depth_and_below(child, depth + 1,
                                                                                              t_depth);
                valid |= child_valid;
                if (child_valid)
                    children_max_nums.push_back(child_max_num);
            }
            return {valid, valid ? *max_element(children_max_nums.begin(),
                                                children_max_nums.end()) : std::rand()};
        }
    } else {
        if (depth >= t_depth) {
            return {true, 1};
        } else {
            return {false, std::rand()};
        }
    }
}

// simple as that:
//      for a node in the middle, we return to the father the sum of the results of the children + the num of direct children of that node,
//      for a leaf it would just pass 0 to its father.
// By the way this just means, count the number of nodes in the tree
template<typename T>
unsigned long num_of_direct_children(Node<T> *node) {

    if (node->has_children()) {
        unsigned long count = 0;
        for (auto &child: node->children) {
            auto child_count = num_of_direct_children(child);
            count += child_count;
        }
        return node->children.size() + count;
    } else {
        return 0;
    }

}

template<typename T>
std::tuple<bool, unsigned long>
num_of_direct_children_from_depth_and_below(Node<T> *node, unsigned long depth, unsigned long t_depth) {

    if (node->has_children()) {
        if (depth >= t_depth) {
            unsigned long count = 0;
            for (auto &child: node->children) {
                auto [_, child_max_num] = num_of_direct_children_from_depth_and_below(child, depth + 1,
                                                                                      t_depth);
                count += child_max_num;
            }
            return {true, node->children.size() + count};
        } else {
            unsigned long count = 0;
            bool valid = false;
            for (auto &child: node->children) {
                auto [child_valid, child_max_num] = num_of_direct_children_from_depth_and_below(child, depth + 1,
                                                                                                t_depth);
                valid |= child_valid;
                if (child_valid)
                    count += child_max_num;
            }
            return {valid, count};
        }
    } else {
        if (depth >= t_depth)
            return {true, 0};
        else
            return {false, std::rand()};
    }
}

#endif //RECURSION_CHILDREN_H
