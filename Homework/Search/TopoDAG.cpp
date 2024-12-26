#include <bits/stdc++.h>
using namespace std;

int main(){
    // 读取节点数n和边数m
    int n, m;
    cin >> n >> m;
    
    // 建立邻接表adj和记录每个节点入度的数组in_degree
    vector<vector<int>> adj(n+1);
    vector<int> in_degree(n+1, 0);
    
    // 读取每条边并更新邻接表和入度
    for(int i=0; i<m; ++i){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        in_degree[y]++;
    }
    
    // 初始化队列，将所有入度为0的节点入队
    queue<int> q;
    for(int i=1; i<=n; ++i){
        if(in_degree[i]==0) q.push(i);
    }
    
    // 存储拓扑排序结果的向量
    vector<int> topo;
    
    // 进行拓扑排序
    while(!q.empty()){
        int u = q.front(); q.pop();
        topo.push_back(u);
        // 遍历u的所有邻接节点，减少它们的入度
        for(auto &v : adj[u]){
            in_degree[v]--;
            if(in_degree[v]==0) q.push(v);
        }
    }
    
    // 如果拓扑排序结果包含所有节点，则输出序列
    if(topo.size() == n){
        for(int i=0; i<n; ++i){
            cout << topo[i] << (i<n-1 ? " " : "\n");
        }
    }
    else{
        // 否则，输出-1表示不存在拓扑序列
        cout << "-1\n";
    }
}
