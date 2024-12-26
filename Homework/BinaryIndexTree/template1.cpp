#include <iostream>
#include <vector>

using namespace std;

vector<int> bit;
// 更新树状数组，在index位置增加delta
void update(int index, int delta, int n) {
    while (index <= n) {
        bit[index] += delta;
        index += index & -index;
    }
}

// 查询树状数组前index项的和
int query(int index) {
    int sum = 0;
    while (index > 0) {
        sum += bit[index];
        index -= index & -index;
    }
    return sum;
}

// 查询区间[left, right]的和
int rangeQuery(int left, int right) {
    return query(right) - query(left - 1);
}

int main() {
    int n, m;
    cin >> n >> m; // 输入数列长度n和操作次数m
    vector<int> arr(n + 1);
    bit.resize(n + 1, 0);

    // 初始化树状数组
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        update(i, arr[i], n);
    }

    // 处理操作
    for (int i = 0; i < m; ++i) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            // 将第x个位置增加y
            update(x, y, n);
        } else if (op == 2) {
            // 查询区间[x, y]的和
            cout << rangeQuery(x, y) << endl;
        }
    }

    return 0;
}
