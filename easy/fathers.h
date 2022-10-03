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
    // the following are left unspecified for now because we don't know what value is it now
    // the data of the children can and usually must survive outside the if-else blocks, so it's declared here
    int num;
    auto test_property = [](Node<T> *node) -> bool { return node->children.empty(); };
    if (node->is_leaf()) {
        if (test_property(node))
            num = 1;
        else
            num = 0;
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = number_of_fathers_with_no_child(child);
            ll.push_back(ret);
        }
        num = accumulate(
                ll.begin(), ll.end(), 0,
                [](auto acc, auto item) {
                    return acc + item;
                });
        if (test_property(node))
            num++;
    }

    return num;
}

template<typename T>
int number_of_fathers_with_single_child(Node<T> *node) {
    int num;
    auto test_property = [](Node<T> *node) -> bool { return node->children.size() == 1; };
    if (node->is_leaf()) {
        if (test_property(node))
            num = 1;
        else
            num = 0;
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = number_of_fathers_with_single_child(child);
            ll.push_back(ret);
        }
        num = accumulate(
                ll.begin(), ll.end(), 0,
                [](auto acc, auto item) {
                    return acc + item;
                });
        if (test_property(node))
            num++;
    }

    return num;
}

template<typename T>
int number_of_fathers_with_specified_number_of_children(Node<T> *node, int num_of_children) {
    int num;
    auto test_property = [](Node<T> *node, int num_of_children) -> bool {
        return node->children.size() == num_of_children;
    };
    if (node->is_leaf()) {
        if (test_property(node, num_of_children))
            num = 1;
        else
            num = 0;
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = number_of_fathers_with_specified_number_of_children(child, num_of_children);
            ll.push_back(ret);
        }
        num = accumulate(
                ll.begin(), ll.end(), 0,
                [](auto acc, auto item) {
                    return acc + item;
                });
        if (test_property(node, num_of_children))
            num++;
    }

    return num;
}

/**
 * Number of fathers with a specified number of children
 */
template<typename T>
std::pair<bool, int> depth_of_the_deepest_father_with_at_least_one_child(Node<T> *node, int curr_depth) {
    curr_depth++;

    int depth;
    bool found;

    auto test_property = [](Node<T> *node) -> bool { return !node->children.empty(); };

    // the only difference between these two branches is that the first considers only the current,
    // while the other considers the children plus the current
    // the else will never be taken, yet we write it here for completeness
    // it comes easier to do the else branch before, because you are helped by the children
    // in the if branch, test the current and provide the results may be done at the same time, in the else branch usually no,
    // children are to be considered as well
    if (leaf(node)) {
        if (test_property(node)) { // if the current is a father, i.e. test the current for the property
            found = true;
            depth = curr_depth;
        } else {
            found = false;
        }
    } else {
        list<std::pair<bool, int>> ll; //here we see that depth when false is a random value, bacause there is no rihgt value
        for (auto &child: node->children) {
            auto ret = depth_of_the_deepest_father_with_at_least_one_child(child, curr_depth);
            ll.push_back(ret);
        }
        list<int> ll2;
        for (auto &el: ll) {
            if (el.first)
                ll2.push_back(el.second);
        }

        if (test_property(node)) {
            ll2.push_back(curr_depth);
        }

        if (!ll2.empty()) {
            found = true;
            depth = *max_element(ll2.begin(), ll2.end());
        } else {
            found = false;
        }
    }
    //here we come out of the branches with valid dept and found, regarless of the branch (undefined when false is a valid condition)

    return {found, depth};
}

// do also by passing depth as parameter, but leave also those here with height so you can see the differences
// father must be treated differently of the children
template<typename T>
std::pair<bool, int> depth_of_the_deepest_father_with_single_child(Node<T> *node, int curr_depth) {
    curr_depth++;

    int depth;
    bool found;

    auto test_property = [](Node<T> *node) -> bool { return node->children.size() == 1; };

    // the only difference between these two branches is that the first considers only the current,
    // while the other considers the children plus the current
    // the else will never be taken, yet we write it here for completeness
    // it comes easier to do the else branch before, because you are helped by the children
    // in the if branch, test the current and provide the results may be done at the same time, in the else branch usually no,
    // children are to be considered as well
    if (node->is_leaf()) {
        if (test_property(node)) { // if the current is a father, i.e. test the current for the property
            found = true;
            depth = curr_depth;
        } else {
            found = false;
        }
    } else {
        list<std::pair<bool, int>> ll; //here we see that depth when false is a random value, bacause there is no rihgt value
        for (auto &child: node->children) {
            auto ret = depth_of_the_deepest_father_with_single_child(child, curr_depth);
            ll.push_back(ret);
        }
        list<int> ll2;
        for (auto &el: ll) {
            if (el.first)
                ll2.push_back(el.second);
        }

        if (test_property(node)) {
            ll2.push_back(curr_depth);
        }

        if (!ll2.empty()) {
            found = true;
            depth = *max_element(ll2.begin(), ll2.end());
        } else {
            found = false;
        }
    }
    //here we come out of the branches with valid dept and found, regarless of the branch (undefined when false is a valid condition)

    return {found, depth};
}

template<typename T>
std::pair<bool, int>
depth_of_the_deepest_father_with_specified_number_of_children(Node<T> *node, int current_depth, int children) {
    current_depth++;

    std::list<int> ll;
    for (auto &child: node->children) {
        auto ret = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(child,
                                                                                                      current_depth,
                                                                                                      children);
        if (ret.first)
            ll.push_back(ret.second);
    }

    if (node->children.size() == children)
        ll.push_back(current_depth);

    bool found;
    int depth;

    if (!ll.empty()) {
        found = true;
        depth = *max_element(ll.begin(), ll.end());
    } else
        found = false;

    return {found, depth};
}

template<typename T>
std::tuple<bool, int, int> //do the same also with min, so that you test all properties (i.e. testproperty on children branch)
number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(Node<T> *node, int current_depth,
                                                                                   int children) {
    current_depth++;

    std::list<std::tuple<bool, int, int>> ll;
    for (auto &child: node->children) {
        auto ret = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(child,
                                                                                                      current_depth,
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
