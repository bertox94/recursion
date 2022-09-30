//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

#include "Node.h"
#include "Tree.h"

/**
 * TEMPLATE:
    * update descending values
    * declare all values to be returned
    if (leaf(node)) {
        * test the property on current only
        * provide the values to be returned out of current only
    } else {
        * get all the values to be returned from the children, as if existed only them
        * test the property on current only
        * get all the values to be returned from current only, as if existed only him
        * provide the values to be returned out of children + current
    }

    return values;
 */

// The trick of recursion is: the question is: bla bla complex. You draw the diagram and say,
// assume I have the solution of exactly bla bla complex of this branch coming up from this branch,
// and the same for the other branch, let's build the solution of bla bla complex to return to the branch upward.
// So basically you pretend to know the answer of the exactly same big question for the entire tree coming up from the branches

//divide functions based on the behavior on the base case (there you should see max, count)
//or counting, max/min

template<typename T>
void scan(Node<T> *node) {
    for (auto &child: node->children)
        scan(child);
}

template<typename T>
int max_depth(Node<T> *node, int depth) {
    depth++;
    int m_depth;
    if (node->is_leaf()) {
        // no statement for the children
        m_depth = depth; // for the father
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = max_depth(child, depth);
            ll.push_back(ret);
        }
        m_depth = max_utils(ll);
    }

    return m_depth;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 0
template<typename T>
int min_depth(Node<T> *node, int depth) { //i.e. depth of the less deep leaf
    depth++;
    int m_depth;
    if (node->is_leaf()) {
        // no statement for the children
        m_depth = depth; // for the father
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = min_depth(child, depth);
            ll.push_back(ret);
        }
        m_depth = min_utils(ll);
    }

    return m_depth;
}


template<typename T>
int how_many(Node<T> *node) {
    int h_many;
    if (node->is_leaf()) {
        h_many = 1;
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = how_many(child);
            ll.push_back(ret);
        }
        h_many = sum_utils(ll) + 1;
    }

    return h_many;
}

template<typename T>
int how_many_variant(Node<T> *node, int count) {
    count++;

    int h_many;
    if (node->is_leaf()) {
        h_many = count;
    } else {
        int ret;
        for (auto &child: node->children) {
            ret = how_many_variant(child, count);
            count = ret;
        }
        h_many = count;
    }

    return h_many;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
//When thinking what to return and stuff, just think that a leaf is just a root without children
template<typename T>
T max_value(Node<T> *node) {
    int m_val;
    if (node->is_leaf()) {
        //empty statement for the children
        m_val = *node->item; // for the father
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = max_value(child);
            ll.push_back(ret);
        }
        ll.push_back(*node->item);
        m_val = max_utils(ll);
    }
    return m_val;
}

template<typename T>
T min_value(Node<T> *node) {
    int m_val;
    if (node->is_leaf()) {
        m_val = *node->item;
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = min_value(child);
            ll.push_back(ret);
        }
        ll.push_back(*node->item);
        m_val = min_utils(ll);
    }
    return m_val;
}

template<typename T>
int how_many_like_this(Node<T> *node, T like) {
    int h_many;
    auto test_property = [](Node<T> *node, T like) -> bool { return *node->item == like; };

    if (node->is_leaf()) {
        if (test_property(node, like))
            h_many = 1;
        else
            h_many = 0;
    } else {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto ret = how_many_like_this(child, like);
            ll.push_back(ret);
        }
        h_many = sum_utils(ll);
        if (test_property(node, like))
            h_many++;
    }

    return h_many;
}

template<typename T>
//contrived example, to avoid, but interesting for how it is the normal dealing of right and left attributes
//nb the loop in the else branch changes, it is an indicator of a bad choice of attributes
int how_many_like_this_variant(Node<T> *node, T like, int count) {
    auto test_property = [](Node<T> *node, T like) -> bool { return *node->item == like; };

    if (test_property(node, like)) //since it is a right attribute we update it right now
        count++;
    int h_many;

    if (node->is_leaf()) {
        h_many = count;
    } else {
        int ret;
        for (auto &child: node->children) {
            ret = how_many_like_this_variant(child, like, count);
            count = ret;
        }
        h_many = ret;
    }

    return h_many;
}

template<typename T>
//little bit more confusing
int how_many_like_this_variant_II(Node<T> *node, T like, int count) {
    auto test_property = [](Node<T> *node, T like) -> bool { return *node->item == like; };

    if (test_property(node, like)) //since it is a right attribute we update it as first thing
        count++;

    if (node->is_leaf()) {
        // nothing
    } else {
        for (auto &child: node->children) {
            count = how_many_like_this_variant(child, like, count);
        }
    }

    return count;
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
        num = sum_utils(ll);
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
        num = sum_utils(ll);
        if (test_property(node))
            num++;
    }

    return num;
}

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
template<typename T>
std::tuple<bool, int> max_num_of_direct_children_at_depth(Node<T> *node, int curr_depth, int target_depth) {
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
            auto ret = max_num_of_direct_children_at_depth(child, curr_depth, target_depth);
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
        num = sum_utils(ll);
        if (test_property(node, num_of_children))
            num++;
    }

    return num;
}

/**
 * Number of fathers with a specified number of children
 */

template<typename T>
std::pair<bool, int> depth_of_the_deepest_node_with_at_least_one_child(Node<T> *node, int curr_depth) {
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
            auto ret = depth_of_the_deepest_node_with_at_least_one_child(child, curr_depth);
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
            depth = max_utils(ll2);
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
            depth = max_utils(ll2);
        } else {
            found = false;
        }
    }
    //here we come out of the branches with valid dept and found, regarless of the branch (undefined when false is a valid condition)

    return {found, depth};
}

template<typename T>
std::pair<bool, int>
depth_of_the_deepest_father_with_specified_number_of_children(Node<T> *node, int curr_depth, int children) {
    curr_depth++;
    int depth;
    bool found;

    auto test_property = [](Node<T> *node, int children) -> bool { return node->children.size() == children; };

    // the only difference between these two branches is that the first considers only the current,
    // while the other considers the children plus the current
    // the else will never be taken, yet we write it here for completeness
    // it comes easier to do the else branch before, because you are helped by the children
    // in the if branch, test the current and provide the results may be done at the same time, in the else branch usually no,
    // children are to be considered as well
    if (leaf(node)) {
        if (test_property(node, children)) { // if the current is a father, i.e. test the current for the property
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

        if (test_property(node, children)) {
            ll2.push_back(curr_depth);
        }

        if (!ll2.empty()) {
            found = true;
            depth = max_utils(ll2);
        } else {
            found = false;
        }
    }
    //here we come out of the branches with valid dept and found, regarless of the branch (undefined when false is a valid condition)

    return {found, depth};
}

template<typename T>
std::tuple<bool, int, int> //do the same also with min, so that you test all properties (i.e. testproperty on children branch)
number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(Node<T> *node, int current_depth,
                                                                                   int children) {
    current_depth++;
    bool found;
    int depth_of_the_target;
    int number;

    auto test_property = [](Node<T> *node, int children) -> bool { return node->children.size() == children; };

    if (leaf(node)) {
        if (test_property(node, children)) {
            found = true;
            depth_of_the_target = current_depth;
            number = 1;
        } else
            found = false;
    } else {
        std::list<std::tuple<bool, int, int>> ll;
        for (auto &child: node->children) {
            auto ret = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(child,
                                                                                                          current_depth,
                                                                                                          children);
            ll.push_back(ret);
        }

        //one may think that could be easier/faster to do:
        //-check if ll is empty then add the father, but it's better to go with lead foot and
        // treat the father the same way of the children (i.e. share ll, ll2)

        list<pair<int, int>> ll2;

        for (auto &el: ll) {
            if (std::get<0>(el)) {
                ll2.emplace_back(std::get<1>(el), std::get<2>(el));
            }
        }

        if (test_property(node, children)) {
            ll2.emplace_back(current_depth, 1);
        }

        if (!ll2.empty()) {
            found = true;

            depth_of_the_target = ll2.front().first;
            for (auto el: ll2) {
                if (el.first > depth_of_the_target)
                    depth_of_the_target = el.first;
            }

            number = 0;
            for (auto el: ll2)
                if (el.first == depth_of_the_target)
                    number += el.second;
        } else
            found = false;
    }
    return {found, depth_of_the_target, number};
}

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
    int num;
    int height;

    auto test_property = [](int height) -> bool { return height == 0; };

    if (node->is_leaf()) {
        height = 0;
        if (test_property(height))
            num = 1;
        else
            num = 0;
    } else {
        std::list<pair<int, int>> ll;
        for (auto &child: node->children) {
            auto ret = number_of_nodes_at_height_zero(child);
            ll.push_back(ret);
        } // you can always assume that ll is not empty

        height = ll.front().first;
        for (auto &el: ll) {
            if (height < el.first)
                height = el.first;
        }
        height++; //this is the height of the current node

        if (test_property(height))
            ll.emplace_back(height, 1);

        num = 0;
        for (auto el: ll) {
            num += el.second;
        }
    }

    return {height, num};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_height_one(Node<T> *node) {
    int num;
    int height;

    auto test_property = [](int height) -> bool { return height == 1; };

    if (node->is_leaf()) {
        height = 0;
        if (test_property(height))
            num = 1;
        else
            num = 0;
    } else {
        std::list<pair<int, int>> ll;
        for (auto &child: node->children) {
            auto ret = number_of_nodes_at_height_one(child);
            ll.push_back(ret);
        } // you can always assume that ll is not empty

        height = ll.front().first;
        for (auto &el: ll) {
            if (height < el.first)
                height = el.first;
        }
        height++; //this is the height of the current node

        if (test_property(height))
            ll.emplace_back(height, 1);

        num = 0;
        for (auto el: ll) {
            num += el.second;
        }
    }

    return {height, num};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_specific_height(Node<T> *node, int specified_height) {
    //the following are left unspecified for now because we don't know what value is it now
    int num;
    int height;

    auto test_property = [](int curr_height, int specified_height) -> bool { return curr_height == specified_height; };

    if (node->is_leaf()) {
        height = 0;
        if (test_property(height, specified_height))
            num = 1;
        else
            num = 0;
    } else {
        std::list<pair<int, int>> ll;
        for (auto &child: node->children) {
            auto ret = number_of_nodes_at_specific_height(child, specified_height);
            ll.push_back(ret);
        }

        height = ll.front().first;
        for (auto &el: ll) {
            if (height < el.first)
                height = el.first;
        }
        height++;

        if (test_property(height, specified_height))
            ll.emplace_back(height, 1);

        num = 0;
        for (auto el: ll) {
            num += el.second;
        }
    }

    return {height, num};
}

/**
 * DEPTH
 * The depth of a node is the depth of the father +1. The father has depth 0.
 */
// here you can see that the dealing with the father variable and the computation of the returned variable are split
// probably because we return a pair of two values
// height is computed in each branch, nodes once outside the branches
// note that it is superfluous to return the height, yet in this case we need to return it anyway
template<typename T>
std::pair<int, int> number_of_nodes_at_depth_zero(Node<T> *node, int current_depth) {
    return {};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_depth_one(Node<T> *node, int current_depth) {
    return {};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_specific_depth(Node<T> *node, int current_depth, int target_depth) {
    return {};
}

#endif //RECURSION_BASIC_H
