cmake_minimum_required(VERSION 3.22)
project(recursion)

set(CMAKE_CXX_STANDARD 20)

add_executable(recursion main.cpp easy/basic.h easy/depth.h easy/fathers.h easy/children.h hard/Height.h hard/ListNodes.h)
