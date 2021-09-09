#include <iostream>
#include "Node.h"


int main() {

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);


    auto root = new Node(new int(distrib(gen)));

    add_children(root, 1);

    print2D(root);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
