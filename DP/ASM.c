//
// Created by 张智博 on 2024/6/6.
//
#include <stdio.h>
#include <string.h>
#include <math.h>

// 定义 ASM 函数
int ASM(char P[], char T[], int m, int n, int K) {
    int i, j;
    int D[m+1][n+1];
    for (j = 0; j <= n; j++) D[0][j] = 0;
    for (i = 0; i <= m; i++) D[i][0] = i;
    for (j = 1; j <= n; j++) {
        for (i = 1; i <= m; i++) {
            if (P[i-1] == T[j-1])
                D[i][j] = fmin(fmin(D[i-1][j-1], D[i-1][j] + 1), D[i][j-1] + 1);
            else
                D[i][j] = fmin(fmin(D[i-1][j-1] + 1, D[i-1][j] + 1), D[i][j-1] + 1);
            if (D[m][j] <= K) return j;
        }
    }
    return -1; // 如果没有找到符合条件的子字符串，则返回 -1
}

// 主函数
int main() {
    // 定义模式和文本
    char P[] = "abc";
    char T[] = "zabcxyz";

    // 模式和文本的长度
    int m = strlen(P);
    int n = strlen(T);

    // 最大允许的编辑距离
    int K = 1;

    // 调用 ASM 函数
    int result = ASM(P, T, m, n, K);

    // 输出结果
    if (result != -1)
        printf("在位置 %d 处找到与模式最接近的子字符串。\n", result);
    else
        printf("没有找到符合条件的子字符串。\n");

    return 0;
}
