#include <iostream>
#include <vector>
#include <cmath>
#include <tuple> 
using namespace std;

// 并查集类，用于管理集合的合并与查找
class UnionFind {
public:
    // 构造函数，初始化每个元素的父节点为自己，秩为0
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 查找函数，带路径压缩优化
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并两个集合，按秩合并优化
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    vector<int> parent; // 父节点数组
    vector<int> rank;    // 秩数组，用于优化合并
};

// 判断老鼠是否能够逃脱奶酪
bool canEscape(int n, int h, int r, vector<tuple<int, int, int>>& holes) {
    UnionFind uf(n + 2); // 创建并查集，包含n个空洞和2个虚拟节点
    int bottom = n; // 虚拟底���节点索引
    int top = n + 1; // 虚拟顶部节点索引

    // 遍历每个空洞
    for (int i = 0; i < n; ++i) {
        tuple<int, int, int> hole = holes[i]; // 获取第i个空洞的坐标
        int x = get<0>(hole), y = get<1>(hole), z = get<2>(hole); // 分别获取x, y, z坐标
        if (z <= r) {
            uf.unite(i, bottom); // 如果空洞与底部表面相切或相交，合并到底部虚拟节点
        }
        if (z + r >= h) {
            uf.unite(i, top); // 如果空洞与顶部表面相切或相交，合并到顶部虚拟节点
        }
        // 检查当前空洞与其他空洞是否相交或相切
        for (int j = i + 1; j < n; ++j) {
            tuple<int, int, int> hole2 = holes[j]; // 获取第j个空洞的坐标
            int x2 = get<0>(hole2), y2 = get<1>(hole2), z2 = get<2>(hole2); // 分别获取x, y, z坐标
            long long dx = (long long)(x - x2); // x轴距离
            long long dy = (long long)(y - y2); // y轴距离
            long long dz = (long long)(z - z2); // z轴距离
            // 如果两个空洞的中心距离小于等于两个半径之和，则合并它们
            if (dx * dx + dy * dy + dz * dz <= (long long)(4) * r * r) {
                uf.unite(i, j);
            }
        }
    }

    // 如果底部虚拟节点和顶部虚拟节点在同一个连通分量中，表示可以逃脱
    return uf.find(bottom) == uf.find(top);
}

int main() {
    int T;
    cin >> T; // 输入测试用例的数量
    while (T--) {
        int n, h, r;
        cin >> n >> h >> r; // 输入空洞数量、高度和半径
        vector<tuple<int, int, int>> holes(n);
        // 输入每个空洞的坐标
        for (int i = 0; i < n; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            holes[i] = make_tuple(x, y, z);
        }
        // 判断是否可以逃脱并输出结果
        if (canEscape(n, h, r, holes)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
