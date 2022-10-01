//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_ADVANCED_H
#define RECURSION_ADVANCED_H

#include "Node.h"
#include "Tree.h"

/**
 * HEIGHT
 * The height of a node is the maximum of the heights of its children +1. If it has no children, it is 0.
 */
// here you can see that the dealing with the father variable and the computation of the returned variable are split
// probably because we return a pair of two values
// height is computed in each branch, nodes once outside the branches
// note that it is superfluous to return the height at height 0, yet due to the mechanism of recursion used here,
// we need to return it anyway

// each one pass values about itself only, do not prepare nothing, what I get in curr, from below,
// is the height from the childrem I must add +1. Same for depth (adjust before). node is the only exception.
// It's like hook to the partner and pass them your values, without preparing anything for him.
// In a node, those operation are done before the recursive call (at the beginning, since an empty recursive call is done if it is a leaf),
// operation on values from children are done after the rec call (they are done only in the else branch since only there there is a rec. call.).
template<typename T>
std::pair<int, int> number_of_nodes_at_height_zero(Node<T> *node) {
    std::list<std::pair<int, int>> ll;
    for (auto &child: node->children) {
        auto ret = number_of_nodes_at_height_zero(child);
        ll.push_back(ret);
    }

    int num;
    int height;

    if (node->is_leaf())
        height = 0;
    else
        height = (*max_element(ll.begin(), ll.end(),
                               [](auto &l, auto &r) { return l.first < r.first; })).first + 1;

    if (height == 0)
        ll.emplace_back(height, 1);

    num = accumulate(
            ll.begin(), ll.end(), 0,
            [](auto &acc, auto &pair) {
                return acc + pair.second;
            });

    return {height, num};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_height_one(Node<T> *node) {
    std::list<std::pair<int, int>> ll;
    for (auto &child: node->children) {
        auto ret = number_of_nodes_at_height_one(child);
        ll.push_back(ret);
    }

    int num;
    int height;

    if (node->is_leaf())
        height = 0;
    else
        height = (*max_element(ll.begin(), ll.end(),
                               [](auto &l, auto &r) { return l.first < r.first; })).first + 1;

    if (height == 1)
        ll.emplace_back(height, 1);

    num = accumulate(
            ll.begin(), ll.end(), 0,
            [&](auto acc, auto pair) {
                return acc + pair.second;
            });

    return {height, num};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_specific_height(Node<T> *node, int specified_height) {
    std::list<std::pair<int, int>> ll;
    for (auto &child: node->children) {
        auto ret = number_of_nodes_at_specific_height(child, specified_height);
        ll.push_back(ret);
    }

    // the following are left unspecified because we don't know yet their value
    int num;
    int height;

    if (node->is_leaf())
        height = 0;
    else
        height = (*max_element(ll.begin(), ll.end(),
                               [](auto &l, auto &r) { return l.first < r.first; })).first + 1;

    if (height == specified_height)
        ll.emplace_back(height, 1);

    num = accumulate(
            ll.begin(), ll.end(), 0,
            [&](auto acc, auto pair) {
                return acc + pair.second;
            });

    return {height, num};
}


template<typename T>
list<T> list_nodes(Node<T> *node) {
    std::list<int> nodes;
    if (node->is_leaf()) {
        // for the children, the list is already empty, no need to do anything
        // for the father will be done later once for this two cases
        nodes.push_back(*node->item);
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = list_nodes(child);
            ll.splice(ll.end(), ret);
        }
        ll.push_back(*node->item);
        nodes = ll;
    }

    return nodes;
}

template<typename T>
std::list<std::tuple<int, int>> list_nodes_II(Node<T> *node) {
    std::list<std::tuple<int, int>> L;
    if (node->has_children()) {
        for (auto &child: node->children) {
            auto Ltemp = list_nodes_II(child);

            for (auto &tpl1: Ltemp) {
                bool found = false;
                for (auto &tpl2: L) {
                    if (std::get<1>(tpl1) == std::get<1>(tpl2)) {
                        std::get<0>(tpl2) += std::get<0>(tpl1);
                        found = true;
                        break;
                    }
                }
                if (!found)
                    L.emplace_back(std::get<0>(tpl1), std::get<1>(tpl1));
            }
        }
        bool found = false;
        for (auto &tpl: L) {
            if (*node->item == std::get<1>(tpl)) {
                std::get<0>(tpl)++;
                found = true;
                break;
            }
        }
        if (!found)
            L.emplace_back(1, *node->item);
    } else {
        L.emplace_back(1, *node->item);
    }

    return L;
}

template<typename T>
std::tuple<std::list<std::tuple<int, int>>, std::list<int>> duplicates(Node<T> *node) {
    std::tuple<std::list<std::tuple<int, int>>, std::list<int>> L;
    if (node->has_children()) {
        for (auto &child: node->children) {
            auto Ltemp = duplicates(child);

            // We assume that one number can either be in L list or L singleton, not both

            // elements in child singleton
            //      may appear in L list
            //          --> increase number of that element in L by 1
            //      may appear in L singletons
            //          --> push {2, elem} in L list
            //          --> remove elem from L singletons
            //      may not be in either of them
            //          --> append elem to L singletons

            // elements in child list
            //      may appear in L singletons
            //          --> append elem to L list and increment by one the number of occurrences (because we assume that one number can either be in L list or L singleton, not both)
            //          --> remove elem from L singletons
            //      may appear in L list
            //          --> increase number of that element in L by the corresponding number
            //      may not be in either of them
            //          --> append elem to L list

            for (auto &item: std::get<1>(Ltemp)) {
                bool found = false;
                for (auto &tpl: std::get<0>(L)) {
                    if (item == std::get<1>(tpl)) {
                        std::get<0>(tpl)++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (auto it = std::get<1>(L).begin(); it != std::get<1>(L).end(); it++) {
                        if (item == *it) {
                            std::get<0>(L).emplace_back(2, item);
                            it = std::get<1>(L).erase(it);
                            found = true;
                            break;
                        }
                    }
                }
                if (!found)
                    std::get<1>(L).push_back(item);
            }

            for (auto &tpl1: std::get<0>(Ltemp)) {
                bool found = false;
                for (auto it = std::get<1>(L).begin(); it != std::get<1>(L).end(); it++) {
                    if (std::get<1>(tpl1) == *it) {
                        std::get<0>(L).emplace_back(std::get<0>(tpl1) + 1, std::get<1>(tpl1));
                        std::get<1>(L).erase(it);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (auto &tpl2: std::get<0>(L)) {
                        if (std::get<1>(tpl1) == std::get<1>(tpl2)) {
                            std::get<0>(tpl2) += std::get<0>(tpl1);
                            found = true;
                            break;
                        }
                    }
                }
                if (!found)
                    std::get<0>(L).emplace_back(std::get<0>(tpl1), std::get<1>(tpl1));
            }
        }

        //curr that appear in L list --> increase number
        //curr that appear in L singleton --> move them both to L list
        //curr that do not appear in L singleton --> append them to L singleton
        bool found = false;
        for (auto &tpl: std::get<0>(L)) {
            if (*node->item == std::get<1>(tpl)) {
                std::get<0>(tpl)++;
                found = true;
                break;
            }
        }
        if (!found) {
            for (auto it = std::get<1>(L).begin(); it != std::get<1>(L).end(); it++) {
                if (*node->item == *it) {
                    std::get<0>(L).emplace_back(2, *node->item);
                    it = std::get<1>(L).erase(it);
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            std::get<1>(L).push_back(*node->item);

    } else {
        std::get<1>(L).push_back(*node->item);
    }


    return L;
}


#endif //RECURSION_ADVANCED_H
