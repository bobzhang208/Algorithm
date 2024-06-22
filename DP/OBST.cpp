//#include <iostream>
//#include <vector>
//#include <limits>
//using namespace std;
//
//const int MAXN = 100;  // 假设最多有100个关键字
//const float MAXINT = numeric_limits<float>::max();
//
//// 定义节点结构
//struct node {
//    float key;
//    node *left, *right;
//    node(float k) : key(k), left(NULL), right(NULL) {}
//};
//
//// OBST算法
//void OBST(int n, float P[], float Q[], float C[][MAXN], float W[][MAXN], int R[][MAXN]) {
//    int i, s, r, low, high, broot;
//    float bcost, rcost;
//
//    for (i = 1; i <= n; i++) {
//        C[i][i-1] = 0;
//        W[i][i-1] = Q[i-1];
//    }
//
//    for (s = 0; s < n; s++) {
//        for (low = 1; low <= n-s; low++) {
//            high = low + s;
//            W[low][high] = W[low][high-1] + P[high] + Q[high];
//            bcost = MAXINT;
//
//            for (r = low; r <= high; r++) {
//                rcost = W[low][high] + C[low][r-1] + C[r+1][high];
//                if (rcost < bcost) {
//                    bcost = rcost;
//                    broot = r;
//                }
//            }
//
//            C[low][high] = bcost;
//            R[low][high] = broot;
//        }
//    }
//}
//
//// 构造树
//void BuildTree(int low, int high, node *&root, float A[], int R[][MAXN]) {
//    if (low > high) return;
//    root = new node(A[R[low][high]]);
//    if (low < R[low][high])
//        BuildTree(low, R[low][high] - 1, root->left, A, R);
//    if (high > R[low][high])
//        BuildTree(R[low][high] + 1, high, root->right, A, R);
//}
//
//// 打印树 (中序遍历)
//void InOrder(node* root) {
//    if (root == NULL) return;
//    InOrder(root->left);
//    cout << root->key << " ";
//    InOrder(root->right);
//}
//
//int main() {
//    int n = 5;
//    float P[] = {0, 0.05, 0.08, 0.37, 0.1, 0.4};  // P[0] 不用
//    float Q[] = {0.06, 0.3, 0.1, 0.1, 0.04, 0.1};
//    float A[] = {0, 1, 2, 3, 4, 5};  // A[0] 不用，假设关键字是1到5
//    float C[MAXN][MAXN] = {0};
//    float W[MAXN][MAXN] = {0};
//    int R[MAXN][MAXN] = {0};
//
//    OBST(n, P, Q, C, W, R);
//
//    node* root = NULL;
//    BuildTree(1, n, root, A, R);
//
//    cout << "Root of the Optimal Binary Search Tree: " << A[R[1][n]] << endl;
//
//    cout << "In-Order Traversal of the Optimal Binary Search Tree:" << endl;
//    InOrder(root);
//
//    return 0;
//}

#include <stdio.h>
#include <limits.h>

// 定义全局数组来存储子问题的解
float memo[100][100]; // 备忘录数组，用于存储子问题的解
int root[100][100];   // 记录根节点数组，用于存储最优子树的根节点

// 定义概率数组，p是成功搜索的概率，q是搜索失败的概率
float p[100], q[100];

// 初始化备忘录数组
void initializeMemo(int n) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            memo[i][j] = -1; // 将memo数组初始化为-1，表示尚未计算过
        }
    }
}

// 计算最优二分搜索树的代价
float optCost(int i, int j) {
    // 如果子问题已经计算过，直接返回结果
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    // 如果 i > j，表示没有键，返回失败搜索的概率
    if (i > j) {
        return q[i];
    }

    // 如果 i == j，表示只有一个键，计算其搜索代价
    if (i == j) {
        memo[i][j] = p[i] + q[i] + q[i + 1];
        return memo[i][j];
    }

    // 计算从 i 到 j 的所有键及其失败概率的总和
    float sum_pq = 0;
    for (int k = i; k <= j; k++) {
        sum_pq += p[k];
    }
    for (int k = i; k <= j + 1; k++) {
        sum_pq += q[k];
    }

    // 初始化最小代价为一个较大的数
    float minCost = INT_MAX;
    int minRoot = -1;

    // 尝试所有可能的根节点 r，并计算其代价
    for (int r = i; r <= j; r++) {
        float cost = optCost(i, r - 1) + optCost(r + 1, j) + sum_pq;
        // 如果当前代价小于最小代价，更新最小代价和根节点
        if (cost < minCost) {
            minCost = cost;
            minRoot = r;
        }
    }

    // 存储计算结果到备忘录数组
    memo[i][j] = minCost;
    root[i][j] = minRoot;
    return minCost;
}

// 打印最优二分搜索树的结构
void printOBST(int i, int j, int parent, char *direction) {
    if (i > j) {
        printf("d%d is the %s child of k%d\n", i, direction, parent);
        return;
    }

    int r = root[i][j];
    printf("k%d is the %s child of k%d\n", r, direction, parent);
    printOBST(i, r - 1, r, "left");
    printOBST(r + 1, j, r, "right");
}

int main() {
    // 输入n个键
    int n = 5;
    float keys[] = {0, 10, 20, 30, 40, 50}; // 键
    float pvals[] = {0, 0.1, 0.2, 0.4, 0.2, 0.1}; // 成功搜索的概率
    float qvals[] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1}; // 失败搜索的概率

    for (int i = 0; i <= n; i++) {
        p[i] = pvals[i];
        q[i] = qvals[i];
    }

    // 初始化备忘录数组
    initializeMemo(n);

    // 计算最小搜索代价
    float cost = optCost(1, n);
    printf("最小的搜索代价是: %.2f\n", cost);

    // 打印最优二分搜索树的结构
    printf("最优二分搜索树的结构:\n");
    printOBST(1, n, 0, "root");

    return 0;
}
