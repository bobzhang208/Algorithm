#include <iostream>
#include "sort.h"
#include "../Utils/utils.h"

using namespace std;

int main() {
    int arr[] = {10, 4, 16, 12, 21, 5};
    int n = sizeof(arr)/sizeof(int);
    cout << "Original array: ";
//    printArray(arr, n);
//    bubbleSort(arr, n);
//    quickSortNotR(arr, 0, n-1);
    quickSort(arr, 0, n-1);
//    mergeSortNotR(arr, n);
//    mergeSort_v2(arr, n);
//    heapSort(arr, n);
    cout << "Sorted array: ";
    printArray(arr, n);

}
