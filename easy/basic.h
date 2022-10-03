//
// Created by Halib on 17.09.2022.
//

#ifndef RECURSION_BASIC_H
#define RECURSION_BASIC_H

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
void scan(Node<T> *node) {
    for (auto &child: node->children)
        scan(child);
}

// R1: depth
// L1: min_depth
template<typename T>
LeftAttr<T> max_depth(Node<T> *node, RightAttr<T> R) {

    LeftAttr<T> L;
    if (node->has_children()) {
        std::list<LeftAttr<T>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = max_depth(child, RightAttr<T>(_depth(R.depth + 1)));
            Lchildren.push_back(Lchild);
        }
        L = *max_element(Lchildren.begin(), Lchildren.end(),
                         [](auto &left, auto &right) { return left.depth < right.depth; });
    } else {
        L.depth = R.depth;
    }

    return L;
}

//always check that the base case makes sense, here in fact a tree with no child has depth = 0
// R1: depth
// L1: min_depth
template<typename T>
LeftAttr<T> min_depth(Node<T> *node, RightAttr<T> R) { //i.e. depth of the less deep leaf

    LeftAttr<T> L;
    if (node->has_children()) {
        std::list<LeftAttr<T>> Lchildren;
        for (auto &child: node->children) {
            auto Lchild = min_depth(child, RightAttr<T>(_depth(R.depth + 1)));
            Lchildren.push_back(Lchild);
        }
        L = *min_element(Lchildren.begin(), Lchildren.end(),
                         [](auto &left, auto &right) { return left.depth < right.depth; });
    } else {
        L.depth = R.depth;
    }

    return L;
}

template<typename T>
//L1: num of children
int how_many(Node<T> *node) {

    int L1;
    if (node->has_children()) {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto L1k = how_many(child);
            ll.push_back(L1k);
        }
        L1 = accumulate(ll.begin(), ll.end(), 0) + 1;
    } else {
        L1 = 1;
    }

    return L1;
}

template<typename T>
int how_many_variant(Node<T> *node, int R1i) {
    int R1 = R1i + 1;

    int L1;
    if (node->has_children()) {
        int L1k;
        for (auto &child: node->children) {
            L1k = how_many_variant(child, R1);
            R1 = L1k;
        }
        L1 = L1k;
    } else {
        L1 = R1;
    }

    return L1;
}

//the base case coincides with the tree being a leaf!
//here in fact max_utils(empty tree) doesn't make sense, so
//max of tree with one element (leaf) is the element, otherwise max_utils between...

//A tree consists of a root, and zero or more trees T1, T2, . . ., Tk
//An empty tree doesn't exist. At least root must be.
//When thinking what to return and stuff, just think that a leaf is just a root without children
//L1: max_value
template<typename T>
LeftAttr<T> max_value(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        std::list<T> list{*node->item};
        for (auto &child: node->children) {
            auto Lchild = max_value(child);
            list.push_back(Lchild.value);
        }
        L.value = *max_element(list.begin(), list.end());
    } else {
        L.value = *node->item;
    }

    return L;
}

//L1: min_value
template<typename T>
T min_value(Node<T> *node) {
    int L1;
    if (node->has_children()) {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto L1k = min_value(child);
            ll.push_back(L1k);
        }
        auto Ltemp = *min_element(ll.begin(), ll.end());
        L1 = min(Ltemp, *node->item);
    } else {
        L1 = *node->item;
    }

    return L1;
}

//R1: item as reference
//L1: number
template<typename T>
int how_many_like_this(Node<T> *node, T Rfather) {
    int R1 = Rfather;

    int L1;
    if (node->has_children()) {
        std::list<int> ll;
        for (auto &child: node->children) {
            auto L1k = how_many_like_this(child, R1);
            ll.push_back(L1k);
        }
        L1 = accumulate(
                ll.begin(), ll.end(), 0,
                [](auto acc, auto item) {
                    return acc + item;
                });
        if (*node->item == R1)
            L1++;
    } else {
        if (*node->item == R1) {
            L1 = 1;
        } else {
            L1 = 0;
        }
    }

    return L1;
}


#endif //RECURSION_BASIC_H
