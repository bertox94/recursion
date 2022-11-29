#include <iostream>
#include "Node.h"
#include "easy/basic.h"
#include "easy/Height.h"
#include "hard/ListNodes.h"
#include "easy/fathers.h"
#include "hard/children.h"
#include "easy/printing.h"
#include "easy/sorting.h"
#include <iomanip>
#include <string>

void testTree() {
    //TODO: give right attribute to child already prepared for them (e.g. the depth of the first call is 0, not -1)
    //Note: left attributes consider value of the curr plus children, right attr compute value for curr already because it doesn't depend on curr.
    // If it did, then it can't be a right attribute. on the other hand, node refers to the actual node,
    // and if the param is named curr_depth, it makes sense that curr_depth on node x, refers to its actual current_depth
    Node<int> *root;
    while (true) {
        cout << "Creating root..." << endl;
        root = new Node<int>(std::rand());
        cout << "Populating tree..." << endl;
        //root->add_children(100);
        auto nnum = build_tree(root, 0, 20, 5, 1);
        auto num = how_many(root);

        if (num < 100) {
            cout << "Tree is too small (" << num << ")\n" << endl;
        } else
            break;
        destroy(root);
    }
    cout << "Done" << endl;

    //print2D(root);
    //scan(root);

    cout << "-------" << endl;
    cout << endl;
    print(root);
    cout << "-------" << endl;
    cout << "sorted ##" << endl;
    sorted(root);
    print(root);
    cout << "-------" << endl;
    cout << endl;
    to_string(root);
    cout << "-------" << endl;
    cout << endl;

    auto maxval = max_value(root);
    auto minval = min_value(root);
    auto l = list_nodes(root);
    cout << "How many:       " << how_many(root) << endl;
    //cout << "How many (RightAttr):   " << how_many_variant(root, 0) << endl;
    cout << "Min depth:      " << min_depth(root) << endl;
    cout << "Max depth:      " << max_depth(root) << endl;
    cout << "Min value:      " << min_value(root) << endl;
    cout << "Max value:      " << max_value(root) << endl;
    cout << "N of leaves:    " << number_of_fathers_with_no_child(root) << endl;


    //for (auto i = 0; i <= max_depth(root, -1) + 25; i++) {
    //    string str = string("B degree (") + to_string(i) + "):";
    //
    //    cout << setw(13) << left << str
    //         << max_num_of_direct_children_at_depth(root, RightAttr<int>(-1, i)).num -
    //            std::get<1>(min_num_of_direct_children_at_depth(root, -1, i))
    //         << endl;//", " << res2 << endl;
    //}

    //cout << "Balance Factor: " << (double) number_of_fathers_with_no_child(root) / how_many(root) << endl;
    cout << "-------" << endl;
    for (auto i = minval; i <= minval + 25; i++) {
        string str = string("HMLT (") + to_string(i) + "):";
        auto res1 = how_many_like_this(root, i);
        //auto res2 = how_many_like_this_variant(root, i, 0);
        //if (res1 != res2)
        cout << setw(13) << left << str << res1 << endl;//", " << res2 << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("NNSH (") + to_string(i) + "):";
        cout << setw(13) << left << str << number_of_nodes_at_specific_height(root, i).second << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("NFSNC (") + to_string(i) + "):";
        cout << setw(13) << left << str << number_of_fathers_with_specified_number_of_children(root, i) << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("MaxNOCD (") + to_string(i) + "):";
        auto L = max_num_of_direct_children_at_depth(root, 0, i);
        cout << setw(13) << left << str << (std::get<0>(L) ? to_string(std::get<1>(L)) : "-") << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("MinNOCD (") + to_string(i) + "):";
        auto tuple = min_num_of_direct_children_at_depth(root, 0, i);
        cout << setw(13) << left << str << (get<0>(tuple) ? to_string(get<1>(tuple)) : "-") << endl;
    }

    cout << "-------" << endl;
    auto lll = list_nodes_II(root);
    std::vector<LeftAttr<int>> ll{lll.compositeList.begin(), lll.compositeList.end()};
    std::sort(ll.begin(), ll.end(), [](auto &left, auto &right) { return left.value < right.value; });
    int num = 0;
    for (auto &el: ll) {
        string str = string("Report (") + to_string(el.value) + "):";
        cout << setw(13) << left << str << to_string(el.num) << endl;
        if (num > 25) {
            break;
        }
        num++;
    }

    cout << "-------" << endl;
    auto llll = duplicates(root);
    std::vector<LeftAttr<int>> duplicatess{llll.compositeList.begin(), llll.compositeList.end()};
    std::vector<int> singletonss{llll.simpleList.begin(), llll.simpleList.end()};
    std::sort(duplicatess.begin(), duplicatess.end(),
              [](auto &left, auto &right) { return left.value < right.value; });
    std::sort(singletonss.begin(), singletonss.end(), [](auto &left, auto &right) { return left < right; });
    std::cout << "Elements that appear once: " << std::endl;
    num = 0;
    for (auto &el: singletonss) {
        cout << to_string(el) << endl;
        if (num > 25) {
            break;
        }
        num++;
    }

    cout << "-------" << endl;
    std::cout << "Elements that appear more then once: " << std::endl;
    num = 0;
    for (auto &el: duplicatess) {
        cout << to_string(el.value) << ", " << to_string(el.num) << endl;
        if (num > 25) {
            break;
        }
        num++;
    }
    cout << "-------" << endl;

    cout << "DDFSC:      " << depth_of_the_deepest_father_with_single_child(root, -1).second << endl;
    cout << "MNOC:      " << max_num_of_direct_children(root) << endl;
    auto tuple = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(root, -1, 1);
    cout << "NFWSCSMD:   " << get<1>(tuple) << ", " << get<2>(tuple) << endl;

    //auto ll = list_nodes(root);
    //cout << "List:       \n" << print(ll) << endl;

    destroy(root);
}

int main() {
    std::srand(std::time(nullptr));
    testTree();
    return 0;
}
