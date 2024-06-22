//#include <iostream>
//#include <climits>
//#include "../utils/utils.h"
//
//using namespace std;
//
//void ExtractOrder(int low, int high, int **last, int MultiOrder[], int &next) {
//    if (high - low > 1) {
//        int k = last[low][high];
//        ExtractOrder(low, k, last, MultiOrder, next);
//        ExtractOrder(k, high, last, MultiOrder, next);
//        MultiOrder[next++] = k;
//    }
//}
//
//int MatrixOrder(int dim[], int n, int MultiOrder[]) {
//    int cost[n + 1][n + 1];
//    int *last[n + 1];
//    for (int i = 0; i <= n; i++) {
//        last[i] = new int[n + 1];
//    }
//
//    for (int i = n - 1; i >= 0; i--) {
//        for (int j = i + 1; j <= n; j++) {
//            if (j - i == 1) {
//                cost[i][j] = 0;
//                last[i][j] = -1;
//            } else {
//                int mcost = INT_MAX;
//                for (int k = i + 1; k < j; k++) {
//                    int a = cost[i][k];
//                    int b = cost[k][j];
//                    int c = dim[i] * dim[k] * dim[j];
//                    if ((a + b + c) < mcost) {
//                        mcost = a + b + c;
//                        last[i][j] = k;
//                    }
//                }
//                cost[i][j] = mcost;
//            }
//        }
//    }
//
//    int next = 0;
//    ExtractOrder(0, n, last, MultiOrder, next);
//
//    // Free the dynamically allocated memory
//    for (int i = 0; i <= n; i++) {
//        delete[] last[i];
//    }
//
//    return cost[0][n];
//}
//
//int main() {
//    int dim[] = {30, 1, 40, 10, 25};
//    int n = 4; // Number of matrices
//    int MultiOrder[4]; // Array to store the optimal multiplication order
//
//    int minCost = MatrixOrder(dim, n, MultiOrder);
//    cout << "Minimum number of multiplications: " << minCost << endl;
//
//    printArray(MultiOrder, n - 1); // Print the optimal multiplication order (split points
//
//    cout << "Optimal multiplication order (split points): ";
//    for (int i = 0; i < n - 1 && MultiOrder[i] != 0; i++) {
//        cout << MultiOrder[i] << " ";
//    }
//    cout << endl;
//
//    return 0;
//}



#include <stdio.h>
#include <limits.h>

int memo[100][100]; // 定义一个全局的二维数组来存储子问题的解
int split[100][100]; // 记录断开点的位置

// 定义一个递归函数来计算最小乘法次数
int matrixChainMemoized(int p[], int i, int j) {
    // 如果矩阵链中只有一个矩阵，则乘法次数为0
    if (i == j) {
        return 0;
    }

    // 如果子问题已经计算过，直接返回结果
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    // 初始化最小乘法次数为一个较大的数
    memo[i][j] = INT_MAX;

    // 尝试所有可能的断开点k
    for (int k = i; k < j; k++) {
        // 计算当前断开点的乘法次数
        int q = matrixChainMemoized(p, i, k) + matrixChainMemoized(p, k + 1, j) + p[i - 1] * p[k] * p[j];

        // 如果当前乘法次数小于之前的最小值，则更新最小值
        if (q < memo[i][j]) {
            memo[i][j] = q;
            split[i][j] = k; // 记录断开点的位置
        }
    }

    // 返回计算的最小乘法次数
    return memo[i][j];
}

// 包装函数来初始化memo数组并调用递归函数
int matrixChainOrder(int p[], int n) {
    // 初始化memo数组为-1，表示尚未计算过
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            memo[i][j] = -1;
        }
    }

    // 调用递归函数计算最小乘法次数
    return matrixChainMemoized(p, 1, n - 1);
}

// 函数来打印矩阵相乘的顺序
void printOptimalParens(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(i, split[i][j]);
        printOptimalParens(split[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    // 定义矩阵维度数组，p[i-1] x p[i] 表示第 i 个矩阵的维度
    int arr[] = {1, 2, 3, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    // 调用矩阵链乘法函数并打印结果
    int minMultiplications = matrixChainOrder(arr, size);
    printf("最少的乘法次数是 %d\n", minMultiplications);

    // 打印最优矩阵相乘顺序
    printf("最优矩阵相乘顺序是 ");
    printOptimalParens(1, size - 1);
    printf("\n");

    return 0;
}
