#include <bits/stdc++.h>
using namespace std;

int main () {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> nodes(n);
    // 读取节点
    for (int i = 0; i < n; ++i) {
        cin >> nodes[i].first >> nodes[i].second;
    }
    // 邻接表表示无向图
    vector<vector<pair<int, double>>> graph(n);
    for (int i = 0; i < m; ++i) {
        int xj, yj, rj, tj;
        cin >> xj >> yj >> rj >> tj;
        vector<int> coveredNodes;
        // 添加所有该区域覆盖的点
        for (int j = 0; j < n; ++j) {
            int xi = nodes[j].first, yi = nodes[j].second;
            if (abs(xi - xj) <= rj && abs(yi - yj) <= rj) {
                coveredNodes.push_back(j);
            }
        }
        // 添加所有覆盖点两两之间的边，边权为t
        for (int u = 0; u < coveredNodes.size(); ++u) {
            for (int v = u + 1; v < coveredNodes.size(); ++v) {
                int a = coveredNodes[u], b = coveredNodes[v];
                graph[a].push_back({b, (double)tj});
                graph[b].push_back({a, (double)tj});
            }
        }
    }
    vector<double> dist(n, 1e18);
    dist[0] = 0;
    // 堆优化的Dijkstra算法
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : graph[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[n - 1] == 1e18) {
        cout << "Nan" << endl;
    } else {
        cout << dist[n - 1] << endl;
    }
    return 0;
}