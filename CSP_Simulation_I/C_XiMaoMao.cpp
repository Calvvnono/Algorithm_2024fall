#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5005;
int n;
ll T;
ll t[N], p[N];
ll sum_t[N], sum_p[N];
ll dp[N][N];


/**
 * 问题分析：
 * - 我们需要将 n 只猫按照顺序分组，每组猫一起烘干。目标是最小化所有猫的不满度之和。
 * - 不满度计算方式是：每只猫的完成时间（洗完并烘干）乘以其不满度系数 pi。
 *
 * 解题思路：
 * - 定义 dp[i][j] 表示前 i 只猫分成 j 组时的最小不满度总和。
 * - 状态转移方程：
 *   dp[i][j] = min(dp[k][j - 1] + (sum_t[i] + T * j) * (sum_p[i] - sum_p[k]))，其中 k 从 j - 1 到 i - 1。
 * - 其中，sum_t[i] 是前 i 只猫的洗涤时间总和，sum_p[i] 是前 i 只猫的不满度系数总和。
 * - (sum_t[i] + T * j) 表示第 j 组完成的时间，(sum_p[i] - sum_p[k]) 是第 j 组的总不满度系数。
 * - dp[0][0] = 0，表示前 0 只猫分成 0 组时的不满度为 0。
 *
 * 优化：
 * - 由于 dp[i][j] 只与 dp[k][j - 1] 有关，我们可以将 dp 数组压缩为一维数组进行优化。
 * - 但是为了清晰起见，这里仍然使用二维数组。
 *
 * 注意：
 * - 初始化 dp 数组时，要确保初始值足够大。
 * - 可以使用一个较大的数，例如 1e18。
 */

int main() {
    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> p[i];
        sum_t[i] = sum_t[i - 1] + t[i];
        sum_p[i] = sum_p[i - 1] + p[i];
    }

    // 初始化 dp 数组
    ll INF = 1e18;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = INF;
    dp[0][0] = 0;

    // 动态规划求解
    for (int i = 1; i <= n; i++) {
        // 组数不能超过 i
        for (int j = 1; j <= i; j++) {
            // 尝试将第 k+1 到第 i 只猫作为第 j 组
            for (int k = j - 1; k <= i - 1; k++) {
                ll total_time = sum_t[i] + T * j;              // 当前总完成时间
                ll group_p = sum_p[i] - sum_p[k];              // 当前组的不满度系数之和
                ll cost = dp[k][j - 1] + total_time * group_p; // 总不满度

                if (dp[k][j - 1] != INF && cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    // 找到最小的不满度总和
    ll ans = INF;
    for (int j = 1; j <= n; j++) {
        if (dp[n][j] < ans) {
            ans = dp[n][j];
        }
    }

    // 输出结果
    cout << ans << endl;

    return 0;
}

/* 全过版本 分治优化，减少每次转移时对 k 的遍历。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5005;
int n;
ll T;
ll t[N], p[N];
ll sum_t[N], sum_p[N];
ll dp[N][N];

// 计算代价函数
ll calc_cost(int k, int i, int j) {
    return dp[k][j - 1] + (sum_t[i] + T * j) * (sum_p[i] - sum_p[k]);
}

// 分治优化的递归函数
void divide_conquer(int j, int l, int r, int optl, int optr) {
    if (l > r) return;
    
    int mid = (l + r) / 2;
    int best_k = -1;
    dp[mid][j] = LLONG_MAX;

    for (int k = optl; k <= min(mid - 1, optr); k++) {
        ll cost = calc_cost(k, mid, j);
        if (cost < dp[mid][j]) {
            dp[mid][j] = cost;
            best_k = k;
        }
    }

    // 递归求解左右区间
    divide_conquer(j, l, mid - 1, optl, best_k);
    divide_conquer(j, mid + 1, r, best_k, optr);
}

int main() {
    cin >> n >> T;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> p[i];
        sum_t[i] = sum_t[i - 1] + t[i];
        sum_p[i] = sum_p[i - 1] + p[i];
    }

    // 初始化 dp 数组
    ll INF = 1e18;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = INF;
    dp[0][0] = 0;

    // 使用分治优化来计算 dp 数组
    for (int j = 1; j <= n; j++) {
        divide_conquer(j, 1, n, 0, n - 1);
    }

    // 找到最小的不满度总和
    ll ans = INF;
    for (int j = 1; j <= n; j++) {
        if (dp[n][j] < ans) {
            ans = dp[n][j];
        }
    }

    // 输出结果
    cout << ans << endl;

    return 0;
}
 */