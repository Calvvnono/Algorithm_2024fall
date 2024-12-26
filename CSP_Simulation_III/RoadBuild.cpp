#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

// 存储路径及其长度
void findPath(int start, int end, vector<vector<pair<int, ll>>>& graph, 
              vector<bool>& visited, ll currentLength,
              ll& pathLength, bool& found) {
    if (start == end) {
        pathLength = currentLength;
        found = true;
        return;
    }
    
    visited[start] = true;
    for (auto& next : graph[start]) {
        int v = next.first;
        ll len = next.second;
        if (!visited[v]) {
            findPath(v, end, graph, visited, currentLength + len, pathLength, found);
            if (found) return;
        }
    }
    visited[start] = false;
}

int main() {
    int n;
    while (cin >> n) {
        // 构建图
        vector<vector<pair<int, ll>>> graph(n);
        for (int i = 0; i < n-1; i++) {
            int u, v;
            ll c;
            cin >> u >> v >> c;
            graph[u].push_back({v, c});
            graph[v].push_back({u, c});
        }
        
        // 统计三类路径长度和
        ll sum0 = 0, sum1 = 0, sum2 = 0;
        
        // 枚举所有城市对
        for (int s = 0; s < n; s++) {
            for (int t = 0; t < n; t++) {
                if (s == t) continue;
                
                // 寻找从s到t的路径
                vector<bool> visited(n, false);
                ll pathLength = 0;
                bool found = false;
                findPath(s, t, graph, visited, 0, pathLength, found);
                
                // 根据路径长度模3的结果累加
                if (found) {
                    pathLength %= MOD;
                    if (pathLength % 3 == 0) sum0 = (sum0 + pathLength) % MOD;
                    else if (pathLength % 3 == 1) sum1 = (sum1 + pathLength) % MOD;
                    else sum2 = (sum2 + pathLength) % MOD;
                }
            }
        }
        
        cout << sum0 << " " << sum1 << " " << sum2 << endl;
    }
    return 0;
}
