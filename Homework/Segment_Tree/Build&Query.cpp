#include <iostream>
using namespace std;

const int N = 1e5 + 5;
int arr[N];

// 线段树节点 [l, r]，val存储该段的sum，left和right分别存储左右端点下标
struct Node {
    int val;
    int left, right;
} tree[4 * N];

// 建树
void build (int root, int l, int r) {
    tree[root].left = l;
    tree[root].right = r;
    if (l == r) {
        tree[root].val = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(root * 2, l, mid); // 左子树
    build(root * 2 + 1, mid + 1, r); // 右子树
    tree[root].val = tree[root * 2].val + tree[root * 2 + 1].val;
}

// 更新区间 [l, r] 内每个元素加上 x
void range_update(int root, int l, int r, int x) {
    if (tree[root].left == tree[root].right) {
        tree[root].val += x;
        return;
    }
    int mid = (tree[root].left + tree[root].right) / 2;
    if (l <= mid) range_update(root * 2, l, r, x); // 更新左子区间
    if (r > mid) range_update(root * 2 + 1, l, r, x); // 更新右子区间
    tree[root].val = tree[root * 2].val + tree[root * 2 + 1].val; // 更新父节点的和
}

// 查询区间 [l, r] 的和
int query (int root, int l, int r) {
    if (tree[root].left == l && tree[root].right == r) { //正好等于该区间
        return tree[root].val;
    }
    int mid = (tree[root].left + tree[root].right) / 2;
    if (mid >= r)
        return query(root * 2, l, r); // 在左子树查找
    else if (mid < l)
        return query(root * 2 + 1, l, r); // 在右子树查找
    else
        return query(root * 2, l, mid) + query(root * 2 + 1, mid + 1, r); // 跨区间查找
}

int main() {
    int n, m;
    cin >> n >> m;

    // 输入初始数组
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    // 建立线段树
    build(1, 1, n);

    // 处理操作
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            // 区间增加操作
            int l, r, x;
            cin >> l >> r >> x;
            range_update(1, l, r, x);
        } else if (op == 2) {
            // 查询区间和
            int l, r;
            cin >> l >> r;
            cout << query(1, l, r) << endl;
        }
    }

    return 0;
}