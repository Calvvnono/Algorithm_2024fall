#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
long long tree[maxn << 2], lazy[maxn << 2], lazy_[maxn << 2], x[maxn]; // 线段树和懒标记数组
int n, m, mod, order, add;
vector<long long> ans;

// 建树函数：构建线段树
void build(int rt, int l, int r) {
    lazy_[rt] = 1;  // 初始化乘法懒标记为 1，因为乘法的单位是 1
    if (l == r) {
        tree[rt] = x[l] % mod;  // 叶子节点直接赋值
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);        // 递归构建左子树
    build(rt << 1 | 1, mid + 1, r); // 递归构建右子树
    tree[rt] = (tree[rt << 1] + tree[rt << 1 | 1]) % mod;  // 合并左右子树的和
}

// 更新当前节点的懒标记并更新值
void update(int rt, int l, int r, long long w, long long cheng) {
    lazy_[rt] = (lazy_[rt] * cheng) % mod;  // 懒标记乘法
    lazy[rt] = (lazy[rt] * cheng) % mod;    // 先处理乘法，再处理加法
    lazy[rt] = (lazy[rt] + w) % mod;        // 懒标记加法
    tree[rt] = (tree[rt] * cheng + (r - l + 1) * w) % mod;  // 更新当前节点的值
}

// 下推懒标记：将当前节点的懒标记传递给子节点
void pushdown(int rt, int l, int r) {
    int mid = (l + r) >> 1;
    update(rt << 1, l, mid, lazy[rt], lazy_[rt]);        // 传递懒标记给左子树
    update(rt << 1 | 1, mid + 1, r, lazy[rt], lazy_[rt]); // 传递懒标记给右子树
    lazy[rt] = 0;    // 清空当前节点的加法懒标记
    lazy_[rt] = 1;   // 清空当前节点的乘法懒标记
}

// 区间修改函数：根据 w 和 cheng 的值，分别处理加法和乘法的更新
void modify(int rt, int l, int r, int s, int t, long long w, long long cheng) {
    if (l >= s && r <= t) {
        update(rt, l, r, w, cheng);  // 在目标区间内，直接更新
        return;
    }
    pushdown(rt, l, r);  // 懒标记下推
    int mid = (l + r) >> 1;
    if (mid >= s) modify(rt << 1, l, mid, s, t, w, cheng);      // 左子树递归更新
    if (mid < t) modify(rt << 1 | 1, mid + 1, r, s, t, w, cheng); // 右子树递归更新
    tree[rt] = (tree[rt << 1] + tree[rt << 1 | 1]) % mod;  // 更新父节点的值
}

// 区间查询函数：查询区间 [s, t] 内的和
long long query(int rt, int l, int r, int s, int t) {
    if (l >= s && r <= t) {
        return tree[rt] % mod;  // 如果区间完全匹配，直接返回
    }
    pushdown(rt, l, r);  // 先下推懒标记，确保区间内的值正确
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (mid >= s) ans = (ans + query(rt << 1, l, mid, s, t)) % mod;  // 左子树查询
    if (mid < t) ans = (ans + query(rt << 1 | 1, mid + 1, r, s, t)) % mod;  // 右子树查询
    return ans % mod;
}

// 主函数：解决问题的函数
void solve() {
    int a, b, add;
    scanf("%d%d%d", &n, &m, &mod);  // 读取 n, m 和 mod
    for (int i = 1; i <= n; i++) scanf("%lld", &x[i]);  // 读取数组初始值
    build(1, 1, n);  // 构建线段树
    for (int i = 1; i <= m; i++) {
        scanf("%d", &order);  // 读取操作指令
        if (order == 2) {  // 区间加法操作
            scanf("%d%d%d", &a, &b, &add);
            modify(1, 1, n, a, b, add, 1);  // 调用 modify，w=add, cheng=1
        } else if (order == 1) {  // 区间乘法操作
            scanf("%d%d%d", &a, &b, &add);
            modify(1, 1, n, a, b, 0, add);  // 调用 modify，w=0, cheng=add
        } else {  // 查询操作
            scanf("%d%d", &a, &b);
            ans.push_back(query(1, 1, n, a, b) % mod);
        }
    }
}

int main() {
    solve();  // 调用求解函数
    for(auto t: ans)    printf("%lld\n", t);  // 输出答案
    return 0;
}
