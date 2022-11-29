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
            auto child_max_num = how_many(child);
            children_max_nums.push_back(child_max_num);
        }
        auto children_max_num = *max_element(children_max_nums.begin(), children_max_nums.end());
        max_num = std::max(children_max_num, (unsigned long)node->children.size());
    } else {
        max_num = 0;
    }

    return max_num;
}

// to reason for leaves, just say, the tree is of one element. Then max num is exactly that,
// no need to consider everything else. Basically just assume the entire tree is a leaf.
// RightAttr: [depth, target_depth]
// LeftAttr: [valid, max_num]
template<typename T>
unsigned long max_num_of_direct_children_at_depth(Node<T> *node, unsigned long depth) {
    auto Rtemp = Rfather;
    Rtemp.depth++;
    auto R = Rtemp;

    LeftAttr<T> L;
    if (node->has_children()) {
        std::list<int> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = max_num_of_direct_children_at_depth(child, R);
            if (Lchild.valid)
                Lchildren.push_back(Lchild.num);
        }
        if (!Lchildren.empty()) { // then you can assume that the current depth is not the target_depth depth
            L.num = *max_element(Lchildren.begin(), Lchildren.end());
            L.valid = true;
        } else if (R.depth == R.target_depth) { // target_depth depth = current depth
            L.num = node->children.size();
            L.valid = true;
        } else // target_depth depth < current depth
            L.valid = false;
    } else {
        if (R.depth == R.target_depth) {
            L.num = node->children.size();
            L.valid = true;
        } else
            L.valid = false;
    }

    return L;
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
            m_num = *min_element(minima.begin(), minima.end());
        }
    }

    return {valid, m_num};
}

#endif //RECURSION_CHILDREN_H
