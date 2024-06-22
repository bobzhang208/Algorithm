#include <iostream>
#include "../Utils/utils.h"

using namespace std;

#include <iostream>

void FixHeap(int arr[], int Hsize, int root, int k);

void BuildHeap(int arr[], int n);

void AfixHeap(int L[], int Hsize, int vac, int k);

void heapSort(int arr[], int n) {
    BuildHeap(arr, n);
    for (int i = n - 1; i >= 1; --i) {
        int temp = arr[i];
        arr[i] = arr[0];
//        FixHeap(arr, i, 0, temp);
        AfixHeap(arr, i, 0, temp);
    }
}

void BuildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
//        FixHeap(arr, n, i, arr[i]);
        AfixHeap(arr, n, i, arr[i]);
    }
}

void FixHeap(int arr[], int Hsize, int root, int k) {
    int larger = 0;
    if ((2 * root + 1) >= Hsize) {
        // 如果根节点是叶节点，直接放入 k
        arr[root] = k;
        return;
    } else if ((2 * root + 1) == Hsize - 1) {
        // 只有一个左孩子
        larger = 2 * root + 1;
    } else if (arr[2 * root + 1] > arr[2 * root + 2]) {
        larger = 2 * root + 1;
    } else {
        larger = 2 * root + 2;
    }

    if (k >= arr[larger]) {
        arr[root] = k;
    } else {
        arr[root] = arr[larger];
        FixHeap(arr, Hsize, larger, k);
    }
}


void AfixHeap(int L[], int Hsize, int vac, int k) {
    while ((2 * vac + 1) < Hsize) {
        // 如果有右孩子
        if (L[2 * vac + 1] < L[2 * vac + 2] && (2 * vac + 2) < Hsize) {
            // 右孩子更大
            L[vac] = L[2 * vac + 2];    // 将右孩子上移
            vac = 2 * vac + 2;  // 移动到右孩子
        } else {
            // 左孩子更大
            L[vac] = L[2 * vac + 1];    // 将左孩子上移
            vac = 2 * vac + 1;  // 移动到左孩子
        }
    }
    while (vac > 0 && k > L[(vac - 1) / 2]) {
        // 如果 k 比父节点大
        L[vac] = L[(vac - 1) / 2];  // 将父节点下移
        vac = (vac - 1) / 2;    // 移动到父节点
    }
    L[vac] = k; // 插入 k
}
