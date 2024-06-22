//
// Created by 张智博 on 2024/6/9.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 链表节点定义
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// 创建一个新的链表节点
Node *createNode(int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// 向链表中添加一个新节点
void addNode(Node **head, int value) {
    Node *newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

// 释放链表内存
void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// 查找数组中的第一大和第二大元素
void find_first_and_second_largest(int arr[], int n, int *first_largest, int *second_largest) {
    if (n < 2) {
        printf("数组长度必须至少为2\n");
        return;
    }

    // 初始化比赛数组
    int *winners = (int *) malloc(n * sizeof(int));
    Node **opponents = (Node **) malloc(n * sizeof(Node *));
    for (int i = 0; i < n; i++) {
        winners[i] = arr[i];
        opponents[i] = NULL;
    }

    int round_size = n;

    // 锦标赛过程
    while (round_size > 1) {
        int next_round_size = (round_size + 1) / 2;
        for (int i = 0, j = 0; i < round_size; i += 2, j++) {
            if (i + 1 < round_size) {
                if (winners[i] > winners[i + 1]) {
                    winners[j] = winners[i];
                    addNode(&opponents[winners[j]], winners[i + 1]);
                } else {
                    winners[j] = winners[i + 1];
                    addNode(&opponents[winners[j]], winners[i]);
                }
            } else {
                winners[j] = winners[i];
            }
        }
        round_size = next_round_size;
    }

    *first_largest = winners[0];

    // 找到第二大元素
    Node *current = opponents[*first_largest];
    *second_largest = INT_MIN;
    while (current != NULL) {
        if (current->value > *second_largest) {
            *second_largest = current->value;
        }
        current = current->next;
    }

    // 释放链表内存
    for (int i = 0; i < n; i++) {
        if (opponents[i] != NULL) {
            freeList(opponents[i]);
        }
    }
    free(winners);
    free(opponents);
}

int main() {
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int first_largest, second_largest;

    find_first_and_second_largest(arr, n, &first_largest, &second_largest);

    printf("第一大数: %d, 第二大数: %d\n", first_largest, second_largest);
    return 0;
}
