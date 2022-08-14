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

template<typename T>
bool has_left_child(Node<T> *tree) {
    return tree->left != nullptr;
}

template<typename T>
bool has_right_child(Node<T> *tree) {
    return tree->right != nullptr;
}

template<typename T>
void add_children(Node<T> *tree, int curr, int big) {
    //higher the number to the right, the bigger the tree
    if (std::rand() % (2 * curr) <= big)
        tree->left = new Node<int>(std::rand() % 1000);

    if (std::rand() % (2 * curr) <= big)
        tree->right = new Node<int>(std::rand() % 1000);

    if (has_left_child(tree))
        add_children(tree->left, curr + 1, big);
    if (has_right_child(tree))
        add_children(tree->right, curr + 1, big);
}

template<typename T>
Node<T> *create_tree(int big) {
    auto tree = new Node<int>(std::rand() % 1000);
    add_children(tree, 1, big);
    return tree;
}

template<typename T>
void print2DUtil(Node<T> *tree, int space) {
    // Base case
    if (tree == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(tree->right, space);

    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << *tree->item << "\n";

    // Process left child
    print2DUtil(tree->left, space);
}

template<typename T>
void print2D(Node<T> *tree) {
    // Pass initial space count as 0
    print2DUtil(tree, 0);
}

template<typename T>
T max_utils(T lvalue, T rvalue) {
    if (rvalue > lvalue)
        return rvalue;
    else
        return lvalue;
}

template<typename T>
T min_utils(T lvalue, T rvalue) {
    if (rvalue < lvalue)
        return rvalue;
    else
        return lvalue;
}

template<typename T>
std::optional<T> min_utils(std::optional<T> lvalue, std::optional<T> rvalue) {
    if (lvalue.has_value()) {
        if (rvalue.has_value()) {
            return min_utils(lvalue.value(), rvalue.value());
        } else
            return lvalue;
    } else return rvalue;
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

int min_utils(std::list<int> ll) {
    int min = ll.front();
    for (auto &el: ll) {
        if (min > el)
            min = el;
    }
    return min;
}

template<typename T>
void scan(Node<T> *tree) {
    if (has_left_child(tree))
        scan(tree->left);

    if (has_right_child(tree))
        scan(tree->right);
}

/**
* ----------------------------------------
* --BEGIN FUNCTIONS-----------------------
* ----------------------------------------
*/

template<typename T>
int max_depth(Node<T> *tree) {
    int lvalue = 0;
    int rvalue = 0;

    if (has_left_child(tree))
        lvalue = max_depth(tree->left);

    if (has_right_child(tree))
        rvalue = max_depth(tree->right);

    return 1 + max_utils(lvalue, rvalue);
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 1
template<typename T>
int min_depth(Node<T> *tree) {
    int lvalue = 0;
    int rvalue = 0;

    if (has_left_child(tree))
        lvalue = min_depth(tree->left);

    if (has_right_child(tree))
        rvalue = min_depth(tree->right);

    return 1 + min_utils(lvalue, rvalue);
}

template<typename T>
int how_many(Node<T> *tree) {
    int sum = 0;
    if (has_left_child(tree))
        sum += how_many(tree->left);

    if (has_right_child(tree))
        sum += how_many(tree->right);

    return 1 + sum;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
template<typename T>
T max(Node<T> *tree) {
    std::list<T> ll;

    if (has_left_child(tree))
        ll.push_back(max(tree->left));

    if (has_right_child(tree))
        ll.push_back(max(tree->right));

    ll.push_back(*tree->item);
    return max_utils(ll);
}

template<typename T>
T min(Node<T> *tree) {
    std::list<T> ll;

    if (has_left_child(tree))
        ll.push_back(min(tree->left));

    if (has_right_child(tree))
        ll.push_back(min(tree->right));

    ll.push_back(*tree->item);
    return min_utils(ll);
}

#endif //RECURSION_TREE_H
