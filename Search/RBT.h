//
// Created by 张智博 on 2024/6/3.
//

#ifndef ALGORITHM_RBT_H
#define ALGORITHM_RBT_H

#include <iostream>
#include <algorithm>

struct Node {
    int data;
    bool isBlack;
    Node *left;
    Node *right;
    Node *parent;

    Node(int val) : data(val), isBlack(false), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() {
        destroyTree(root);
    }

//    bool search(int key);

    void insert(int key);

    void remove(int key);

    void printTree();
//
private:
    void insertFixup(Node *node);

    void deleteFixup(Node *node, Node *parent);

    void rotateLeft(Node *node);

    void rotateRight(Node *node);

    void transplant(Node *u, Node *v);

    void destroyTree(Node *node);

    void printTreeHelper(Node *node);

    Node *minimum(Node *node);

    Node *root;
};


#endif //ALGORITHM_RBT_H