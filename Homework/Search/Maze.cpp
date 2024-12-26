// 本程序使用深度优先搜索（DFS）算法来解决迷宫问题。
// 题目要求在一个 n*m 大小的迷宫中，从左上角出发，恰好在第 k 步时到达右下角。
// 迷宫中 1 表示墙壁，0 表示平地。每次只能向上下左右移动一格，且不能移动到曾经经过的位置。
// 
// 解题思路：
// 1. 从起点 (0,0) 出发，使用 DFS 算法遍历迷宫。
// 2. 在 DFS 过程中，记录当前步数，如果到达终点 (n-1, m-1) 时步数恰好为 k，则输出 "Yes"。
// 3. 如果遍历完所有可能的路径都没有满足条件的，输出 "No"。
// 4. 使用 visited 数组记录已经访问过的位置，避免走回头路。
// 5. 通过递归实现 DFS，尝试向上下左右四个方向移动。

#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int maze[100][100];
bool visited[100][100];
bool flag = false;

bool dfs(int x, int y, int steps) {
    if(x == n-1 && y == m-1) {
        return steps == k;
    }
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    for(int i=0;i<4;i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >=0 && nx < n && ny >=0 && ny < m && maze[nx][ny] == 0 && !visited[nx][ny]) {
            visited[nx][ny] = true;
            if(dfs(nx, ny, steps +1)) return true;
            visited[nx][ny] = false; // 还原现场
        }
    }
    return false;
}

int main(){
    cin >> n >> m >> k;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> maze[i][j];
        }
    }
    visited[0][0] = true;
    if(dfs(0,0,0)) cout << "Yes";
    else cout << "No";
}
