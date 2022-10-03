//
// Created by Halib on 01.10.2022.
//

#ifndef RECURSION_LISTNODES_H
#define RECURSION_LISTNODES_H

#include <tuple>
#include "../Node.h"

template<typename T>
LeftAttr<T> list_nodes(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) { //Lchildren would be used if this was std::simpleList<std::simpleList<int>>, if the tyoe is similar to the return one, then call it Ltemp
        for (auto &child: node->children) {
            auto Lchild = list_nodes(child);
            L.simpleList.splice(L.simpleList.end(), Lchild.simpleList);
        }
        L.simpleList.push_back(*node->item);
    } else {
        L.simpleList.push_back(*node->item);
    }

    return L;
}

template<typename T>
LeftAttr<T> list_nodes_II(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        for (auto &child: node->children) {
            auto Lchild = list_nodes_II(child);

            for (auto &LAttr1: Lchild.compositeList) {
                bool found = false;
                for (auto &LAttr2: L.compositeList) {
                    if (LAttr1.value == LAttr2.value) {
                        LAttr2.num += LAttr1.num;
                        found = true;
                        break;
                    }
                }
                if (!found)
                    L.compositeList.push_back(LeftAttr<T>(_num(LAttr1.num), _value(LAttr1.value)));
            }
        }
        bool found = false;
        for (auto &LAttr: L.compositeList) {
            if (*node->item == LAttr.value) {
                LAttr.num++;
                found = true;
                break;
            }
        }
        if (!found)
            L.compositeList.emplace_back(_num(1), _value(*node->item));
    } else {
        L.compositeList.emplace_back(_num(1), _value(*node->item));
    }

    return L;
}

template<typename T>
LeftAttr<T> duplicates(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        for (auto &child: node->children) {
            auto Lchild = duplicates(child);

            // We assume that one number can either be in L simpleList or L singleton, not both

            // elements in child singleton
            //      may appear in L simpleList
            //          --> increase number of that element in L by 1
            //      may appear in L singletons
            //          --> push {2, elem} in L simpleList
            //          --> remove elem from L singletons
            //      may not be in either of them
            //          --> append elem to L singletons

            // elements in child simpleList
            //      may appear in L singletons
            //          --> append elem to L simpleList and increment by one the number of occurrences (because we assume that one number can either be in L simpleList or L singleton, not both)
            //          --> remove elem from L singletons
            //      may appear in L simpleList
            //          --> increase number of that element in L by the corresponding number
            //      may not be in either of them
            //          --> append elem to L simpleList

            for (auto &childSingleton: Lchild.simpleList) {
                bool found = false;
                for (auto &currMultiple: L.compositeList) {
                    if (childSingleton == currMultiple.value) {
                        currMultiple.num++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (auto currSingleton = L.simpleList.begin();
                         currSingleton != L.simpleList.end(); currSingleton++) {
                        if (childSingleton == *currSingleton) {
                            L.compositeList.push_back(LeftAttr<T>(_num(2), _value(childSingleton)));
                            currSingleton = L.simpleList.erase(currSingleton);
                            found = true;
                            break;
                        }
                    }
                }
                if (!found) {
                    L.simpleList.push_back(childSingleton);
                }
            }

            for (auto &childMultiple: Lchild.compositeList) {
                bool found = false;
                for (auto currSingleton = L.simpleList.begin(); currSingleton != L.simpleList.end(); currSingleton++) {
                    if (childMultiple.value == *currSingleton) {
                        L.compositeList.push_back(
                                LeftAttr<T>(_num(childMultiple.num + 1), _value(childMultiple.value)));
                        L.simpleList.erase(currSingleton);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (auto &currMultiple: L.compositeList) {
                        if (childMultiple.value == currMultiple.value) {
                            currMultiple.num += childMultiple.num;
                            found = true;
                            break;
                        }
                    }
                }
                if (!found) {
                    L.compositeList.push_back(LeftAttr<T>(_num(childMultiple.num), _value(childMultiple.value)));
                }
            }
        }

        //curr that appear in L simpleList --> increase number
        //curr that appear in L singleton --> move them both to L simpleList
        //curr that do not appear in L singleton --> append them to L singleton
        bool found = false;
        for (auto &currMultiple: L.compositeList) {
            if (*node->item == currMultiple.value) {
                currMultiple.num++;
                found = true;
                break;
            }
        }
        if (!found) {
            for (auto currSingleton = L.simpleList.begin(); currSingleton != L.simpleList.end(); currSingleton++) {
                if (*node->item == *currSingleton) {
                    L.compositeList.push_back(LeftAttr<T>(_num(2), _value(*node->item)));
                    L.simpleList.erase(currSingleton);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            L.simpleList.push_back(*node->item);
        }
    } else {
        L.simpleList.push_back(*node->item);
    }

    return L;
}

#endif //RECURSION_LISTNODES_H
