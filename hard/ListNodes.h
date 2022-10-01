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
    if (node->has_children()) { //Lchildren would be used if this was std::list<std::list<int>>, if the tyoe is similar to the return one, then call it Ltemp
        for (auto &child: node->children) {
            auto Lchild = list_nodes(child);
            L.list.splice(L.list.end(), Lchild.list);
        }
        L.list.push_back(*node->item);
    } else {
        L.list.push_back(*node->item);
    }

    return L;
}

template<typename T>
LeftAttr<T> list_nodes_II(Node<T> *node) {
    LeftAttr<T> L;
    if (node->has_children()) {
        for (auto &child: node->children) {
            auto Lchild = list_nodes_II(child);

            for (auto &LAttr1: Lchild.llist) {
                bool found = false;
                for (auto &LAttr2: L.llist) {
                    if (LAttr1.value == LAttr2.value) {
                        LAttr2.num += LAttr1.num;
                        found = true;
                        break;
                    }
                }
                if (!found)
                    L.llist.push_back(LeftAttr<T>(LAttr1.num, LAttr1.value));
            }
        }
        bool found = false;
        for (auto &LAttr: L.llist) {
            if (*node->item == LAttr.value) {
                LAttr.num++;
                found = true;
                break;
            }
        }
        if (!found)
            L.llist.emplace_back(1, *node->item);
    } else {
        L.llist.emplace_back(1, *node->item);
    }

    return L;
}

template<typename T>
std::tuple<std::list<std::tuple<int, int>>, std::list<int>> duplicates(Node<T> *node) {
    std::tuple<std::list<std::tuple<int, int>>, std::list<int>> L;
    if (node->has_children()) {
        std::tuple<std::list<std::tuple<int, int>>, std::list<int>> Ltemp;
        for (auto &child: node->children) {
            auto Lchild = duplicates(child);

            // We assume that one number can either be in Ltemp list or Ltemp singleton, not both

            // elements in child singleton
            //      may appear in Ltemp list
            //          --> increase number of that element in Ltemp by 1
            //      may appear in Ltemp singletons
            //          --> push {2, elem} in Ltemp list
            //          --> remove elem from Ltemp singletons
            //      may not be in either of them
            //          --> append elem to Ltemp singletons

            // elements in child list
            //      may appear in Ltemp singletons
            //          --> append elem to Ltemp list and increment by one the number of occurrences (because we assume that one number can either be in Ltemp list or Ltemp singleton, not both)
            //          --> remove elem from Ltemp singletons
            //      may appear in Ltemp list
            //          --> increase number of that element in Ltemp by the corresponding number
            //      may not be in either of them
            //          --> append elem to Ltemp list

            for (auto &item: std::get<1>(Lchild)) {
                bool found = false;
                for (auto &tpl: std::get<0>(Ltemp)) {
                    if (item == std::get<1>(tpl)) {
                        std::get<0>(tpl)++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (auto it = std::get<1>(Ltemp).begin(); it != std::get<1>(Ltemp).end(); it++) {
                        if (item == *it) {
                            std::get<0>(Ltemp).emplace_back(2, item);
                            it = std::get<1>(Ltemp).erase(it);
                            found = true;
                            break;
                        }
                    }
                }
                if (!found) {
                    std::get<1>(Ltemp).push_back(item);
                }
            }

            for (auto &tpl1: std::get<0>(Lchild)) {
                bool found = false;
                for (auto it = std::get<1>(Ltemp).begin(); it != std::get<1>(Ltemp).end(); it++) {
                    if (std::get<1>(tpl1) == *it) {
                        std::get<0>(Ltemp).emplace_back(std::get<0>(tpl1) + 1, std::get<1>(tpl1));
                        std::get<1>(Ltemp).erase(it);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (auto &tpl2: std::get<0>(Ltemp)) {
                        if (std::get<1>(tpl1) == std::get<1>(tpl2)) {
                            std::get<0>(tpl2) += std::get<0>(tpl1);
                            found = true;
                            break;
                        }
                    }
                }
                if (!found) {
                    std::get<0>(Ltemp).emplace_back(std::get<0>(tpl1), std::get<1>(tpl1));
                }
            }
        }

        //curr that appear in Ltemp list --> increase number
        //curr that appear in Ltemp singleton --> move them both to Ltemp list
        //curr that do not appear in Ltemp singleton --> append them to Ltemp singleton
        bool found = false;
        for (auto &tpl: std::get<0>(Ltemp)) {
            if (*node->item == std::get<1>(tpl)) {
                std::get<0>(tpl)++;
                found = true;
                break;
            }
        }
        if (!found) {
            for (auto it = std::get<1>(Ltemp).begin(); it != std::get<1>(Ltemp).end(); it++) {
                if (*node->item == *it) {
                    std::get<0>(Ltemp).emplace_back(2, *node->item);
                    it = std::get<1>(Ltemp).erase(it);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            std::get<1>(Ltemp).push_back(*node->item);
        }
        L = Ltemp;
    } else {
        std::tuple<std::list<std::tuple<int, int>>, std::list<int>> Ltemp;
        std::get<1>(Ltemp).push_back(*node->item);
        L = Ltemp;
    }


    return L;
}

#endif //RECURSION_LISTNODES_H
