//
// Created by 张智博 on 2024/6/2.
//
#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

const int N = 7;

int length(int range);

void Compress(int n, int p[], int s[], int l[], int b[], int minVals[]);

int TraceBack(int n, int l[], int b[], int minVals[]);  // 返回有多少个段
void Out(int m, int min_len, int l[], int b[], int minVals[]);

int main() {
    int p[] = {0, 255, 1, 5, 2, 1, 2};  // 图像灰度数组 下标从1开始计数
//    int p[] = {251, 251, 250, 254, 255, 245, 250};  // 图像灰度数组 下标从1开始计数
    int s[N] = {0}, l[N] = {0}, b[N] = {0}, minVals[N] = {0};

    cout << "图像的灰度序列为：" << endl;

    for (int i = 1; i < N; i++) {
        cout << p[i] << " ";
    }
    cout << endl;

    Compress(N - 1, p, s, l, b, minVals);
    int m = TraceBack(N - 1, l, b, minVals);
    Out(m, s[N - 1], l, b, minVals);
    return 0;
}

void Compress(int n, int p[], int s[], int l[], int b[], int minVals[]) {
    int Lmax = 256, header = 19; // 11位 + 8位存储最小值
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        int maxVal = p[i], minVal = p[i];
        b[i] = length(maxVal - minVal); // 计算单个像素点需要的存储位数（此处范围为0）
        int bmax = b[i];
        s[i] = s[i - 1] + bmax + header;
        l[i] = 1;
        minVals[i] = minVal;

        for (int j = 2; j <= i && j <= Lmax; j++)  // 最后一段含有一个像素，两个像素，所有像素
        {
            if (p[i - j + 1] > maxVal) maxVal = p[i - j + 1];
            if (p[i - j + 1] < minVal) minVal = p[i - j + 1];
            if (bmax < length(maxVal - minVal)) {
                bmax = length(maxVal - minVal); // 更新bmax为当前段内最大范围
            }


            if (s[i] > s[i - j] + j * bmax + header) {
                s[i] = s[i - j] + j * bmax + header;
                l[i] = j;
                b[i] = bmax;
                minVals[i] = minVal;  // 更新当前段的最小值
            }
        }
    }
}

int length(int range) {
    int k = 1;
    while (range > 0) {
        k++;
        range = range / 2;
    }
    return k;
}

int TraceBack(int n, int l[], int b[], int minVals[]) // 从后向前检查，因而之后对应段的，最后一个存储有效
{
    stack<int> ss;
    stack<int> minStack; // 用来保存每段的最小值
    ss.push(l[n]);
    ss.push(b[n]);
    minStack.push(minVals[n]);
    while (n != 0) {
        n = n - l[n];
        ss.push(l[n]); // l[0]=0,也被压入栈中
        ss.push(b[n]);
        minStack.push(minVals[n]);
    }
    int i = 0;
    while (!ss.empty()) {
        b[i] = ss.top();
        ss.pop();
        l[i] = ss.top(); // 此时 l[]，用来存储，第 i 组中，元素个数
        ss.pop();
        minVals[i] = minStack.top(); // 保存最小值
        minStack.pop();
        i++;
    }
    return i - 1;
}

void Out(int m, int min_len, int l[], int b[], int minVals[]) {
    int i = 0;
    cout << "最小长度：" << min_len << endl;
    cout << "共分成：" << m << "段" << endl;
    for (i = i + 1; i <= m; i++) {
        cout << "第" << i << "段含有" << l[i] << "元素. " << "需要存储位数" << b[i] << "，最小值为" << minVals[i]
             << endl;
    }
}
