//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

#include "Node.h"
#include "Tree.h"

/**
 * TEMPLATE:
    declare all values to be returned

    if (leaf(tree)) {
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
int max_num_of_direct_children(Node<T> *tree) {
    int max_num_of_children_of_the_children;
    int maximum_num_of_children;

    if (tree->children.empty()) {
        maximum_num_of_children = 0;
    } else {
        std::list<int> children_of_the_children;
        for (auto &child: tree->children)
            children_of_the_children.push_back(max_num_of_direct_children(child));
        max_num_of_children_of_the_children = max_utils(children_of_the_children);
        int n_of_children = tree->children.size();
        maximum_num_of_children = max_utils(std::list<T>{n_of_children, max_num_of_children_of_the_children});
    }

    return maximum_num_of_children;
}

template<typename T>
int number_of_fathers_with_specified_number_of_children(Node<T> *tree, int num_of_children) {
    int num_of_nodes_of_the_children;
    int current_num_of_nodes;

    if (leaf(tree)) {
        num_of_nodes_of_the_children = 0;
    } else {
        std::list<int> nodes_from_the_children;
        for (auto &child: tree->children)
            nodes_from_the_children.push_back(
                    number_of_fathers_with_specified_number_of_children(child, num_of_children));
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
std::pair<bool, int> depth_of_the_deepest_node_with_at_least_one_child(Node<T> *tree) {
    int distance;
    bool found;

    auto has_at_least_one_child = [](Node<T> *tree) -> bool { return !tree->children.empty(); };

    //the only difference between these two branches is that the first considers only the current, while the other considers the children plus the current
    // the else will never be taken, yet we write it here for completeness
    // it comes easier to do the else branch before, because you are helped by the children
    // in the if branch, test the current and provide the results may be done at the same time, in the else branch usually no,
    // children are to be considered as well
    if (leaf(tree)) {
        if (has_at_least_one_child(tree)) { // if the current is a father, i.e. test the current for the property
            found = true;
            distance = 0;
        } else {
            found = false;
        }
    } else {
        list<int> depths_of_the_children; //here we see that distance when false is a random value, bacause there is no rihgt value
        for (auto &child: tree->children) {
            auto ret = depth_of_the_deepest_node_with_at_least_one_child(child);
            if (ret.first)
                depths_of_the_children.push_back(ret.second);
        }

        if (!depths_of_the_children.empty()) {
            found = true;
            int max_distance_among_the_children = max_utils(depths_of_the_children);
            int max_distance_among_the_children_seen_by_curr = max_distance_among_the_children + 1;
            if (has_exactly_one_child(tree)) { // if the current is a father, i.e. test the current for the property
                int distance_of_the_current = 0;
                distance = std::max(0, max_distance_among_the_children_seen_by_curr);
            } else
                distance = max_distance_among_the_children_seen_by_curr;
        } else {
            if (has_at_least_one_child(tree)) { // if the current is a father, i.e. test the current for the property
                found = true;
                distance = 0;
            } else
                found = false;
        }
    }
    //here we come out of the branches with valid dept and found, regarless of the branch (undefined when false is a valid condition)

    return {found, distance};
}

// do also by passing depth as parameter, but leave also those here with height so you can see the differences
// father must be treated differently of the children
template<typename T>
std::pair<bool, int> depth_of_the_deepest_father_with_single_child(Node<T> *tree) {
    int distance;
    bool found;

    auto has_exactly_one_child = [](Node<T> *tree) -> bool { return tree->children.size() == 1; };

    if (leaf(tree)) {
        if (has_exactly_one_child(tree)) {
            found = true;
            distance = 0;
        } else
            found = false;
    } else {
        list<int> depths_of_the_children;
        for (auto &child: tree->children) {
            auto ret = depth_of_the_deepest_father_with_single_child(child);
            if (ret.first)
                depths_of_the_children.push_back(ret.second);
        }

        if (!depths_of_the_children.empty()) {
            found = true;
            int max_distance_among_the_children = max_utils(depths_of_the_children);
            int max_distance_among_the_children_seen_by_curr = max_distance_among_the_children + 1;
            if (has_exactly_one_child(tree)) {
                int distance_of_the_current = 0;
                distance = std::max(0, max_distance_among_the_children_seen_by_curr);
            } else
                distance = max_distance_among_the_children_seen_by_curr;
        } else {
            if (has_exactly_one_child(tree)) {
                found = true;
                distance = 0;
            } else
                found = false;
        }
    }
    return {found, distance};
}

template<typename T>
std::pair<bool, int> depth_of_the_deepest_father_with_specified_number_of_children(Node<T> *tree, int children) {
    int depth;
    bool found;

    auto has_exactly_n_children = [&children](Node<T> *tree) -> bool { return tree->children.size() == children; };

    if (leaf(tree)) {
        if (has_exactly_n_children(tree)) {
            found = true;
            depth = 0;
        } else
            found = false;
    } else {
        list<int> depths;
        for (auto &child: tree->children) {
            auto ret = depth_of_the_deepest_father_with_specified_number_of_children(child);
            if (ret.first)
                depths.push_back(ret.second);
        }

        if (has_exactly_n_children(tree))
            depths.push_back(0);

        if (depths.empty()) {
            found = true;
            depth = max_utils(depths);
        } else
            found = false;
    }
    return {found, depth};
}

template<typename T>
std::tuple<bool, int, int>
number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(Node<T> *tree, int current_depth,
                                                                                   int children) {

    bool found;
    int depth_of_the_target;
    int number;

    auto has_exactly_n_children = [&children](Node<T> *tree) -> bool { return tree->children.size() == children; };

    if (leaf(tree)) {
        if (has_exactly_n_children(tree)) {
            found = true;
            depth_of_the_target = current_depth;
        } else
            found = false;
    } else {
        std::list<int> depths;
        std::list<int> numbers;
        for (auto &child: tree->children) {
            int depth_of_the_children = current_depth + 1;
            auto ret = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(child,
                                                                                                          depth_of_the_children,
                                                                                                          children);
            if (get<0>(ret)) {
                depths.push_back(get<1>(ret));
                numbers.push_back(get<2>(ret));
            }
        }

        //one may think that could be easier/faster to do:
        //-check if depths is empty then add the father, but it's better to go with lead foot and
        // treat the father the same way of the children (i.e. share depths, numbers)

        if (has_exactly_n_children(tree)) {
            depths.push_back(0);
            numbers.push_back(1);
        }

        if (!depths.empty()) {
            found = true;
            depth_of_the_target = max_utils(depths);
            number = sum_utils(numbers);
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
