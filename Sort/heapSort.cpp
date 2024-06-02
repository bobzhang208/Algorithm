//#include <iostream>
//#include "../Utils/utils.h"
//
//using namespace std;
//
//
//void heapify(int arr[], int n, int i) {
//    int largest = i; // 初始化最大值为根
//    int left = 2 * i + 1; // 左子节点索引
//    int right = 2 * i + 2; // 右子节点索引
//
//    // 如果左子节点大于根
//    if (left < n && arr[left] > arr[largest]) {
//        largest = left;
//    // 如果右子节点是目前已知的最大值
//    if (right < n && arr[right] > arr[largest]) {
//        largest = right;
//    }
//
//    // 如果最大值不是根
//    if (largest != i) {
//        swap(arr[i], arr[largest]);
//        // 递归地调整受影响的子堆
//        heapify(arr, n, largest);
//    }
//}
//
//// 用于将一个数组构建成一个最大堆的函数
//void buildHeap(int arr[], int n) {
//    // 从最后一个非叶子节点开始，直到根节点
//    for (int i = n / 2 - 1; i >= 0; i--) {
//        heapify(arr, n, i);
//        printArray(arr, n);
//    }
//}
//
//// 堆排序函数
//void heapSort(int arr[], int n) {
//    buildHeap(arr, n);
//
//    // 一个个从堆顶取出元素，然后重新调整堆
//    for (int i = n - 1; i > 0; i--) {
//        // 移动当前的根到数组的末尾
//        swap(arr[0], arr[i]);
//        // 调整减小了的堆
//        heapify(arr, i, 0);
//    }
//}
