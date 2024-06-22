#include<iostream>
#include<stack>

using namespace std;

const int N = 7;

int length(int i);

void Compress(int n, int p[], int s[], int l[], int b[]);

int TraceBack(int n, int l[], int b[]);  //返回有多少个段
void Out(int m, int min_len, int l[], int b[]);

int main() {
//    int p[] = {0,10,12,15,255,1,2};//图像灰度数组 下标从1开始计数
    int p[N] = {0, 255, 2, 8, 2, 1, 2};//图像灰度数组 下标从1开始计数
    int s[N] = {0}, l[N] = {0}, b[N] = {0};
    // s储存的是前i个像素点的最小存储位数
    // l储存的是第i段的像素点个数
    // b储存的是第i段的最大存储位数

    cout << "图像的灰度序列为：" << endl;

    for (int i = 0; i < N; i++) {
        cout << p[i] << " ";
    }
    cout << endl;
    Compress(N, p, s, l, b);

    int m = TraceBack(N - 1, l, b);
    Out(m, s[N - 1], l, b);
    return 0;
}

void Compress(int n, int p[], int s[], int l[], int b[]) {
    int Lmax = 256, header = 11;
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        b[i] = length(p[i]);//计算像素点p需要的存储位数``
        int bmax = b[i];
        s[i] = s[i - 1] + bmax;
        l[i] = 1;


        for (int j = 2; j <= i && j <= Lmax; j++)  //内层循环要依次向前找256次，每一次扩大最后一段的长度（+1），比较如果将前面的一位加入最后一段是否会更小
        {

            if (bmax < length(p[i - j + 1])) { // 因为需要将前面的某一位加入最后一段，所以需要确定新的最后一段最多要几位
                bmax = length(p[i - j + 1]);
            }

            if (s[i] > s[i - j] + j * bmax) {
                // 如果将前面的某一位加入最后一段，会使得总的存储位数更小，那么就加入
                s[i] = s[i - j] + j * bmax;
                l[i] = j;
                b[i] = bmax;
            }
        }
        s[i] += header;
    }
}

int length(int i) {
    int k = 1;
    i = i / 2;
    while (i > 0) {
        k++;
        i = i / 2;
    }
    return k;
    //return ceil(log(i+1)/log(2));
}

int TraceBack(int n, int l[], int b[]) //从后向前检查，因而之后对应段的，最后一个存储有效
{
    stack<int> ss;
    ss.push(l[n]);
    ss.push(b[n]);
    while (n != 0) {
        n = n - l[n];
        ss.push(l[n]);  //l[0]=0,也被压入栈中
        ss.push(b[n]);
    }
    int i = 0;
    while (!ss.empty()) {
        b[i] = ss.top();
        ss.pop();
        l[i] = ss.top(); //此时　ｌ[]，用来存储，第ｉ组中，元素个数
        ss.pop();
        i++;
    }
    return i - 1;
    // 返回的是有多少个段
}

void Out(int m, int min_len, int l[], int b[]) {
    int i = 0;
    cout << "最小长度：" << min_len << endl;
    cout << "共分成：" << m << "段" << endl;
    for (i = i + 1; i <= m; i++) {
        cout << "第一个段含有" << l[i] << "元素.   " << "需要存储位数" << b[i] << endl;
    }
}

//#include <iostream>
//#include <stack>
//#include <vector>
//
//using namespace std;
//
//const int N = 7;
//
//int length(int i);
//int Compress(int i, int p[], int s[], int l[], int b[], vector<int>& memo);
//int TraceBack(int n, int l[], int b[]);  // 返回有多少个段
//void Out(int m, int min_len, int l[], int b[]);
//
//int main() {
////     int p[] = {0,10,12,15,255,1,2};//图像灰度数组 下标从1开始计数
//     int p[] = {0, 255, 1, 5, 2, 1, 2};
////    int p[] = {251, 251, 250, 254, 255, 245, 250};  // 图像灰度数组 下标从1开始计数
//    int s[N] = {0}, l[N] = {0}, b[N] = {0};
//
//    cout << "图像的灰度序列为：" << endl;
//
//    for (int i = 1; i < N; i++) {
//        cout << p[i] << " ";
//    }
//    cout << endl;
//
//    // 初始化 memo 数组，使用 -1 表示尚未计算过
//    vector<int> memo(N, -1);
//
//    Compress(N - 1, p, s, l, b, memo);
//    int m = TraceBack(N - 1, l, b);
//    Out(m, s[N - 1], l, b);
//    return 0;
//}
//
//int Compress(int i, int p[], int s[], int l[], int b[], vector<int>& memo) {
//    if (i == 0) {
//        return 0;
//    }
//
//    if (memo[i] != -1) {
//        return memo[i];
//    }
//
//    int Lmax = 256, header = 11;
//    b[i] = length(p[i]);
//    int bmax = b[i];
//    s[i] = Compress(i - 1, p, s, l, b, memo) + bmax + header;
//    l[i] = 1;
//
//    for (int ii = 0; ii < memo.size(); ii++) {
//        cout << memo[ii] << " ";
//    }
//    cout << endl;
//    for (int j = 2; j <= i && j <= Lmax; j++) {
//        int len = length(p[i - j + 1]);
//        if (bmax < len) {
//            bmax = len;
//        }
//
//        int temp = Compress(i - j, p, s, l, b, memo) + j * bmax + header;
//        if (s[i] > temp) {
//            s[i] = temp;
//            l[i] = j;
//            b[i] = bmax;
//        }
//    }
//
//    memo[i] = s[i];
//    return s[i];
//}
//
//int length(int i) {
//    int k = 1;
//    i = i / 2;
//    while (i > 0) {
//        k++;
//        i = i / 2;
//    }
//    return k;
//    // return ceil(log(i+1)/log(2));
//}
//
//int TraceBack(int n, int l[], int b[]) {
//    stack<int> ss;
//    ss.push(l[n]);
//    ss.push(b[n]);
//    while (n != 0) {
//        n = n - l[n];
//        ss.push(l[n]);  // l[0]=0,也被压入栈中
//        ss.push(b[n]);
//    }
//    int i = 0;
//    while (!ss.empty()) {
//        b[i] = ss.top();
//        ss.pop();
//        l[i] = ss.top(); // 此时　ｌ[]，用来存储，第ｉ组中，元素个数
//        ss.pop();
//        i++;
//    }
//    return i - 1;
//}
//
//void Out(int m, int min_len, int l[], int b[]) {
//    int i = 0;
//    cout << "最小长度：" << min_len << endl;
//    cout << "共分成：" << m << "段" << endl;
//    for (i = i + 1; i <= m; i++) {
//        cout << "第一个段含有" << l[i] << "元素.   " << "需要存储位数" << b[i] << endl;
//    }
//}



