/**
 * 题解思路：
 * 1. 将初始棋盘和目标棋盘分别转换为string表示，以便于状态的比较和存储。
 * 2. 使用广度优先搜索（BFS）算法，从初始棋盘状态开始，逐层扩展相邻状态，直到找到目标棋盘状态。
 * 3. 在BFS过程中，使用队列存储当前状态和步数，并使用哈希集合记录已访问的状态，避免重复搜索。
 * 4. 每次扩展时，尝试交换相邻的棋子生成新状态，如果新状态未被访问过，则将其加入队列和哈希集合。
 * 5. 当队列中出现目标棋盘状态时，返回当前步数，即为最少的移动步数。
 * 6. 如果搜索完所有可能状态仍未找到目标棋盘状态，则返回-1表示无解。
 */

#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

string boardToString(int board[4][4]) {
    string s;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            s += board[i][j] + '0';
    return s;
}

int bfs(string start, string goal) {
    queue<pair<string, int>> q;
    unordered_set<string> visited;
    q.push({ start, 0 });
    visited.insert(start);
    while (!q.empty()) {
        auto [state, step] = q.front();
        q.pop();
        if (state == goal) return step;
        for (int i = 0; i < 16; ++i) {
            int x = i / 4, y = i % 4;
            for (int k = 0; k < 4; ++k) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4) {
                    string next_state = state;
                    swap(next_state[x * 4 + y], next_state[nx * 4 + ny]);
                    if (!visited.count(next_state)) {
                        visited.insert(next_state);
                        q.push({ next_state, step + 1 });
                    }
                }
            }
        }
    }
    return -1; // 无解
}

int main() {
    int board[4][4], target[4][4];
    string start, goal;
    // 读取初始棋盘
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            scanf("%1d", &board[i][j]);
    // 忽略空行
    getchar();
    // 读取目标棋盘
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            scanf("%1d", &target[i][j]);
    start = boardToString(board);
    goal = boardToString(target);
    int result = bfs(start, goal);
    cout << result << endl;
    return 0;
}
