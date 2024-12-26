/**
 * 靶形数独题解与代码说明：
 * 
 * 题目要求完成一个 9x9 的数独填充，使得每行、每列和每个 3x3 宫格中的数字不重复，
 * 并且按照靶形分值分布来计算得分，填充后的总得分越高越好。
 * 
 * ### 解题思路：
 * 1. **数据结构与初始化**：使用 2D 数组 `a` 记录初始数独状态，`rec` 记录最终填充状态，
 *    `score` 表示每个格子的分值，`fr`、`fc`、`f` 分别表示行、列和 3x3 宫格的数字使用情况。
 * 2. **分值打表**：根据题目给定的靶形区域，每个格子的分值已在 `score` 中预定义。
 * 3. **数独分区 ID**：`getid` 函数用于计算某个格子属于哪个 3x3 宫格。
 * 4. **深度优先搜索（DFS）**：`dfs` 函数用于遍历每个格子，并根据分值分布和数独规则尝试填入数字。
 *    若填满数独，则计算当前得分，并更新最大得分 `ans`。
 * 5. **主函数流程**：从输入读取数独初始状态，记录空格数量以决定搜索顺序，调用 DFS 开始搜索，
 *    输出最高得分，如果无解则输出 -1。
 * 
 * ### 复杂度分析：
 * 该算法利用 DFS 进行暴力搜索，结合提前排好的搜索顺序表，以减少搜索次数。
 */

#include <bits/stdc++.h>
using namespace std;

int a[10][10], rec[10][10], ans, head, nex[10];
bool fr[10][10], fc[10][10], f[10][10];

// 靶形分值打表
int score[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 9, 10, 9, 8, 7, 6},
    {0, 6, 7, 8, 9, 9, 9, 8, 7, 6},
    {0, 6, 7, 8, 8, 8, 8, 8, 7, 6},
    {0, 6, 7, 7, 7, 7, 7, 7, 7, 6},
    {0, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};

struct node {
    int id, cnt; // id: 行号, cnt: 行中空格数量
} n[10];

// 排序函数，按照空格数量升序排列
bool cmp(node x, node y) {
    return x.cnt < y.cnt;
}

// 获取格子 (i, j) 所在的 3x3 小宫格 ID
int getid(int i, int j) {
    if (i <= 3) {
        if (j <= 3) return 1;
        else if (j >= 7) return 3;
        else return 2;
    } else if (i >= 7) {
        if (j <= 3) return 7;
        else if (j >= 7) return 9;
        else return 8;
    } else {
        if (j <= 3) return 4;
        else if (j >= 7) return 6;
        else return 5;
    }
}

// 深度优先搜索填充数独
void dfs(int x, int y) {
    if (x == 0) { // 如果数独填充完毕，计算当前得分
        int res = 0;
        for (int i = 1; i <= 9; i++)
            for (int j = 1; j <= 9; j++)
                res += rec[i][j] * score[i][j];
        ans = max(ans, res); // 更新最大得分
        return;
    }

    if (a[x][y]) { // 当前格子已填充，继续下一个格子
        rec[x][y] = a[x][y];
        if (y == 9) dfs(nex[x], 1);
        else dfs(x, y + 1);
    } else { // 尝试填充当前空格
        for (int i = 1; i <= 9; i++) {
            if (!fr[x][i] && !fc[y][i] && !f[getid(x, y)][i]) {
                fr[x][i] = 1; fc[y][i] = 1; f[getid(x, y)][i] = 1;
                rec[x][y] = i;
                if (y == 9) dfs(nex[x], 1);
                else dfs(x, y + 1);
                fr[x][i] = 0; fc[y][i] = 0; f[getid(x, y)][i] = 0;
            }
        }
    }
}

int main() {
    for (int i = 1; i <= 9; i++) n[i].id = i;
    // 初始化数据，记录每行空格数，并更新已填数字的标记
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            scanf("%d", &a[i][j]);
            n[i].cnt += (a[i][j] == 0);
            fr[i][a[i][j]] = 1;
            fc[j][a[i][j]] = 1;
            f[getid(i, j)][a[i][j]] = 1;
        }
    }
    // 根据空格数量排序行，确定搜索顺序
    sort(n + 1, n + 10, cmp);
    head = n[1].id;
    for (int i = 1; i < 9; i++) nex[n[i].id] = n[i + 1].id;
    // 开始 DFS 填充数独
    dfs(head, 1);
    // 输出结果
    if (ans == 0) printf("-1\n"); // 无解情况
    else printf("%d\n", ans);
    return 0;
}
