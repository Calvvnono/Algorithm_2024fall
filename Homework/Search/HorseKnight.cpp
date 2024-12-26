/**
 * 题目：Knight Moves
 * 
 * 题目要求编写一个程序，计算一个棋盘上的骑士从一个格子移动到另一个格子所需的最小步数。
 * 骑士的移动规则如同国际象棋中的规则，可以按照“日”字形跳到周围的八个可能位置之一。
 * 
 * ### 解题思路：
 * 1. **骑士的移动方式**：骑士可以沿“日”字形在八个不同方向上跳跃。
 * 2. **广度优先搜索（BFS）**：我们使用 BFS 来寻找最短路径。由于每一步都等价，我们可以从起点开始，将每一步到达的位置加入队列，记录访问过的格子以及到达该格子的步数。
 * 3. **边界处理**：在移动过程中，需确保骑士跳跃到的格子在棋盘的范围内。
 * 4. **终止条件**：当 BFS 找到目标位置时，记录并输出所需步数。如果起始位置与目标位置相同，则直接输出 0。
 * 
 * ### 输入输出说明：
 * - 输入包含棋盘大小、多个骑士的起点和终点坐标，输出每个骑士所需的最小步数。
 * 
 * ### 复杂度分析：
 * 使用 BFS 保证了最短路径的查找效率，复杂度为 O(L^2)（其中 L 为棋盘的一边长度）。
 */

#include <bits/stdc++.h>
using namespace std;

const int dx[8] = {2, 2, -2, -2, 1, -1, 1, -1}; // 骑士在 x 方向的移动
const int dy[8] = {1, -1, 1, -1, 2, 2, -2, -2}; // 骑士在 y 方向的移动

// BFS 函数，用于计算从 (sx, sy) 到 (ex, ey) 的最小步数
int bfs(int L, int sx, int sy, int ex, int ey) {
    if (sx == ex && sy == ey) return 0; // 如果起点就是终点，返回 0 步

    vector<vector<bool>> visited(L, vector<bool>(L, false)); // 记录访问过的格子
    queue<pair<int, int>> q; // 队列用于 BFS
    queue<int> steps; // 队列保存当前步数
    q.push({sx, sy});
    steps.push(0);
    visited[sx][sy] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        int step = steps.front();
        q.pop();
        steps.pop();

        // 尝试骑士的八个移动方向
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < L && ny >= 0 && ny < L && !visited[nx][ny]) {
                if (nx == ex && ny == ey) return step + 1; // 到达终点
                q.push({nx, ny});
                steps.push(step + 1);
                visited[nx][ny] = true;
            }
        }
    }
    return -1; // 无解情况
}

int main() {
    int n; // 骑士的数量
    cin >> n;
    while (n--) {
        int L, sx, sy, ex, ey;
        cin >> L >> sx >> sy >> ex >> ey;
        cout << bfs(L, sx, sy, ex, ey) << endl; // 输出每个骑士的最小步数
    }
    return 0;
}
