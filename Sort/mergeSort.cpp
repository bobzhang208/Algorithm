//
// Created by 张智博 on 2024/5/13.
//
#include <iostream>
#include <stack>

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
        mergeSort(arr, middle + 1, last);

        merge(arr, first, last, middle);

    }
}


struct MergeSortTask {
    int left;
    int right;
    bool mergeStep;
};

void mergeSortNotR(int arr[], int n) {
    stack<MergeSortTask> tasks;
    tasks.push({0, n - 1, false});

    while (!tasks.empty()) {
        MergeSortTask current = tasks.top();
        tasks.pop();

        int left = current.left;
        int right = current.right;
        int middle = left + (right - left) / 2;

        if (left < right) {
            if (current.mergeStep) {
                merge(arr, left, right, middle);
            } else {
                tasks.push({left, right, true});
                tasks.push({middle + 1, right, false});
                tasks.push({left, middle, false});
            }
        }
    }
}


void mergeSort_v2(int L[], int n) {
    while (n > 1) {
        int i = 0;  // Index starts from 0
        int j, k;

        do {
            // Find the first sorted part
            for (j = i; (j < n - 1) && (L[j] <= L[j + 1]); ++j);

            if (j == n - 1) {
                if (i == 0) return;  // Entire array is sorted
                else break;
            }

            // Find the second sorted part
            for (k = j + 1; (k < n - 1) && (L[k] <= L[k + 1]); ++k);

            merge(L, i, k, j);
            i = k + 1;
        } while (i <= n - 1);
    }
}