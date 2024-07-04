//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

#include <iomanip>
#include <numeric>
#include <fstream>
#include <functional>
#include "../Node.h"

/**
 * TEMPLATE:
    * update descending values
    * declare all values to be returned
    if (leaf(node)) {
        * test the property on current only
        * provide the values to be returned out of current only
    } else {
        * get all the values to be returned from the children, as if existed only them
        * test the property on current only
        * get all the values to be returned from current only, as if existed only him
        * provide the values to be returned out of children + current
    }
    * can we update "for the father" only here and remove the if(leaf())?
    return values;
 */

// The trick of recursion is: the question is: bla bla complex. You draw the diagram and say,
// assume I have the solution of exactly bla bla complex of this branch coming up from this branch,
// and the same for the other branch, let's build the solution of bla bla complex to return to the branch upward.
// So basically you pretend to know the answer of the exactly same big question for the entire tree coming up from the branches

//divide functions based on the behavior on the base case (there you should see max, count)
//or counting, max/min

auto maximum = [](std::vector<int> vector) { return *std::max_element(vector.begin(), vector.end()); };
auto minimum = [](std::vector<int> vector) { return *std::min_element(vector.begin(), vector.end()); };

void print_to_file(Node *node, ofstream &myfile) {
    myfile << node->id << std::endl;
    for (auto &child: node->children) {
        print_to_file(child, myfile);
    }
}

Node *scan(Node *node, int id) {
    if (node->id == id)
        return node;
    auto child = node->children.begin();
    auto prev = child;
    while (child != node->children.end() && (*child)->id <= id) {
        prev = child;
        child++;
    }
    return scan(*prev, id);
}

int _depth(Node *node, int depth, const std::function<int(vector < int > )> &lambda) {
    if (node->has_children()) {
        std::vector<int> children_depths;
        for (auto &child: node->children) {
            children_depths.push_back(_depth(child, depth + 1, lambda));
        }
        return lambda(children_depths);
    }
    return depth;
}

int max_depth(Node *node, int depth) {
    return _depth(node, depth, maximum);
}

int min_depth(Node *node, int depth) {
    return _depth(node, depth, minimum);
}

//L1: num of children
int how_many(Node *node) {
    int num = 1;
    if (node->has_children()) {
        for (auto &child: node->children)
            num += how_many(child);
    }
    return num;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
//When thinking what to return and stuff, just think that a leaf is just a root without children
//L1: maxvalue_

int maxvalue_(Node *node) {
    if (node->has_children()) {
        std::vector<int> Ltemp;
        for (auto &child: node->children) {
            auto Lchild = maxvalue_(child);
            Ltemp.push_back(Lchild);
        }
        Ltemp.push_back(node->item);
        return maximum(Ltemp);
    }
    return node->item;
}

int minvalue_(Node *node) {
    if (node->has_children()) {
        std::vector<int> Ltemp;
        for (auto &child: node->children) {
            auto Lchild = maxvalue_(child);
            Ltemp.push_back(Lchild);
        }
        Ltemp.push_back(node->item);
        return minimum(Ltemp);
    }
    return node->item;
}

//R1: item as reference
//L1: number
//as an execrise you could remove the else branch when not necessary, for example here
int how_many_like_this(Node *node, int it) {
    int num = 0;
    if (node->has_children()) {
        for (auto &child: node->children) {
            auto Lchild = how_many_like_this(child, it);
            num += Lchild;
        }
    }
    if (node->item == it)
        num++;
    return num;
}


void destroy(Node *node) {
    for (auto &child: node->children) {
        destroy(child);
    }
    delete node;
}


#endif //RECURSION_BASIC_H
