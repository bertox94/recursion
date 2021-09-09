//
// Created by Halib on 9/9/2021.
//

#ifndef RECURSION_TREE_H
#define RECURSION_TREE_H

#define COUNT 10

#include <algorithm>
#include <chrono>
#include <list>
#include "Node.h"

//an empty tree is a tree?
// In my opinion no! a tree can be a leaf, and on a leaf computation is easier but not totally empty!

template<typename T>
bool has_no_child(Node<T> *tree) {
    return tree->left == nullptr && tree->right == nullptr;
}

template<typename T>
bool has_left_child(Node<T> *tree) {
    return tree->left != nullptr;
}

template<typename T>
bool has_right_child(Node<T> *tree) {
    return tree->right != nullptr;
}

template<typename T>
void add_children(Node<T> *tree, int curr) {

    //higher the number to the right, the bigger the tree
    if (std::rand() % (2 * curr) <= 2) {
        tree->left = new Node(std::rand() % 1000);
        add_children(tree->left, curr + 1);
        if (tree->right != nullptr)
            add_children(tree->right, curr + 1);
    }
    if (std::rand() % (2 * curr) <= 2) {
        tree->right = new Node(std::rand() % 1000);
        if (tree->left != nullptr)
            add_children(tree->left, curr + 1);
        add_children(tree->right, curr + 1);
    }


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
int max_depth(Node<T> *tree) {

    if (tree == nullptr)
        return -1;

    int a = max_depth(tree->left);
    int b = max_depth(tree->right);

    int res = 1 + std::max({a, b});

    return res;
}

template<typename T>
int min_depth(Node<T> *tree) {

    if (tree == nullptr)
        return -1;

    int a = min_depth(tree->left);
    int b = min_depth(tree->right);

    int res = 1 + std::min({a, b});

    return res;
}

template<typename T>
int how_many(Node<T> *tree) {

    if (tree == nullptr)
        return 0;

    int a = how_many(tree->left);
    int b = how_many(tree->right);

    int res = 1 + a + b;

    return res;
}

//the base case coincides with the tree being a leaf!
template<typename T>
T max_II(Node<T> *tree) {

    if (tree->left == nullptr && tree->right == nullptr) {
        return *tree->item;
    } else if (tree->left != nullptr && tree->right == nullptr) {
        T a = max_II(tree->left);
        int res = std::max({a, *tree->item});
        return res;
    } else if (tree->left == nullptr && tree->right != nullptr) {
        T b = max_II(tree->right);
        int res = std::max({b, *tree->item});
        return res;
    } else {
        T a = max_II(tree->left);
        T b = max_II(tree->right);
        int res = std::max({a, b, *tree->item});
        return res;
    }
}

//here in fact max(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max between...
template<typename T>
T max(Node<T> *tree) {

    if (has_no_child(tree))
        return *tree->item;

    std::list<T> ll{*tree->item};

    if (has_left_child(tree)) {
        T a = max(tree->left);
        ll.push_back(a);
    }

    if (has_right_child(tree)) {
        T b = max(tree->right);
        ll.push_back(b);
    }

    int res = *std::max_element(ll.begin(), ll.end());
    return res;
}


#endif //RECURSION_TREE_H
