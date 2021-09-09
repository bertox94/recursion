#include <iostream>
#include "Node.h"
#include "Tree.h"

using namespace std;


int main() {

    std::srand(std::time(nullptr));


    auto tree = new Node<int>(std::rand() % 1000);

    add_children(tree, 1);

    print2D(tree);

    cout << max_depth(tree) << endl;
    cout << min_depth(tree) << endl;
    cout << how_many(tree) << endl;
    cout << max(tree) << endl;

    return 0;
}
