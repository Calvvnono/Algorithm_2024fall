#include <iostream>
#include <vector>
#include <set>
using namespace std;

/**
 * 问题描述：
 * - 给定一棵树（n 个节点，n-1 条边），有 q 个询问，每个询问包含三个节点 (ai, bi, ci)。
 * - 小 N 从 ai 到 bi 的路径上，每个节点都拍了照。
 * - 小 S 从 ci 到 bi。
 * - 问小 S 的路径上，有多少个节点是小 N 拍过照的，即两条路径的公共节点数。

 * 解题思路：
 * - 对于每个询问，找到从 ai 到 bi 的路径，记录路径上的节点。
 * - 找到从 ci 到 bi 的路径，记录路径上的节点。
 * - 计算两条路径的公共节点数量。

 * 注意：
 * - 该算法的时间复杂度为 O(q * n)，在数据规模较大时可能无法通过时间限制。
 * - 但是为了验证算法的正确性，可以先实现最基础的版本。
 */

const int MAXN = 200005;
vector<int> tree[MAXN];
bool visited[MAXN];
vector<int> path_a_b, path_c_b;
bool found;

/* 寻找从 start 到 end 的路径，存储在 path 中 */
void find_path(int current, int end, vector<int>& path) {
    visited[current] = true;
    path.push_back(current);
    if (current == end) {
        found = true;
        return;
    }
    for (int neighbor : tree[current]) {
        if (!visited[neighbor]) {
            find_path(neighbor, end, path);
            if (found) return;
        }
    }
    path.pop_back();
}

int main() {
    int n, q, testnum;
    scanf("%d%d%d", &n, &q, &testnum);
    // 构建树
    for (int i = 0; i < n-1; ++i) {
        int ui, vi;
        scanf("%d%d", &ui, &vi);
        tree[ui].push_back(vi);
        tree[vi].push_back(ui);
    }

    // 处理每个询问
    for (int i = 0; i < q; ++i) {
        int ai, bi, ci;
        scanf("%d%d%d", &ai, &bi, &ci);

        // 找到从 ai 到 bi 的路径
        path_a_b.clear();
        fill(visited, visited + n + 1, false);
        found = false;
        find_path(ai, bi, path_a_b);

        // 找到从 ci 到 bi 的路径
        path_c_b.clear();
        fill(visited, visited + n + 1, false);
        found = false;
        find_path(ci, bi, path_c_b);

        // 将路径转换为集合，计算交集的大小
        set<int> set_a_b(path_a_b.begin(), path_a_b.end());
        set<int> set_c_b(path_c_b.begin(), path_c_b.end());

        // 计算交集大小
        int common_nodes = 0;
        for (int node : set_c_b) {
            if (set_a_b.count(node)) {
                ++common_nodes;
            }
        }

        printf("%d\n", common_nodes);
    }

    return 0;
}
