//
// Created by 张智博 on 2024/6/2.
//
#include "BST.h"
#include <iostream>
#include <queue>

using namespace std;


void displayTree(TreeNode *root) {
    if (!root) return;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            TreeNode *node = q.front();
            q.pop();

            if (node) {
                cout << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            } else {
                cout << "N ";
            }
        }

        cout << endl;
    }
}

// build a binary search tree
TreeNode *bst_insert(TreeNode *root, int val, TreeNode *parent) {
    if (root == nullptr) {
        TreeNode *newNode = new TreeNode;
        newNode->val = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = parent;
        return newNode;
    }

    if (val < root->val) {
        root->left = bst_insert(root->left, val, root);
    } else {
        root->right = bst_insert(root->right, val, root);
    }

    return root;
}

void bst_insert_Nonr(TreeNode *root, TreeNode *z) {
    TreeNode *x, *y;
    y = nullptr;
    x = root;
    while (x != nullptr) {//
        y = x;//结点的右子树中最左后继结点处
        if (z->val < x->val) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == nullptr) root = z;
    else if (z->val < y->val) y->left = z;
    else y->right = z;
}

void inorder_tree_walk(TreeNode *root) {
    if (root != NULL) {
        inorder_tree_walk(root->left);
        cout << root->val << " ";
        inorder_tree_walk(root->right);
    }
}

TreeNode *bst_search(TreeNode *root, int val) {
    if (root == nullptr || root->val == val) {
        return root;
    }

    if (val < root->val) {
        return bst_search(root->left, val);
    } else {
        return bst_search(root->right, val);
    }
}

TreeNode *bst_search_nonr(TreeNode *root, int val) {
    while (root != nullptr && root->val != val) {
        if (val < root->val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return root;
}

TreeNode *bst_findmin(TreeNode *root) {
    while (root->left != nullptr) {
        root = root->left;
    }

    return root;
}

TreeNode *bst_findmax(TreeNode *root) {
    while (root->right != nullptr) {
        root = root->right;
    }

    return root;
}

TreeNode *bst_findsuccessor(TreeNode *node) {
    if (node == nullptr) return nullptr;

    // Case 1: 如果节点有右子树，后继节点是右子树中的最左节点
    if (node->right) {
        TreeNode *current = node->right;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    // Case 2: 如果节点没有右子树，后继节点是其第一个右子节点的祖先
    TreeNode *parent = node->parent;
    while (parent && parent->right == node) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

TreeNode *bst_findpredecessor(TreeNode *node) {
    if (node == nullptr) return nullptr;

    // Case 1: 如果节点有左子树，前驱节点是左子树中的最右节点
    if (node->left) {
        TreeNode *current = node->left;
        while (current->right) {
            current = current->right;
        }
        return current;
    }

    // Case 2: 如果节点没有左子树，前驱节点是其第一个左子节点的祖先
    TreeNode *parent = node->parent;
    while (parent && parent->left == node) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void bst_delNode(TreeNode *root, int val) {
    TreeNode *node = bst_search(root, val);
    if (node == nullptr) return;

    // Case 1: 如果节点没有子节点
    if (node->left == nullptr && node->right == nullptr) {
        if (node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
    }

        // Case 2: 如果节点有一个子节点
    else if (node->left == nullptr || node->right == nullptr) {
        TreeNode *child = node->left ? node->left : node->right;
        if (node->parent->left == node) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        delete node;
    }

        // Case 3: 如果节点有两个子节点
    else {
        TreeNode *successor = bst_findsuccessor(node);
        node->val = successor->val;
        bst_delNode(successor, successor->val);
    }
}


