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

int main() {
    std::srand(std::time(nullptr));

    cout << "Creating tree..." << endl;
    Node<int> *tree = create_tree<int>(140);
    cout << "Done" << endl;

    //print2D(tree);
    //scan(tree);
    cout << endl;
    auto maxval = max_value(tree);
    auto minval = min_value(tree);
    cout << "How many:   " << how_many(tree) << endl;
    cout << "Min depth:  " << min_depth(tree) << endl;
    cout << "Max depth:  " << max_depth(tree) << endl;
    cout << "Min value:  " << min_value(tree) << endl;
    cout << "Max value:  " << max_value(tree) << endl;
    cout << "N of leaves: " << number_of_fathers_with_no_child(tree) << endl;
    //cout << "-------" << endl;
    //for (auto i = minval; i <= maxval; i++) {
    //    string str = string("HMLT (") + to_string(i) + "):";
    //    cout << setw(13) << left << str << how_many_like_this(tree, i) << endl;
    //}
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
    cout << "DDFSC:      " << depth_of_the_deepest_father_with_single_child(tree) << endl;
    auto pair = number_of_fathers_with_specified_number_of_children_at_maximal_and_thus_same_depth(tree);
    cout << "NFWSCSMD:   " << pair.first << ", " << pair.second << endl;
    //auto ll = list_nodes(tree);
    //cout << "List:       \n" << print(ll) << endl;

    delete tree;

    return 0;
}
