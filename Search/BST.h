//
// Created by 张智博 on 2024/6/2.
//

#ifndef ALGORITHM_SEARCH_H
#define ALGORITHM_SEARCH_H
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

TreeNode *bst_insert(TreeNode *root, int val, TreeNode *parent = nullptr);
void displayTree(TreeNode *root);
void inorder_tree_walk(TreeNode *root);
TreeNode *bst_search(TreeNode *root, int val);
TreeNode *bst_search_nonr (TreeNode *root, int val);
TreeNode *bst_findmin(TreeNode *root);
TreeNode *bst_findmax(TreeNode *root);
TreeNode *bst_findsuccessor(TreeNode *root);
TreeNode *bst_findpredecessor(TreeNode *root);
void bst_delNode(TreeNode *root, int val);
#endif //ALGORITHM_SEARCH_H
