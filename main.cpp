#include <iostream>
#include "Node.h"
#include "Tree.h"
#include "basic.h"
#include <sstream>
#include <iomanip>

using namespace std;


string print(const list<int> &ll) {
    stringstream ss;
    for (auto &el: ll) {
        ss << el << endl;
    }
    return ss.str();
}

template<int index>
struct TupleLess {
    template<typename Tuple>
    bool operator()(const Tuple &left, const Tuple &right) const {
        return std::get<index>(left) < std::get<index>(right);
    }
};

int main() {
    std::srand(std::time(nullptr));

    cout << "Creating tree..." << endl;
    Node<int> *tree = create_tree<int>(100);
    cout << "Done" << endl;

    //print2D(tree);
    //scan(tree);
    cout << endl;
    auto maxval = max_value(tree);
    auto minval = min_value(tree);
    cout << "How many:   " << how_many(tree) << endl;
    //cout << "How many (R):   " << how_many_variant(tree, 0) << endl;
    cout << "Min depth:  " << min_depth(tree, -1) << endl;
    cout << "Max depth:  " << max_depth(tree, -1) << endl;
    cout << "Min value:  " << min_value(tree) << endl;
    cout << "Max value:  " << max_value(tree) << endl;
    //cout << "N of leaves: " << number_of_fathers_with_no_child(tree) << endl;
    //cout << "-------" << endl;
    for (auto i = minval; i <= minval + 25; i++) {
        string str = string("HMLT (") + to_string(i) + "):";
        auto res1 = how_many_like_this(tree, i);
        //auto res2 = how_many_like_this_variant(tree, i, 0);
        //if (res1 != res2)
        cout << setw(13) << left << str << res1 << endl;//", " << res2 << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("NNSH (") + to_string(i) + "):";
        cout << setw(13) << left << str << number_of_nodes_at_specific_height(tree, i).second << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("NFSNC (") + to_string(i) + "):";
        cout << setw(13) << left << str << number_of_fathers_with_specified_number_of_children(tree, i) << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("MaxNOCD (") + to_string(i) + "):";
        auto tuple = max_num_of_direct_children_at_depth(tree, -1, i);
        cout << setw(13) << left << str << (get<0>(tuple) ? to_string(get<1>(tuple)) : "-") << endl;
    }
    cout << "-------" << endl;
    for (auto i = 0; i <= 25; i++) {
        string str = string("MinNOCD (") + to_string(i) + "):";
        auto tuple = min_num_of_direct_children_at_depth(tree, -1, i);
        cout << setw(13) << left << str << (get<0>(tuple) ? to_string(get<1>(tuple)) : "-") << endl;
    }

    cout << "-------" << endl;
    auto lll = list_nodes_II(tree);
    std::vector<std::tuple<int, int>> ll{lll.begin(), lll.end()};
    std::sort(ll.begin(), ll.end(), [](auto &left, auto &right) { return std::get<0>(left) > std::get<0>(right); });
    int i = 0;
    for (auto &el: ll) {
        string str = string("Report (") + to_string(std::get<1>(el)) + "):";
        cout << setw(13) << left << str << to_string(std::get<0>(el)) << endl;
        i++;
        if (i == 25)
            break;
    }

    //cout << "DDFSC:      " << depth_of_the_deepest_father_with_single_child(tree, -1).second << endl;
    cout << "MNOC:      " << max_num_of_direct_children(tree) << endl;
    auto tuple = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(tree, -1, 1);
    cout << "NFWSCSMD:   " << get<1>(tuple) << ", " << get<2>(tuple) << endl;
    //auto ll = list_nodes(tree);
    //cout << "List:       \n" << print(ll) << endl;

    delete tree;

    return 0;
}
