#include <iostream>
#include "sort.h"
#include "../Utils/utils.h"

using namespace std;

int main() {
    int arr[] = {6, 4, 16, 12, 21, 5};
    int n = sizeof(arr)/sizeof(int);
    cout << "Original array: ";
    printArray(arr, n);
    bubbleSort(arr, n);

    cout << "Sorted array: ";
    printArray(arr, n);

}
