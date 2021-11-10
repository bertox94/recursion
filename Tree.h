#ifndef RECURSION_TREE_H
#define RECURSION_TREE_H

#define COUNT 10

#include <algorithm>
#include <chrono>
#include <list>
#include <numeric>
#include "Node.h"

//an empty tree is a tree?
// In my opinion no! a tree can be a leaf, and on a leaf computation is easier but not totally empty!

template<typename T>
bool has_left_child(Node<T>* tree) {
    return tree->left != nullptr;
}

template<typename T>
bool has_right_child(Node<T>* tree) {
    return tree->right != nullptr;
}

template<typename T>
void add_children(Node<T>* tree, int curr, int big) {
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
Node<T>* create_tree(int big) {
    auto tree = new Node<int>(std::rand() % 1000);
    add_children(tree, 1, big);
    return tree;
}

template<typename T>
void print2DUtil(Node<T>* tree, int space) {
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
void print2D(Node<T>* tree) {
    // Pass initial space count as 0
    print2DUtil(tree, 0);
}

//accepts only non-empty lists
template<typename T>
T max_utils(std::list<T>& ll) {
    return *std::max_element(ll.begin(), ll.end());
}

//accepts only non-empty lists
template<typename T>
T min_utils(std::list<T>& ll) {
    return *std::min_element(ll.begin(), ll.end());
}

//accepts only non-empty lists
template<typename T>
T sum(std::list<T>& ll) {
    return std::accumulate(ll.begin(), ll.end(), 0);
}

template<typename T>
void scan(Node<T>* tree) {
    if (has_left_child(tree))
        scan(tree->left);

    if (has_right_child(tree))
        scan(tree->right);

    return;
}

/**
* ----------------------------------------
* --BEGIN FUNCTIONS-----------------------
* ----------------------------------------
*/

template<typename T>
int max_depth(Node<T>* tree) {
    std::list<T> ll{0};

    if (has_left_child(tree))
        ll.push_back(max_depth(tree->left));

    if (has_right_child(tree))
        ll.push_back(max_depth(tree->right));

    int res = 1 + max_utils(ll);

    return res;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 1
template<typename T>
int min_depth(Node<T>* tree) {
    std::list<T> ll{0};

    if (has_left_child(tree))
        ll.push_back(min_depth(tree->left));
    else
        ll.push_back(0);

    if (has_right_child(tree))
        ll.push_back(min_depth(tree->right));
    else
        ll.push_back(0);

    int res = 1 + min_utils(ll);

    return res;
}

template<typename T>
int how_many(Node<T>* tree) {
    std::list<T> ll{ 1 };

    if (has_left_child(tree))
        ll.push_back(how_many(tree->left));

    if (has_right_child(tree))
        ll.push_back(how_many(tree->right));

    int res = sum(ll);
    return res;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
template<typename T>
T max(Node<T>* tree) {
    std::list<T> ll{ *tree->item };

    if (has_left_child(tree))
        ll.push_back(max(tree->left));

    if (has_right_child(tree))
        ll.push_back(max(tree->right));

    int res = max_utils(ll);
    return res;
}

template<typename T>
T min(Node<T>* tree) {
    std::list<T> ll{ *tree->item };

    if (has_left_child(tree))
        ll.push_back(min(tree->left));

    if (has_right_child(tree))
        ll.push_back(min(tree->right));

    int res = min_utils(ll);
    return res;
}

#endif //RECURSION_TREE_H
