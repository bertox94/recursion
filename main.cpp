#include <iostream>
#include "Node.h"
#include "Tree.h"

using namespace std;


int main() {

    std::srand(std::time(nullptr));


    auto root = new Node<int>(std::rand() % 1000);

    add_children(root, 1);

    print2D(root);

    cout << max_depth(root) << endl;
    cout << min_depth(root) << endl;
    cout << how_many(root) << endl;
    cout << max(root) << endl;

    return 0;
}
