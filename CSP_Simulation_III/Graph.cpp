#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100005;  // 城市中地点的最大数量

vector<int> adj[MAXN];     // 邻接表
bool visited[MAXN];        // 访问标记
int dist[MAXN];            // 从s点到每个节点的距离
int n, s, k;               // n: 城市地点数, s: 售卖机初始位置, k: 售卖机覆盖的最大距离

// BFS，计算从初始售卖机到每个地点的距离
void bfs(int start) {
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q; // 存储节点编号及其距离
    q.push({start, 0});
    visited[start] = true;
    dist[start] = 0;

    while (!q.empty()) {
        int node = q.front().first;
        int d = q.front().second;
        q.pop();

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dist[neighbor] = d + 1;
                q.push({neighbor, d + 1});
            }
        }
    }
}

// 主函数
int main() {
    cin >> n >> s >> k;
    s--;  // 将 s 转换为 0-based index

    // 构建图
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;  // 转换为 0-based index
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 使用 BFS 找到从 s 点出发到各个节点的距离
    bfs(s);

    // 寻找叶子节点（度为1的节点）并记录其距离
    vector<int> leaves;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1 && i != s) {  // 叶子节点
            leaves.push_back(i);
        }
    }

    // 按照离 s 点的距离从远到近排序叶子节点
    sort(leaves.begin(), leaves.end(), [](int a, int b) {
        return dist[a] > dist[b];  // 从远到近排序
    });

    // 增加售卖机的最小数量
    int added = 0;
    bool covered[MAXN] = {false};  // 标记节点是否已经被覆盖

    // 对每个叶子节点进行处理
    for (int leaf : leaves) {
        if (!covered[leaf]) {  // 如果当前叶子节点没有被覆盖
            // 从该叶子节点向外扩展，直到最大距离 k，放置一个售卖机
            added++;  // 需要增加一台售卖机
            // 将该叶子节点及其覆盖范围内的节点标记为已覆盖
            for (int i = 0; i < n; i++) {
                if (dist[i] >= dist[leaf] - k && dist[i] <= dist[leaf]) {
                    covered[i] = true;
                }
            }
        }
    }

    // 输出结果
    cout << added << endl;

    return 0;
}
