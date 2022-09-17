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
    auto tree = new Node<int>(std::rand() % 1000);
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
void scan(Node<T> *tree) {
    for (auto &child: tree->children)
        scan(child);
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

template<typename T>
int max_depth(Node<T> *tree) {
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = max_depth(child);
        ll.push_back(ret);
    }

    int max_depth_as_children_were_root;
    if (tree->children.empty())
        max_depth_as_children_were_root = 0;
    else
        max_depth_as_children_were_root = max_utils(ll);
    return 1 + max_depth_as_children_were_root;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 1
template<typename T>
int min_depth(Node<T> *tree) {
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = min_depth(child);
        ll.push_back(ret);
    }

    int min_depth_as_children_were_root;
    if (tree->children.empty())
        min_depth_as_children_were_root = 0;
    else
        min_depth_as_children_were_root = min_utils(ll);
    return 1 + min_depth_as_children_were_root;
}

template<typename T>
int how_many(Node<T> *tree) {
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = how_many(child);
        ll.push_back(ret);
    }

    int how_many_below_curr;
    if (tree->children.empty())
        how_many_below_curr = 0;
    else
        how_many_below_curr = std::accumulate(ll.begin(), ll.end(), 0);
    return 1 + how_many_below_curr;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
template<typename T>
T max_value(Node<T> *tree) {
    std::list<T> ll{*tree->item};
    for (auto &child: tree->children) {
        auto ret = max_value(child);
        ll.push_back(ret);
    }
    return max_utils(ll);
}

template<typename T>
T min_value(Node<T> *tree) {
    std::list<T> ll{*tree->item};
    for (auto &child: tree->children) {
        auto ret = min_value(child);
        ll.push_back(ret);
    }
    return min_utils(ll);
}

template<typename T>
list<T> list_nodes(Node<T> *tree) {
    std::list<T> ll{*tree->item};
    for (auto &child: tree->children) {
        auto ret = list_nodes(child);
        ll.splice(ll.end(), ret);
    }
    return ll;
}

#endif //RECURSION_TREE_H
