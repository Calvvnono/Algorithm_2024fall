#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * 问题分析：
 * - 给定 n 个物种和 m 条能量流动关系，能量从物种 ai 流向物种 bi，形成一个有向无环图（DAG）。
 * - 我们需要计算食物链的数量，即所有从生产者（入度为 0 的节点）到消费者（出度为 0 的节点）的路径数量。
 * - 注意孤立的物种（没有任何连接的节点）不算作食物链。
 *
 * 解题思路：
 * - 使用拓扑排序和动态规划来计算从每个生产者到每个消费者的路径数量。
 * - 由于图是 DAG，可以进行拓扑排序，按照拓扑序遍历节点。
 * - 我们需要计算从生产者（入度为 0 的节点）到每个节点的路径数，并在消费者（出度为 0 的节点）处累加路径数得到最终答案。
 *
 * 具体步骤：
 * 1. 建立反向图，将所有的边反向，方便从消费者开始向生产者传播路径数量。
 * 2. 记录每个节点的入度和出度，用于判断生产者和消费者。
 * 3. 初始化队列，将入度为 0（在反向图中，即原图的出度为 0，消费者）的节点加入队列，并将其路径数量初始化为 1。
 * 4. 进行拓扑排序（BFS），在遍历过程中更新每个节点的路径数量：
 *    - 对于当前节点 u，遍历其反向邻居 v（即原图中从 v 指向 u 的边）：
 *      - 更新 dp[v] = dp[v] + dp[u]，并对取模。
 *      - 减少 in_degree[v]，如果 in_degree[v] 减少到 0，加入队列。
 *      - 如果 v 是生产者（原图中入度为 0），则将 dp[v] 累加到答案中。
 * 5. 最终答案即为所有生产者的路径数量之和。
 */

const int MAX_N = 100005;

int n, m;
vector<int> rev_adj[MAX_N]; // 反向邻接表
int in_degree[MAX_N];       // 入度
int out_degree[MAX_N];      // 出度
int dp[MAX_N];              // dp[u] 表示从节点 u 到消费者的路径数
int ans = 0;

int main() {
    cin >> n >> m;

    // 建立反向图，并记录入度和出度
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        rev_adj[b].push_back(a); // 反向边：从 b 指向 a
        in_degree[a]++;
        out_degree[b]++;
    }

    // 初始化 dp 数组和队列
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        // 入度为 0 的节点（在反向图中）即为消费者（原图中出度为 0）
        if (in_degree[i] == 0) {
            dp[i] = 1; // 消费者到消费者的路径数为 1
            q.push(i);
        }
    }

    // 拓扑排序（BFS）
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : rev_adj[u]) {
            dp[v] = (dp[v] + dp[u]);
            in_degree[v]--;
            if (in_degree[v] == 0) {
                // 如果 v 是生产者（原图中入度为 0）
                if (out_degree[v] == 0) {
                    ans = (ans + dp[v]);
                    continue;
                }
                q.push(v);
            }
        }
    }

    // 输出结果
    cout << ans << endl;

    return 0;
}
