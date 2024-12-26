#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

/**
 * 思路题解：
 * 
 * 这道题的目标是将一个蛋糕的总体积n分配成m层，每层的体积和表面积根据半径r和高度h决定。每一层都是一个圆柱体，要求找出满足体积和表面积要求的最优解。
 * 我们使用深度优先搜索（DFS）来进行递归搜索，从顶层开始，逐层构造蛋糕，直到满足目标体积。每一层的半径r和高度h需要满足一定的条件，同时需要计算每层的表面积（包括底面和侧面）。
 * 
 * 关键部分：
 * 1. **DFS递归搜索**：从最底层开始搜索，每一层的半径和高度递减。搜索过程中不断更新最小表面积。
 * 2. **剪枝**：为了提高效率，我们在递归过程中使用剪枝条件，如果当前搜索的状态已经超过了体积限制或表面积限制，则停止继续递归。
 * 3. **预处理**：我们提前计算每一层的最小体积和最小表面积，帮助我们在搜索过程中进行判断和剪枝。
 * 
 * 通过递归搜索，最终得到最小的表面积并输出。如果没有解，输出0。
 */

const int MAX_LAYER = 21;    // 最大层数
const int INF = 1000000000;  // 无解时的默认值

int n, m;               // n: 总体积, m: 层数
int minv[MAX_LAYER], mins[MAX_LAYER];  // minv[i]表示i层到1层加起来的最小总体积, mins[i]表示最小表面积
int best;               // 当前最小表面积

// 深度优先搜索函数
void DFS(int depth, int sumv, int sums, int r, int h) {
    // 如果深度为0，说明已经完成了蛋糕的构建，判断是否更新最小表面积
    if (depth == 0) {
        if (sumv == n && sums < best) {
            best = sums;
        }
        return;
    }
    // 剪枝条件：
    // 1. 当前体积 + 剩余最小体积 > n
    // 2. 当前表面积 + 剩余最小表面积 > best
    // 3. 当前表面积 + 剩余最小表面积不能超过best
    if (sumv + minv[depth - 1] > n || sums + mins[depth - 1] > best || sums + 2 * (n - sumv) / r >= best) {
        return;
    }
    // 递减顺序枚举当前层的半径r的每个可能值，最小值为depth
    for (int i = r - 1; i >= depth; --i) {
        if (depth == m) {
            sums = i * i; // 第m层时，设置外表面积的初始值
        }
        // 计算当前层的最大高度
        int maxh = (n - sumv - minv[depth - 1]) / (i * i) < h - 1 ? (n - sumv - minv[depth - 1]) / (i * i) : h - 1;
        // 枚举当前层的高度
        for (int j = maxh; j >= depth; --j) {
            // 递归调用DFS
            DFS(depth - 1, sumv + i * i * j, sums + 2 * i * j, i, j);
        }
    }
}

int main(void) {
    while (scanf("%d%d", &n, &m) != EOF) {
        best = INF;  // 初始化最小表面积为无限大
        int rmax = (int)sqrt((double)n); // 最大的半径值为sqrt(n)
        int hmax = n; // 最大的高度为n

        // 初始化minv和mins数组
        minv[0] = mins[0] = 0;
        for (int i = 1; i <= m; i++) {
            minv[i] = minv[i - 1] + i * i * i; // 计算每一层的最小体积
            mins[i] = mins[i - 1] + 2 * i * i; // 计算每一层的最小表面积
        }
        // 调用DFS进行递归搜索
        DFS(m, 0, 0, rmax, hmax);
        // 输出结果
        if (best == INF) {
            best = 0;  // 如果没有解，输出0
        }
        printf("%d\n", best);
    }
    return 0;
}
