//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

#include "Node.h"
#include "Tree.h"

template<typename T>
void scan(Node<T> *tree) {
    for (auto &child: tree->children)
        scan(child);
}

template<typename T>
int max_depth(Node<T> *tree) {
    int m_depth_of_the_children;
    int m_depth_of_the_current;
    if (tree->children.empty()) {
        // no statement for the children
        m_depth_of_the_current = 0; // for the father
    } else {
        std::list<int> depths;
        for (auto &child: tree->children) {
            auto ret = max_depth(child);
            depths.push_back(ret);
        }
        m_depth_of_the_children = max_utils(depths);
        m_depth_of_the_current = m_depth_of_the_children + 1;
    }

    return m_depth_of_the_current;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 0
template<typename T>
int min_depth(Node<T> *tree) {
    int m_depth_of_the_children;
    int m_depth_of_the_current;
    if (tree->children.empty()) {
        // no statement for the children
        m_depth_of_the_current = 0; // for the father
    } else {
        std::list<int> depths;
        for (auto &child: tree->children) {
            auto ret = min_depth(child);
            depths.push_back(ret);
        }
        m_depth_of_the_children = min_utils(depths);
        m_depth_of_the_current = m_depth_of_the_children + 1;
    }

    return m_depth_of_the_current;
}

template<typename T>
int how_many(Node<T> *tree) {
    int h_many_children;
    int h_many;
    if (tree->children.empty()) {
        h_many_children = 0;
    } else {
        std::list<int> nodes;
        for (auto &child: tree->children)
            nodes.push_back(how_many(child));
        h_many_children = sum_utils(nodes);
    }

    h_many = h_many_children + 1; //for the father
    return h_many;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
//When thinking what to return and stuff, just think that a leaf is just a root without children
template<typename T>
T max_value(Node<T> *tree) {
    int m_val_among_the_children;
    int m_val;
    if (tree->children.empty()) {
        //empty statement for the children
        m_val = *tree->item; // for the father
    } else {
        std::list<int> maxes;
        for (auto &child: tree->children)
            maxes.push_back(max_value(child));
        m_val_among_the_children = max_utils(maxes); // for the children
        m_val = std::max(m_val_among_the_children, *tree->item); // for the father
    }
    return m_val;
}

template<typename T>
T min_value(Node<T> *tree) {
    int m_val_among_the_children;
    int m_val;
    if (tree->children.empty()) {
        //empty statement for the children
        m_val = *tree->item; // for the father
    } else {
        std::list<int> minima;
        for (auto &child: tree->children)
            minima.push_back(min_value(child));
        m_val_among_the_children = min_utils(minima); // for the children
        m_val = std::min(m_val_among_the_children, *tree->item); // for the father
    }
    return m_val;
}

template<typename T>
T how_many_like_this(Node<T> *tree, T like) {
    int num_of_nodes_of_the_children;
    int num_of_nodes;
    if (tree->children.empty()) {
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes;
        for (auto &child: tree->children)
            nodes.push_back(how_many_like_this(child, like));
        num_of_nodes_of_the_children = sum_utils(nodes);
    }
    num_of_nodes = num_of_nodes_of_the_children;
    if (*tree->item == like)
        num_of_nodes++;
    return num_of_nodes;
}

template<typename T>
list<T> list_nodes(Node<T> *tree) {
    std::list<int> nodes;
    if (tree->children.empty()) {
        // for the children, the list is already empty, no need to do anything
        // for the father will be done later once for this two cases
    } else {
        std::list<int> children_nodes;
        for (auto &child: tree->children)
            children_nodes.splice(children_nodes.end(), list_nodes(child));
        nodes = children_nodes;
    }
    nodes.push_back(*tree->item);
    return nodes;
}

/**
 * Number of fathers with a specified number of children
 */
template<typename T>
int number_of_fathers_with_no_child(Node<T> *tree) {
    // the following are left unspecified for now because we don't know what value is it now
    // the data of the children can and usually must survive outside the if-else blocks, so it's declared here
    int num_of_nodes_of_the_children;
    int current_num_of_nodes;

    //in this if-else we deal only with children!!!
    if (tree->children.empty()) {
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes_from_the_children;
        for (auto &child: tree->children)
            nodes_from_the_children.push_back(number_of_fathers_with_no_child(child));
        num_of_nodes_of_the_children = sum_utils(nodes_from_the_children);
    }
    // fair enpugh that we come out of this with data on the children,
    // we don't care about current until now

    current_num_of_nodes = num_of_nodes_of_the_children;
    if (tree->children.empty())
        current_num_of_nodes++;

    return current_num_of_nodes;
}

template<typename T>
int number_of_fathers_with_single_child(Node<T> *tree) {
    int num_of_nodes_of_the_children;
    int current_num_of_nodes;

    if (tree->children.empty()) {
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes_from_the_children;
        for (auto &child: tree->children)
            nodes_from_the_children.push_back(number_of_fathers_with_single_child(child));
        num_of_nodes_of_the_children = sum_utils(nodes_from_the_children);
    }

    current_num_of_nodes = num_of_nodes_of_the_children;
    if (tree->children.size() == 1)
        current_num_of_nodes++;

    return current_num_of_nodes;
}

template<typename T>
int number_of_fathers_with_specified_number_of_children(Node<T> *tree, int num_of_children) {
    int num_of_nodes_of_the_children;
    int current_num_of_nodes;

    if (tree->children.empty()) {
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes_from_the_children;
        for (auto &child: tree->children)
            nodes_from_the_children.push_back(number_of_fathers_with_specified_number_of_children(child));
        num_of_nodes_of_the_children = sum_utils(nodes_from_the_children);
    }

    current_num_of_nodes = num_of_nodes_of_the_children;
    if (tree->children.size() == num_of_children)
        current_num_of_nodes++;

    return current_num_of_nodes;
}

/**
 * Number of fathers with a specified number of children
 */
template<typename T>
int depth_of_the_deepest_father_with_single_child(Node<T> *tree) {
    //First, handle what comes up from children
    std::list<int> ll;
    for (auto &child: tree->children) {
        auto ret = depth_of_the_deepest_father_with_single_child(child);
        ll.push_back(ret);
    }

    //Then, handle the father/consider it a leaf (i.e. once you took care of children in the steps above,
    // the father is just a leaf (what you call the base case))
    if (tree->children.size() == 1)
        ll.emplace_back(0);

    //Compute what to return
    int max_depth = max_utils(ll);

    return max_depth + 1;
}

template<typename T>
std::pair<int, int> number_of_fathers_with_single_child_at_same_and_maximal_depth(Node<T> *tree) {
    //First, handle what comes up from children
    std::list<std::pair<int, int>> ll;
    for (auto &child: tree->children) {
        auto ret = number_of_fathers_with_single_child_at_same_and_maximal_depth(child);
        ll.push_back(ret);
    }

    //Then, handle the father, usually you can handle it the same way you deal with children, so just add it to the same list
    if (tree->children.size() == 1)
        ll.emplace_back(1, 0);

    //Compute what to return
    int num = 0, depth = 0;
    for (auto &el: ll) {
        if (el.second > depth) {
            num = 1;
            depth = el.second;
        } else if (el.second == depth) {
            num++;
        }
    }

    return {num, depth + 1};
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
template<typename T>
std::pair<int, int> number_of_nodes_at_height_zero(Node<T> *tree) {
    int num_of_nodes_of_the_children;
    int current_num_of_nodes;
    int height_of_the_children;
    int max_height_among_the_children;
    int current_height;

    if (tree->children.empty()) {
        current_height = 0;
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes_from_the_children;
        std::list<int> heights_of_the_children;
        for (auto &child: tree->children) {
            auto ret = number_of_nodes_at_height_zero(child);
            heights_of_the_children.push_back(ret.first);
            nodes_from_the_children.push_back(ret.second);
        }
        max_height_among_the_children = max_utils(heights_of_the_children);
        current_height = max_height_among_the_children + 1;
        num_of_nodes_of_the_children = sum_utils(nodes_from_the_children);
    }

    current_num_of_nodes = num_of_nodes_of_the_children;
    if (current_height == 0)
        current_num_of_nodes = num_of_nodes_of_the_children + 1;

    return {current_height, current_num_of_nodes};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_height_one(Node<T> *tree) {
    int num_of_nodes_of_the_children;
    int current_num_of_nodes;
    int height_of_the_children;
    int max_height_among_the_children;
    int current_height;

    if (tree->children.empty()) {
        current_height = 0;
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes_from_the_children;
        std::list<int> heights_of_the_children;
        for (auto &child: tree->children) {
            auto ret = number_of_nodes_at_height_one(child);
            heights_of_the_children.push_back(ret.first);
            nodes_from_the_children.push_back(ret.second);
        }
        max_height_among_the_children = max_utils(heights_of_the_children);
        current_height = max_height_among_the_children + 1;
        num_of_nodes_of_the_children = sum_utils(nodes_from_the_children);
    }

    current_num_of_nodes = num_of_nodes_of_the_children;
    if (current_height == 1)
        current_num_of_nodes = num_of_nodes_of_the_children + 1;

    return {current_height, current_num_of_nodes};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_specific_height(Node<T> *tree, int specified_height) {
    //the following are left unspecified for now because we don't know what value is it now
    int num_of_nodes_of_the_children;
    int current_num_of_nodes;
    int height_of_the_children;
    int max_height_among_the_children;
    int current_height;

    if (tree->children.empty()) {
        current_height = 0;
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes_from_the_children;
        std::list<int> heights_of_the_children;
        for (auto &child: tree->children) {
            auto ret = number_of_nodes_at_specific_height(child, specified_height);
            heights_of_the_children.push_back(ret.first);
            nodes_from_the_children.push_back(ret.second);
        }
        max_height_among_the_children = max_utils(heights_of_the_children);
        current_height = max_height_among_the_children + 1;
        num_of_nodes_of_the_children = sum_utils(nodes_from_the_children);
    }

    current_num_of_nodes = num_of_nodes_of_the_children;
    if (current_height == specified_height)
        current_num_of_nodes = num_of_nodes_of_the_children + 1;

    return {current_height, current_num_of_nodes};
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
std::pair<int, int> number_of_nodes_at_depth_zero(Node<T> *tree, int current_depth) {
    return {};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_depth_one(Node<T> *tree, int current_depth) {
    return {};
}

template<typename T>
std::pair<int, int> number_of_nodes_at_specific_depth(Node<T> *tree, int current_depth, int target_depth) {
    return {};
}

#endif //RECURSION_BASIC_H
