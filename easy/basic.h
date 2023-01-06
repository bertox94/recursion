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
    return depth_(max_height(node).height);
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
LeftAttr<T> min_depth(Node<T> *node, int depth) {
    return depth_(min_height(node).height);
}

template<typename T>
LeftAttr<T> min_height(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        std::vector<LeftAttr<T>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = min_height(child);
            Lchildren.push_back(Lchild);
        }
        return height_((*min_element(Lchildren.begin(), Lchildren.end(),
                                     [](auto &l, auto &r) { return l.height < r.height; })).height + 1);
    } else {
        return height_(0);
    }
}

template<typename T>
//L1: num of children
LeftAttr<T> how_many(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        L.num = 0;
        for (auto &child: node->children) {
            auto Lchild = how_many(child);
            L.num += Lchild.num;
        }
        L.num++;
        return L;
    } else {
        return num_(1);
    }
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
//When thinking what to return and stuff, just think that a leaf is just a root without children
//L1: maxvalue_
template<typename T>
LeftAttr<T> maxvalue_(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        std::vector<LeftAttr<T>> Ltemp;
        for (auto &child: node->children) {
            auto Lchild = maxvalue_(child);
            Ltemp.push_back(Lchild);
        }
        Ltemp.push_back(value_(node->item));
        return value_((*max_element(Ltemp.begin(), Ltemp.end(),
                                    [](auto &l, auto &r) { return l.height < r.height; })).value);
    } else {
        return value_(node->item);
    }
}

template<typename T>
LeftAttr<T> minvalue_(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        std::vector<LeftAttr<T>> Ltemp;
        for (auto &child: node->children) {
            auto Lchild = minvalue_(child);
            Ltemp.push_back(Lchild);
        }
        Ltemp.push_back(value_(node->item));
        return value_((*min_element(Ltemp.begin(), Ltemp.end(),
                                    [](auto &l, auto &r) { return l.height < r.height; })).value);
    } else {
        return value_(node->item);
    }
}

//R1: item as reference
//L1: number
//as an execrise you could remove the else branch when not necessary, for example here
template<typename T>
LeftAttr<T> how_many_like_this(Node<T> *node, RightAttr<T> R) {
    LeftAttr<T> L;
    if (node->has_children()) {
        L.num = 0;
        for (auto &child: node->children) {
            auto Lchild = how_many_like_this(child, R);
            L.num += Lchild.num;
        }
        L.num += node->item == R.value ? 1 : 0;
        return L;
    } else {
        if (node->item == R.value) {
            return num_(1);
        } else {
            return num_(0);
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
