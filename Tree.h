#ifndef RECURSION_TREE_H
#define RECURSION_TREE_H

#define COUNT 10

#include <algorithm>
#include <chrono>
#include <list>
#include <numeric>
#include <optional>
#include "Node.h"

//an empty tree is a tree?
// In my opinion no! a tree can be a leaf, and on a leaf computation is easier but not totally empty!
// an empty nothing doesn't exists!

template<typename T>
void add_children(Node<T> *tree, int curr, int big) {
    //higher the number to the right, the bigger the tree
    while (std::rand() % (2 * curr) <= big) {
        tree->children.push_back(new Node<int>(std::rand() % 1000));
        curr++;
    }

    for (auto &child: tree->children)
        add_children(child, curr + 1, big);
}

template<typename T>
Node<T> *create_tree(int big) {
    auto tree = new Node<int>(std::rand());
    add_children(tree, 1, big);
    return tree;
}

template<typename T>
T max_utils(std::list<T> &ll) {
    T max = ll.front();
    for (auto el: ll) {
        if (max < el)
            max = el;
    }
    return max;
}

template<typename T>
int min_utils(std::list<T> ll) {
    T &min = ll.front();
    for (auto &el: ll) {
        if (min > el)
            min = el;
    }
    return min;
}

template<typename T>
int sum_utils(std::list<T> ll) {
    return std::accumulate(ll.begin(), ll.end(), 0);
}

/**
* ----------------------------------------
* --BEGIN FUNCTIONS-----------------------
* ----------------------------------------
*/

// since a tree with one element is a tree, you can apply all the reasoning to just the leaf, by pretending to move big things.
// Then you just change the words to the general case, because the big things (that you say assume that we have the list of nodes,
// instead of just ine element of node or an empty list for the children, if a leaf ---> an empty list is a list as well,
// be it empty or in the middle of the tree)
// Otherwise just throw yourself in the middle and apply the question direclty with the the n input (from children), 1 output (to root)
// diagram and apply children gives me how many, then think when no children at all
// A directed tree, differs from a DAG, since each child in the tree have only one father, i.e. during a scan, each node will be visited exactly once.




//define the specified_height of a node as the maximum of the heights of its children +1
template<typename T>
std::pair<int, int> number_of_nodes_at_specific_height(Node<T> *tree, int specified_height) {
    //define all that will be needed later
    std::list<int> nodes_at_specified_height;
    std::list<int> heights;
    int num_of_nodes_at_specified_height; //left unspecified for now because we have to assign to it a value
    int curr_height; //left unspecified for now

    //we want to know the parameters here for the successive computation
    if (tree->children.empty()) {
        // compute with data from father, because he has no children
        // here you must define all the variables left unspecified above
        // do not worry if the follwoing valies do not seems rght,
        // computation for the father will be dealt later with the data of the children
        curr_height = 0;
        num_of_nodes_at_specified_height = 0;
    } else {
        for (auto &child: tree->children) {
            auto ret = number_of_nodes_at_specific_height(child, specified_height);
            heights.push_back(ret.first);
            nodes_at_specified_height.push_back(ret.second);
        }
        curr_height = max_utils(heights);
        num_of_nodes_at_specified_height = sum_utils(nodes_at_specified_height);
    }

    // compute with data from father and children
    // here starts computation of what we want to put on the top arrow of the famous diagram
    if (curr_height == specified_height)
        num_of_nodes_at_specified_height++;
    curr_height++;

    return {curr_height, num_of_nodes_at_specified_height};
}

template<typename T>
int number_of_fathers_with_single_child(Node<T> *tree) {
    std::list<int> fathers_with_single_child;
    int number_of_fathers_with_single_child;

    if (tree->children.empty()) {
        number_of_fathers_with_single_child = 0;
    } else {
        for (auto &child: tree->children) {
            auto ret = number_of_fathers_with_single_child(child);
            fathers_with_single_child.push_back(ret);
        }
        number_of_fathers_with_single_child = sum_utils(fathers_with_single_child);
    }

    if (tree->children.size() == 1)
        number_of_fathers_with_single_child++;

    return number_of_fathers_with_single_child;
}

template<typename T>
int number_of_father_with_specified_number_of_children(Node<T> *tree, int num_of_children) {
    std::list<int> fathers_with_single_child;
    int number_of_fathers_with_single_child;

    if (tree->children.empty()) {
        number_of_fathers_with_single_child = 0;
    } else {
        for (auto &child: tree->children) {
            auto ret = number_of_father_with_specified_number_of_children(child, num_of_children);
            fathers_with_single_child.push_back(ret);
        }
        number_of_fathers_with_single_child = sum_utils(fathers_with_single_child);
    }

    if (tree->children.size() == num_of_children)
        number_of_fathers_with_single_child++;

    return number_of_fathers_with_single_child;
}

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

#endif //RECURSION_TREE_H
