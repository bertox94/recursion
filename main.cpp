#include <iostream>
#include "Node.h"
#include "Tree.h"

using namespace std;

int main() {
    std::srand(std::time(nullptr));

    int times = 15;
    int times2 = 100;


    for (int i = 0; i < times; i++) {
        long long val = 0;
        for (int j = 0; j < times2; j++) {
            Node<int>* tree = create_tree<int>(i);
            val += how_many(tree);
            delete tree;
        }
        cout << i << ": " << val / times2 << endl;
    }

    /*
        print2D(tree);
        cout << "Max depth: " << max_depth(tree) << endl;
        cout << "Min depth: " << min_depth(tree) << endl;
        cout << "How many:  " << how_many(tree) << endl;
        cout << "Max:       " << max(tree) << endl;
        cout << "Min:       " << min(tree) << endl;
        //scan(tree);
    */

    return 0;
}
