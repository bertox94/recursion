//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_CHILDREN_H
#define RECURSION_CHILDREN_H

#include "../Node.h"
#include "../Tree.h"

template<typename T>
int max_num_of_direct_children(Node<T> *node) {
    int m_num;

    if (node->is_leaf()) {
        m_num = 0;
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = max_num_of_direct_children(child);
            ll.push_back(ret);
        }
        ll.push_back(node->children.size());
        m_num = max_utils(ll);
    }

    return m_num;
}

// to reason for leaves, just say, the tree is of one element. Then max num is exactly that,
// no need to consider everything else. Basically just assume the entire tree is a leaf.
// R: [depth, target_depth]
template<typename T>
std::tuple<bool, int> max_num_of_direct_children_at_depth(Node<T> *node, std::pair<int, int> Rfather) {
    auto Rtemp = Rfather;
    Rtemp.first++;
    auto R = Rtemp;

    std::pair<bool, int> L;
    int m_num;
    bool valid;
    auto test_property = [](int curr, int target) -> bool { return curr == target; };
    if (node->is_leaf()) {
        if (R.first == R.second) {
            m_num = node->children.size();
            valid = true;
        } else
            valid = false;
    } else {
        std::list<std::tuple<int, int>> ll;
        for (auto &child: node->children) {
            auto ret = max_num_of_direct_children_at_depth(child, R);
            ll.push_back(ret);
        }
        std::list<int> maxes;
        for (auto &tpl: ll) {
            if (std::get<0>(tpl))
                maxes.push_back(std::get<1>(tpl));
        }
        if (test_property(curr_depth, target_depth)) {
            maxes.push_back(node->children.size());
        }
        if (maxes.empty()) {
            valid = false;
        } else {
            valid = true;
            m_num = max_utils(maxes);
        }
    }

    return {valid, m_num};
}

// min_num_of_direct_children_at_depth(node,1) should be 0
// be useful to test there there are leaf at depth one, as usually shown in min_dept(...)
template<typename T>
std::tuple<bool, int> min_num_of_direct_children_at_depth(Node<T> *node, int curr_depth, int target_depth) {
    curr_depth++;
    int m_num;
    bool valid;
    auto test_property = [](int curr, int target) -> bool { return curr == target; };
    if (node->is_leaf()) {
        if (test_property(curr_depth, target_depth)) {
            m_num = node->children.size();
            valid = true;
        } else
            valid = false;
    } else {
        std::list<std::tuple<int, int>> ll;
        for (auto &child: node->children) {
            auto ret = min_num_of_direct_children_at_depth(child, curr_depth, target_depth);
            ll.push_back(ret);
        }
        std::list<int> minima;
        for (auto &tpl: ll) {
            if (std::get<0>(tpl))
                minima.push_back(std::get<1>(tpl));
        }
        if (test_property(curr_depth, target_depth)) {
            minima.push_back(node->children.size());
        }
        if (minima.empty()) {
            valid = false;
        } else {
            valid = true;
            m_num = min_utils(minima);
        }
    }

    return {valid, m_num};
}

#endif //RECURSION_CHILDREN_H
