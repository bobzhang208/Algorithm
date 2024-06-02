cmake_minimum_required(VERSION 3.27)
project(Algorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sort Sort/sort_main.cpp
        Sort/bubbleSort.cpp
        Sort/heapSort.cpp
        Sort/insertSort.cpp
        Sort/mergeSort.cpp
        Sort/quickSort.cpp
        Sort/selectSort.cpp
        Sort/shellSort.cpp
        Sort/sort.h
        Utils/utils.cpp
        Utils/utils.h)

add_executable(Search Search/search_main.cpp
        Utils/utils.cpp
        Utils/utils.h
        Search/BST.h
        Search/BST.cpp
)