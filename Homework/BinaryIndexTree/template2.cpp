#include <iostream>
#include <vector>

using namespace std;

class BinaryIndexedTree {
private:
    vector<long long> bit1, bit2;
    int n;

    // 更新树状数组
    void add(vector<long long>& bit, int idx, long long val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    // 查询树状数组前idx项的和
    long long sum(const vector<long long>& bit, int idx) {
        long long ret = 0;
        while (idx > 0) {
            ret += bit[idx];
            idx -= idx & -idx;
        }
        return ret;
    }

public:
    BinaryIndexedTree(int size) : n(size) {
        bit1.resize(n + 1, 0);
        bit2.resize(n + 1, 0);
    }

    // 区间更新
    void range_add(int l, int r, long long val) {
        add(bit1, l, val);
        add(bit1, r + 1, -val);
        add(bit2, l, val * (l - 1));
        add(bit2, r + 1, -val * r);
    }

    // 查询前缀和
    long long prefix_sum(int idx) {
        return sum(bit1, idx) * idx - sum(bit2, idx);
    }

    // 单点查询
    long long point_query(int idx) {
        return prefix_sum(idx) - prefix_sum(idx - 1);
    }
};

int main() {
    int n, m;
    cin >> n >> m; // 输入数列长度n和操作次数m
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    BinaryIndexedTree bit(n);

    // 初始化树状数组
    for (int i = 1; i <= n; ++i) {
        bit.range_add(i, i, arr[i]);
    }

    // 处理操作
    for (int i = 0; i < m; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, k;
            // 将区间[x, y]的每个数增加k
            cin >> x >> y >> k;
            bit.range_add(x, y, k);
        } else if (op == 2) {
            int x;
            // 输出第x个数的值
            cin >> x;
            cout << bit.point_query(x) << endl;
        }
    }

    return 0;
}
