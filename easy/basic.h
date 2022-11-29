//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

#include <iomanip>
#include <numeric>
#include "../Node.h"

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
    * can we update "for the father" only here and remove the if(leaf())?
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

// NB: depth = height at the root of each tree
template<typename T>
unsigned long max_depth(Node<T> *node) {

    unsigned long max_depth_;
    if (node->has_children()) {
        std::list<unsigned long> children_depths;
        for (auto &child: node->children) {
            auto child_depth = max_depth(child);
            children_depths.push_back(child_depth + 1);
        }
        max_depth_ = *max_element(children_depths.begin(), children_depths.end(),
                                  [](auto &left, auto &right) { return left < right; });
    } else {
        max_depth_ = 0;
    }

    return max_depth_;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 0
// all you need to cconsider is:
//if it has children, then we pass upward the minimum value among the children, because for the sub-root, the minimum depth is simply the minimum among its children,
// and for the sub-root of a tree with just the root, (which may very well be the original tree without children) the minimum depth is simply the depth of that node.
// The same applies for the leaf, it doesnt matter the depth relative to its parent, it only matters the depth relative to its children, as if only that existed.
template<typename T>
unsigned long min_depth(Node<T> *node) { //i.e. depth of the less deep leaf

    unsigned long min_depth_;
    if (node->has_children()) {
        std::list<unsigned long> children_depths;
        for (auto &child: node->children) {
            auto child_depth = min_depth(child);
            children_depths.push_back(child_depth + 1);
        }
        min_depth_ = *min_element(children_depths.begin(), children_depths.end(),
                                  [](auto &left, auto &right) { return left < right; });
    } else {
        min_depth_ = 0;
    }

    return min_depth_;
}

template<typename T>
//L1: num of children
unsigned long how_many(Node<T> *node) {

    unsigned long size;
    if (node->has_children()) {
        std::list<int> children_sizes;
        for (auto &child: node->children) {
            auto child_size = how_many(child);
            children_sizes.push_back(child_size);
        }
        size = std::accumulate(children_sizes.begin(), children_sizes.end(), 0) + 1;
    } else {
        size = 1;
    }

    return size;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
//When thinking what to return and stuff, just think that a leaf is just a root without children
//L1: max_value
template<typename T>
T max_value(Node<T> *node) {
    T max_val_;
    if (node->has_children()) {
        std::list<T> children_max_values{node->item};
        for (auto &child: node->children) {
            auto child_max_value = max_value(child);
            children_max_values.push_back(child_max_value);
        }
        max_val_ = *max_element(children_max_values.begin(), children_max_values.end());
    } else {
        max_val_ = node->item;
    }

    return max_val_;
}

//L1: min_value
template<typename T>
T min_value(Node<T> *node) {
    T min_val_;
    if (node->has_children()) {
        std::list<T> children_min_values{node->item};
        for (auto &child: node->children) {
            auto child_min_value = max_value(child);
            children_min_values.push_back(child_min_value);
        }
        min_val_ = *max_element(children_min_values.begin(), children_min_values.end());
    } else {
        min_val_ = node->item;
    }

    return min_val_;
}

//R1: item as reference
//L1: number
//as an execrise you could remove the else branch when not necessary, for example here
template<typename T>
unsigned long how_many_like_this(Node<T> *node, T cmp) {
    unsigned long count;
    if (node->has_children()) {
        std::list<unsigned long> children_counts;
        for (auto &child: node->children) {
            auto child_count = how_many_like_this(child, cmp);
            children_counts.push_back(child_count);
        }
        count = accumulate(
                children_counts.begin(), children_counts.end(), 0,
                [](auto acc, auto item) {
                    return acc + item;
                });
        if (node->item == cmp)
            count++;
    } else {
        if (node->item == cmp) {
            count = 1;
        } else {
            count = 0;
        }
    }

    return count;
}

template<typename T>
void destroy(Node<T> *node) {
    for (auto &child: node->children) {
        destroy(child);
    }
    delete node;
}


#endif //RECURSION_BASIC_H
