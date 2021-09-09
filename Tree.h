//
// Created by Halib on 9/9/2021.
//

#ifndef RECURSION_TREE_H
#define RECURSION_TREE_H

#define COUNT 10

#include <algorithm>
#include <chrono>
#include "Node.h"

//an empty tree is a tree?
// In my opinion no! a tree can be a leaf, and on a leaf computation is easier but not totally empty!

template<typename T>
bool is_leaf(Node<T> *root) {
    return root->left == nullptr && root->right == nullptr;
}

template<typename T>
void add_children(Node<T> *root, int curr) {

    //higher the number to the right, the bigger the tree
    if (std::rand() % (2 * curr) <= 2) {
        root->left = new Node(std::rand() % 1000);
        add_children(root->left, curr + 1);
        if (root->right != nullptr)
            add_children(root->right, curr + 1);
    }
    if (root != nullptr && std::rand() % (2 * curr) <= 2) {
        root->right = new Node(std::rand() % 1000);
        if (root->left != nullptr)
            add_children(root->left, curr + 1);
        add_children(root->right, curr + 1);
    }


}

template<typename T>
void print2DUtil(Node<T> *root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << *root->item << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

template<typename T>
void print2D(Node<T> *root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

template<typename T>
int max_depth(Node<T> *root) {

    if (root == nullptr)
        return -1;

    int a = max_depth(root->left);
    int b = max_depth(root->right);

    int res = 1 + std::max({a, b});

    return res;
}

template<typename T>
int min_depth(Node<T> *root) {

    if (root == nullptr)
        return -1;

    int a = min_depth(root->left);
    int b = min_depth(root->right);

    int res = 1 + std::min({a, b});

    return res;
}

template<typename T>
int how_many(Node<T> *root) {

    if (root == nullptr)
        return 0;

    int a = how_many(root->left);
    int b = how_many(root->right);

    int res = 1 + a + b;

    return res;
}

//here in fact max(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max between...
template<typename T>
T max(Node<T> *root) {

    //it is a leaf
    if (is_leaf(root))
        return *root->item;

    T a, b;
    int res;

    if (root->left != nullptr && root->right == nullptr) {
        a = max(root->left);
        res = std::max({a, *root->item});
    } else if (root->left == nullptr && root->right != nullptr) {
        b = max(root->right);
        res = std::max({b, *root->item});
    } else {
        a = max(root->left);
        b = max(root->right);
        res = std::max({a, b, *root->item});
    }
    return res;
}


#endif //RECURSION_TREE_H
