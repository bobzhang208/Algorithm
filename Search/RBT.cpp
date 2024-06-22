//
// Created by 张智博 on 2024/6/3.
//
#include "RBT.h"
#include <iostream>
#include <iomanip>
#include "queue"

using namespace std;

void RedBlackTree::insert(int key) {
    Node *newNode = new Node(key);
    Node *current = root;
    Node *parent = NULL;
    // 找到插入位置
    while (current != NULL) {
        parent = current;
        if (key < current->data) {
            current = current->left;
        } else if (key > current->data) {
            current = current->right;
        } else {
            // 若节点已存在，则直接返回
            delete newNode;
            return;
        }
    }

    newNode->parent = parent;
    // 插入新节点
    if (parent == NULL) {
        // 空树，直接将新节点设为根节点
        root = newNode;
    } else if (key < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    // 调整红黑树
    insertFixup(newNode);
}

void RedBlackTree::insertFixup(Node *node) {
    Node *parent = NULL;
    Node *grandparent = NULL;

    // 如果当前节点不是根节点，并且当前节点和其父节点都是红色
    while (node != root && !node->isBlack && !node->parent->isBlack) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {  // 如果父节点是祖父节点的左子节点
            Node *uncle = grandparent->right;

            if (uncle != NULL && uncle->isBlack == false) {  // 情况1：叔叔节点是红色
                parent->isBlack = true;
                uncle->isBlack = true;
                grandparent->isBlack = false;
                node = grandparent;
            } else {
                if (node == parent->right) {  // 情况2：叔叔节点是黑色，当前节点是右子节点
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                // 情况3：叔叔节点是黑色，当前节点是左子节点
                rotateRight(grandparent);
                std::swap(parent->isBlack, grandparent->isBlack);
                node = parent;
            }
        } else {  // 如果父节点是祖父节点的右子节点
            Node *uncle = grandparent->left;

            if (uncle != NULL && uncle->isBlack == false) {  // 情况1：叔叔节点是红色
                parent->isBlack = true;
                uncle->isBlack = true;
                grandparent->isBlack = false;
                node = grandparent;
            } else {
                if (node == parent->left) {  // 情况2：叔叔节点是黑色，当前节点是左子节点
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                // 情况3：叔叔节点是黑色，当前节点是右子节点
                rotateLeft(grandparent);
                std::swap(parent->isBlack, grandparent->isBlack);
                node = parent;
            }
        }
    }
    root->isBlack = true;  // 保证根节点始终是黑色
}

void RedBlackTree::rotateLeft(Node *node) {
    Node *temp = node->right;
    node->right = temp->left;
    if (temp->left != nullptr) {
        temp->left->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == nullptr) {
        root = temp;
    } else if (node == node->parent->left) {
        node->parent->left = temp;
    } else {
        node->parent->right = temp;
    }
    temp->left = node;
    node->parent = temp;
}

void RedBlackTree::rotateRight(Node *node) {
    Node *temp = node->left;
    node->left = temp->right;
    if (temp->right != nullptr) {
        temp->right->parent = node;
    }
    temp->parent = node->parent;
    if (node->parent == nullptr) {
        root = temp;
    } else if (node == node->parent->right) {
        node->parent->right = temp;
    } else {
        node->parent->left = temp;
    }
    temp->right = node;
    node->parent = temp;
}

void RedBlackTree::remove(int key) {
    Node *z = root;
    Node *x;
    Node *y;
    Node *parent = nullptr;

    // 查找要删除的节点
    while (z != nullptr) {
        if (z->data == key) {
            break;
        } else if (z->data < key) {
            parent = z;
            z = z->right;
        } else {
            parent = z;
            z = z->left;
        }
    }

    if (z == nullptr) {
        std::cout << "Key not found in the tree.\n";
        return;
    }

    y = z;
    bool yOriginalColor = y->isBlack;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->isBlack;
        x = y->right;

        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isBlack = z->isBlack;
    }

    // 删除节点后，更新父节点指针
    if (x != nullptr) {
        x->parent = y;
    }

    delete z;

    if (yOriginalColor) {
        // 调整红黑树以修复删除后的可能破坏的性质
        deleteFixup(x, parent);
    }

    // 更新根节点
    if (root != nullptr && root->parent != nullptr) {
        root = root->parent;
    }
}


void RedBlackTree::deleteFixup(Node *x, Node *parent) {
    while (x != root && (x == nullptr || x->isBlack)) {
        if (x == parent->left) {
            // x是左孩子, w是x的兄弟节点
            Node *w = parent->right;

            if (!w->isBlack) {
                // 情况1：x的兄弟节点w是红色的
                w->isBlack = true;
                parent->isBlack = false;
                rotateLeft(parent);
                w = parent->right;
            }

            if ((w->left == nullptr || w->left->isBlack) && (w->right == nullptr || w->right->isBlack)) {
                // 情况2：x的兄弟节点w是黑色的，且w的两个孩子都是黑色的
                w->isBlack = false;
                x = parent;
                parent = x->parent;
            } else {
                // 情况3：x的兄弟节点w是黑色的，且w的左孩子是红色，右孩子是黑色
                if (w->right == nullptr || w->right->isBlack) {
                    if (w->left != nullptr) w->left->isBlack = true;
                    w->isBlack = false;
                    rotateRight(w);
                    w = parent->right;
                }
                w->isBlack = parent->isBlack;
                parent->isBlack = true;
                if (w->right != nullptr) w->right->isBlack = true;
                rotateLeft(parent);
                x = root;
                break;
            }
        } else {
            Node *w = parent->left;

            // 情况1: x的兄弟节点w是红色的
            if (!w->isBlack) {
                w->isBlack = true;
                parent->isBlack = false;
                rotateRight(parent);
                w = parent->left;   // 兄弟节点变成P的右孩子
            }
            // 情况2: x的兄弟节点w是黑色的，且w的两个孩子都是黑色的
            if ((w->left == nullptr || w->left->isBlack) && (w->right == nullptr || w->right->isBlack)) {
                w->isBlack = false;     // 兄弟节点变成红色
                x = parent;     // 上移
                parent = x->parent;    // 上移， 开始下一轮循环
            } else {
                if (w->left == nullptr || w->left->isBlack) {
                    // 情况3: x的兄弟节点w是黑色的，左孩子是空或者是黑色
                    if (w->right != nullptr) w->right->isBlack = true;
                    w->isBlack = false;
                    rotateLeft(w);
                    w = parent->left;
                }
                // 情况4: x的兄弟节点w是黑色的，且w的左孩子是红色
                w->isBlack = parent->isBlack;   // 兄弟节点颜色变成家长颜色
                parent->isBlack = true;         // 父节点变成黑色
                if (w->left != nullptr) w->left->isBlack = true;    // 兄弟节点的左孩子变成黑色(兄弟的左子节点变成兄弟节点颜色)
                rotateRight(parent);
                x = root;
                break;
            }
        }
    }

    if (x != nullptr) x->isBlack = true;
}


void RedBlackTree::transplant(Node *u, Node *v) {
    // 用v替换u
    if (u->parent == nullptr) {
        root = v;   //如果u是根节点，直接用v替换u，即v成为根节点
    } else if (u == u->parent->left) {
        u->parent->left = v; //如果u是左孩子，用v替换u，即v成为左孩子
    } else {
        u->parent->right = v; //如果u是右孩子，用v替换u，即v成为右孩子
    }

    if (v != nullptr) {
        v->parent = u->parent;  //如果v不为空，将v的父节点指向u的父节点
    }
}

Node *RedBlackTree::minimum(Node *node) {
    // 找到以node为根的子树的最小节点
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void RedBlackTree::printTreeHelper(Node *node) {
    if (node == nullptr) return;
    std::queue<Node *> q;
    q.push(node);

    while (!q.empty()) {
        Node *current = q.front();
        q.pop();
        std::cout << current->data << (current->isBlack ? "(B)" : "(R)") << " ";

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
    std::cout << std::endl;
}

// 打印树
void RedBlackTree::printTree() {
    printTreeHelper(root);
}

void RedBlackTree::destroyTree(Node *node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}