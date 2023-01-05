//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

#include <iomanip>
#include <numeric>
#include <fstream>
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

template<typename T>
void scan(Node<T> *node, ofstream &myfile) {
    myfile << node->id << std::endl;
    for (auto &child: node->children) {
        scan(child, myfile);
    }
}

template<typename T>
LeftAttr<T> max_depth(Node<T> *node, int depth) {
    return max_height(node);
}

// what the parent in the middle receives from the children is none other than the height that the children says to their father.
// Of course what th father will answer its father, to the original question that was once applied to the root of the tree,
// will be the height of the children + 1. And it is the same question that the children hve answered to their father.
template<typename T>
LeftAttr<T> max_height(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        std::vector<LeftAttr<T>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = max_height(child);
            Lchildren.push_back(Lchild);
        }
        return height_((*max_element(Lchildren.begin(), Lchildren.end(),
                                     [](auto &l, auto &r) { return l.height < r.height; })).height + 1);
    } else {
        return height_(0);
    }
}

template<typename T>
int min_depth(Node<T> *node, int depth) {

    if (node->has_children()) {
        int min_depth_ = -1;
        for (auto &child: node->children) {
            auto child_depth = min_depth(child, depth + 1);
            min_depth_ = min_depth_ == -1 ? child_depth : std::min(min_depth_, child_depth);
        }
        return min_depth_;
    } else {
        return depth;
    }
}

template<typename T>
int min_height(Node<T> *node) {

    if (node->has_children()) {
        int min_height_ = -1;
        for (auto &child: node->children) {
            auto child_depth = min_height(child);
            min_height_ = min_height_ == -1 ? child_depth : std::min(min_height_, child_depth);
        }
        return min_height_ + 1;
    } else {
        return 0;
    }
}

template<typename T>
//L1: num of children
int how_many(Node<T> *node) {

    if (node->has_children()) {
        int count = 0;
        for (auto &child: node->children) {
            auto child_count = how_many(child);
            count += child_count;
        }
        return count + 1;
    } else {
        return 1;
    }
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
//When thinking what to return and stuff, just think that a leaf is just a root without children
//L1: max_value
template<typename T>
T max_value(Node<T> *node) {
    if (node->has_children()) {
        T max_val_ = node->item;
        for (auto &child: node->children) {
            auto child_max_value = max_value(child);
            max_val_ = std::max(max_val_, child_max_value);
        }
        return max_val_;
    } else {
        return node->item;
    }
}

template<typename T>
T min_value(Node<T> *node) {
    if (node->has_children()) {
        T min_val_ = node->item;
        for (auto &child: node->children) {
            auto child_min_value = min_value(child);
            min_val_ = std::min(min_val_, child_min_value);
        }
        return min_val_;
    } else {
        return node->item;
    }
}

//R1: item as reference
//L1: number
//as an execrise you could remove the else branch when not necessary, for example here
template<typename T>
int how_many_like_this(Node<T> *node, T cmp) {
    if (node->has_children()) {
        int count = 0;
        for (auto &child: node->children) {
            auto child_count = how_many_like_this(child, cmp);
            count += child_count;
        }
        count += node->item == cmp ? 1 : 0;
        return count;
    } else {
        if (node->item == cmp) {
            return 1;
        } else {
            return 0;
        }
    }
}

template<typename T>
void destroy(Node<T> *node) {
    for (auto &child: node->children) {
        destroy(child);
    }
    delete node;
}


#endif //RECURSION_BASIC_H
