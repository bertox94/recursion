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
bool leaf(Node<T> *tree) {
    return tree->children.empty();
}

template<typename T>
Node<T> *create_tree(int big) {
    auto tree = new Node<int>(std::rand());
    add_children(tree, 1, big);
    return tree;
}

template<typename T>
T max_utils(const std::list<T> &ll) {
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

// since a tree with one element is a tree, you can apply all the reasoning to just the leaf, by pretending to move big things.
// Then you just change the words to the general case, because the big things (that you say assume that we have the list of nodes,
// instead of just ine element of node or an empty list for the children, if a leaf ---> an empty list is a list as well,
// be it empty or in the middle of the tree)
// Otherwise just throw yourself in the middle and apply the question direclty with the the n input (from children), 1 output (to root)
// diagram and apply children gives me how many, then think when no children at all
// A directed tree, differs from a DAG, since each child in the tree have only one father, i.e. during a scan, each node will be visited exactly once.







#endif //RECURSION_TREE_H
