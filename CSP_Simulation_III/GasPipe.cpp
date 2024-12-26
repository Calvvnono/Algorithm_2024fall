#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

// 使用DFS找到两点间的路径
void findPath(int start, int end, vector<vector<int>>& graph, 
              vector<bool>& visited, vector<int>& path, 
              vector<int>& finalPath, bool& found) {
    path.push_back(start);
    if (start == end) {
        finalPath = path;
        found = true;
        return;
    }
    
    visited[start] = true;
    for (int next : graph[start]) {
        if (!visited[next] && !found) {
            findPath(next, end, graph, visited, path, finalPath, found);
        }
    }
    path.pop_back();
}

// 计算给定路径的最小花费
ll calculateMinCost(vector<int>& path, string& heights, ll c, ll w) {
    int len = path.size();
    ll minCost = 0;
    
    // 对路径上的每个位置决定管道高度
    vector<int> pipeHeight(len);
    for (int i = 0; i < len; i++) {
        // 如果城市高度是1，管道必须是2
        if (heights[path[i] - 1] == '1') {
            pipeHeight[i] = 2;
        } else {
            // 如果城市高度是0，选择最小可能的高度
            // 为简单起见，我们总是选择高度1（因为这样一定能得到最小花费）
            pipeHeight[i] = 1;
        }
    }
    
    // 计算管道花费
    for (int i = 0; i < len - 1; i++) {
        // 管道高度取决于两端点的较大值
        int height = max(pipeHeight[i], pipeHeight[i + 1]);
        minCost += height * c;
    }
    
    // 计算支柱花费（除首尾外的每个位置都需要两个支柱）
    minCost += pipeHeight[0] * w;  // 起点支柱
    for (int i = 1; i < len - 1; i++) {
        minCost += 2 * pipeHeight[i] * w;  // 中间点的两个支柱
    }
    minCost += pipeHeight[len - 1] * w;  // 终点支柱
    
    return minCost;
}

int main() {
    int n, q, testnum;
    cin >> n >> q >> testnum;
    
    ll c, w;
    cin >> c >> w;
    
    string heights;
    cin >> heights;
    
    // 构建图
    vector<vector<int>> graph(n + 1);  // 1-based indexing
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    // 处理查询
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        
        // 找路径
        vector<bool> visited(n + 1, false);
        vector<int> path, finalPath;
        bool found = false;
        findPath(a, b, graph, visited, path, finalPath, found);
        
        // 计算最小花费
        ll result = calculateMinCost(finalPath, heights, c, w);
        cout << result << endl;
    }
    
    return 0;
}
