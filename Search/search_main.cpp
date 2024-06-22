//
// Created by 张智博 on 2024/6/2.
//
#include <iostream>
#include "BST.h"
#include "RBT.h"
#include "../Utils/Utils.h"

using namespace std;

#define AL_CLS 2    // 1 for BST

int main() {
//    int arr[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
//    int arr[] = {7, 5, 12, 6};
    int arr[] = {10, 7, 25, 4, 8, 17, 28, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Orginal array: ";
    printArray(arr, n);

    switch (AL_CLS) {
        case 1: {
            TreeNode *root = nullptr;
            for (int i = 0; i < n; i++) {
                root = bst_insert(root, arr[i]);
            }
            displayTree(root);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
//            inorder_tree_walk(root);
//            TreeNode *s = bst_search(root, 7);
//            TreeNode *s = bst_search_nonr(root, 7);
//            TreeNode *s = bst_findmin(root);
//            TreeNode *s = bst_findsuccessor(bst_search(root, 4));
//            TreeNode *s = bst_findpredecessor(bst_search(root, 17));
            bst_delNode(root, 6);
//            cout << s->val << endl;
            displayTree(root);
            break;
        }


        case 2: {
            RedBlackTree tree;
            for (int key: arr) {
                tree.insert(key);
            }
            tree.printTree();
            tree.remove(17);
            break;
        }

        default: {
            cout << "Invalid input!" << endl;
            break;
        }

    }

}