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
int sum_utils(std::list<T> ll) {
    return std::accumulate(ll.begin(), ll.end(), 0);
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
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = max_value(child);
        ll.push_back(ret);
    }
    ll.push_back(*tree->item);
    return max_utils(ll);
}

template<typename T>
T min_value(Node<T> *tree) {
    std::list<T> ll;
    for (auto &child: tree->children) {
        auto ret = min_value(child);
        ll.push_back(ret);
    }
    ll.push_back(*tree->item);
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

//define the height of a node as the maximum of the heights of its children +1
template<typename T>
std::pair<int, int> number_of_nodes_at_depth_one(Node<T> *tree) {
    //First, handle what comes up from children
    std::list<int> ll;
    for (auto &child: tree->children) {
        auto ret = number_of_father_with_single_child(child);
        ll.push_back(ret);
    }

    //Then, find a way to treat the father as the children
    if (tree->children.size() == 0) { // leaf (usually always present)
        ll.emplace_back(0);
    } else if (tree->children.size() == 1) //specific case that need attention
        ll.emplace_back(1);
    else {
        // nothing relevant here
    }

    //Compute what to return
    int num = sum_utils(ll);

    return {};
}


//define the specified_height of a node as the maximum of the heights of its children +1
template<typename T>
std::pair<int, int> number_of_nodes_at_specific_height(Node<T> *tree, int specified_height) {
    //define all that will be needed later
    std::list<int> nodes_at_specified_height;
    std::list<int> heights;
    int curr_height; //left unspecified for now
    int num_of_nodes_at_specified_height; //left unspecified for now because we have to assign to it a value

    //we want to know the parameters here for the successive computation
    if (tree->children.empty()) {
        // compute with data from father, because he has no children
        // here you must define all the variables left unspecified above
        curr_height = 0;
        if (curr_height == specified_height)
            num_of_nodes_at_specified_height = 1;
        else
            num_of_nodes_at_specified_height = 0;
    } else {
        for (auto &child: tree->children) {
            auto ret = number_of_nodes_at_specific_height(child, specified_height);
            heights.push_back(ret.first);
            nodes_at_specified_height.push_back(ret.second);
        }
        //compute with data from father and children
        curr_height = max_utils(heights) + 1;
        num_of_nodes_at_specified_height = sum_utils(nodes_at_specified_height);
        if (curr_height == specified_height)
            num_of_nodes_at_specified_height++;
    }

    return {curr_height, num_of_nodes_at_specified_height};
}

template<typename T>
int number_of_father_with_single_child(Node<T> *tree) {
    //First, handle what comes up from children
    std::list<int> ll;
    for (auto &child: tree->children) {
        auto ret = number_of_father_with_single_child(child);
        ll.push_back(ret);
    }

    //Then, find a way to treat the father as the children
    if (tree->children.size() == 0) { // leaf (usually always present)
        ll.emplace_back(0);
    } else if (tree->children.size() == 1) //specific case that need attention
        ll.emplace_back(1);
    else {
        // nothing relevant here
    }

    //Compute what to return
    int num = sum_utils(ll);

    return num;
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

template<typename T>
int number_of_father_with_specified_number_of_children(Node<T> *tree, int num_of_children) {
    //First, handle what comes up from children
    std::list<int> ll;
    for (auto &child: tree->children) {
        auto ret = number_of_father_with_specified_number_of_children(child, num_of_children);
        ll.push_back(ret);
    }

    //Then, find a way to treat the father as the children
    if (tree->children.size() == 0) { // leaf (usually always present)
        ll.emplace_back(0);
    }
    if (tree->children.size() == num_of_children) //specific case that need attention
        ll.emplace_back(1);


    //Compute what to return
    int num = sum_utils(ll);

    return num;
}

#endif //RECURSION_TREE_H
