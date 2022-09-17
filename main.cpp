#include <iostream>
#include "Node.h"
#include "Tree.h"
#include <sstream>

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

    Node<int> *tree = create_tree<int>(100);

    //print2D(tree);
    scan(tree);
    cout << endl;
    cout << "Max depth: " << max_depth(tree) << endl;
    cout << "Min depth: " << min_depth(tree) << endl;
    cout << "How many:  " << how_many(tree) << endl;
    cout << "Max value: " << max_value(tree) << endl;
    cout << "Min value: " << min_value(tree) << endl;
    //auto ll = list_nodes(tree);
    //cout << "List:       \n" << print(ll) << endl;

    delete tree;

    return 0;
}
