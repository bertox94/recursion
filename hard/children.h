//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_CHILDREN_H
#define RECURSION_CHILDREN_H

#include <utility>

#include "../Node.h"

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
unsigned long max_num_of_direct_children(Node<T> *node) {

    if (node->has_children()) {
        unsigned long max_num = node->children.size();
        for (auto &child: node->children) {
            auto child_max_num = max_num_of_direct_children(child);
            max_num = std::max(max_num, child_max_num);
        }
        return max_num;
    } else {
        return 0;
    }
}

template<typename T>
std::tuple<bool, unsigned long>
max_num_of_direct_children_at_depth(Node<T> *node, unsigned long depth, unsigned long t_depth) {

    if (node->has_children()) {
        if (depth == t_depth) {
            return {true, node->children.size()};
        } else if (depth > t_depth) {
            return {false, std::rand()};
        } else {
            bool valid = false;
            unsigned long max_num = -1;
            for (auto &child: node->children) {
                auto [child_valid, child_max_num] = max_num_of_direct_children_at_depth(child, depth + 1, t_depth);
                valid |= child_valid;
                max_num = child_valid ? std::max(max_num, child_max_num) : max_num;
            }
            return {valid, max_num};
        }
    } else {
        if (depth == t_depth) {
            return {true, 0};
        } else {
            return {false, std::rand()};
        }
    }
}

// min_num_of_direct_children_at_depth(node,1) should be 0
// be useful to test there there are leaf at depth one, as usually shown in min_dept(...)
template<typename T>
std::tuple<bool, unsigned long>
min_num_of_direct_children_at_depth(Node<T> *node, unsigned long depth, unsigned long t_depth) {

    if (node->has_children()) {
        if (depth == t_depth) {
            return {true, node->children.size()};
        } else if (depth > t_depth) {
            return {false, std::rand()};
        } else {
            bool valid = false;
            std::list<unsigned long> children_min_nums;
            for (auto &child: node->children) {
                auto [child_valid, child_min_num] = min_num_of_direct_children_at_depth(child, depth + 1, t_depth);
                valid |= child_valid;
                if (child_valid)
                    children_min_nums.push_back(child_min_num);
            }
            return {valid, valid ? *min_element(children_min_nums.begin(),
                                                children_min_nums.end()) : std::rand()};
        }
    } else {
        if (depth == t_depth) {
            return {true, 0};
        } else {
            return {false, std::rand()};
        }
    }
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
