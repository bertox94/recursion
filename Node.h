//
// Created by Halib on 9/9/2021.
//

#ifndef RECURSION_NODE_H
#define RECURSION_NODE_H

#define COUNT 10

#include <random>
#include <ctime>
#include <iostream>

template<typename T>
class Node {
public:
    T *item;
    Node *left;
    Node *right;

    Node(T *item) : item(item), left(nullptr), right(nullptr) {}
};

template<typename T>
Node<T> *build_random_tree() {
    //int tree

    int size;

    std::default_random_engine generator(((unsigned) time(new time_t())));
    std::uniform_int_distribution<int> distribution(1, 100);

    size = distribution(generator);

    auto *root = new Node(new int(distribution(generator)));
    root->left = new Node(new int(distribution(generator)));
    root->right = new Node(new int(distribution(generator)));

}

void add_children(Node<int> *node, int curr) {

    //std::random_device rd;  //Will be used to obtain a seed for the random number engine
    //std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    //std::uniform_int_distribution<> distrib(1, curr);

    int rand = std::rand() % curr;

    std::cout << curr << std::endl;
    std::cout << rand << std::endl;
    std::cout << std::endl;

    //higher this number bigger the tree
    if (rand > 1)
        return;

    node->left = new Node(new int(std::rand() % 1000));
    node->right = new Node(new int(std::rand() % 1000));

    add_children(node->left, curr + 1);
    add_children(node->right, curr + 1);


}

// Function to print binary tree in 2D
// It does reverse inorder traversal
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

// Wrapper over print2DUtil()
template<typename T>
void print2D(Node<T> *root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


#endif //RECURSION_NODE_H
