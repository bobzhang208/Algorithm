//
// Created by 张智博 on 2024/5/13.
//
#include <iostream>

using namespace std;

void merge(int arr[], int left, int right, int middle) {
    int tmp[right - left + 1];
    int i = left;
    int j = middle + 1;
    int k = left;
    while ((i <= middle) && (j <= right)) {
        if (arr[i] < arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }

    if (i > middle) {
        for (int p = j; p <= right; p++) {
            tmp[k++] = arr[p];
        }
    } else {
        for (int p = i; p <= middle; p++) {
            tmp[k++] = arr[p];
        }
    }

    for (int p = left; p <= right; p++) {
        arr[p] = tmp[p];
    }
}

void mergeSort(int arr[], int first, int last) {
    if (first < last) {
        int middle = (first + last) / 2;
        mergeSort(arr, first, middle);
        mergeSort(arr, middle+1, last);

        merge(arr, first, last, middle);

    }
}