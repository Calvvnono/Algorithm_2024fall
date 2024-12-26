#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

/**
 * 问题分析：
 * - 有 n 个小朋友坐成一圈，每人有 ai 颗糖果。
 * - 每人只能给左右两人传递糖果，每次传递一颗糖果的代价为 1。
 * - 目标是使所有人最终拥有相同数量的糖果，求最小总代价。
 * 
 * 解题思路：
 * 
 * 1. **假设所有传递都向左进行：**
 *    - 为了便于计算，我们假设所有的糖果传递都是向左的，向右的传递可以视为向左传递的负数。
 *    - 定义 Ki 为第 i 个小朋友向左传递的糖果数量（可以为负数）。
 * 
 * 2. **建立糖果数量和传递数量的关系：**
 *    - 对于第 i 个小朋友，最终的糖果数量为：
 *      \( \text{最终糖果数} = ai - Ki + K_{i+1} \)。
 *    - 因为是一个环，所以 \( K_{n+1} = K_1 \)。
 * 
 * 3. **使所有小朋友的糖果数相等：**
 *    - 为了使所有人的糖果数相等，设为 avg，则有：
 *      \( ai - Ki + K_{i+1} = {avg} \)。
 *    - 根据上述公式，对所有 i，建立方程。
 * 
 * 4. **推导传递数量的关系：**
 *    - 从方程 \( ai - Ki + K_{i+1} = {avg} \)，可得：
 *      \( K_{i+1} - K_i = ai - {avg} \)。
 *    - 令 \( C_i = ai - {avg} \)，表示第 i 个小朋友的糖果数与平均值的差值。
 *    - 于是有 \( K_{i+1} - K_i = C_i \)
 *    - 也就有：Ki = K0 + ΣCi。 其中 K0 是一个可以任取的初值（平移量）。
 * 
 * 5. **计算最小总代价：**
 *    - 传递的总代价为所有 Σ|K_i|，我们希望取合适的 K0，使得这个总和尽可能小。
 *    - 为了使总代价最小，需要找到一个值 mid（平移），使得 \( \sum_{i=1}^{n} |K_i - mid| \) 最小。
 *    - 这个 mid 即为 \( K_i \) 的中位数。从实际意义上，K0的任取是由于环形循环传递的特性。
 * 
 * **时间复杂度：**
 * - O(n log n)，主要耗费在对 \( K_i \) 数组的排序上。
 */

int main() {
    int n;
    scanf("%d", &n);

    vector<ll> ai(n + 1);
    ll total = 0;

    // 读取糖果数量，计算总和
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &ai[i]);
        total += ai[i];
    }

    ll avg = total / n; // 计算平均值，使用整数除法

    vector<ll> Ci(n + 1);
    vector<ll> Ki(n + 1);
    Ki[0] = 0;

    // 计算差值数组 Ci 和前缀和数组 Ki
    for (int i = 1; i <= n; ++i) {
        Ci[i] = ai[i] - avg;          // 每个人与平均值的差值
        Ki[i] = Ki[i - 1] + Ci[i];    // 计算 Ki
    }

    // 去掉 Ki[0]，因为我们从 Ki[1] 开始
    vector<ll> K_sub(Ki.begin() + 1, Ki.end());

    // 对 Ki 进行排序，找到中位数 mid
    sort(K_sub.begin(), K_sub.end());
    ll mid = K_sub[n / 2]; // 中位数

    ll ans = 0;
    // 计算 ans = ∑|Ki - mid|
    for (int i = 1; i <= n; ++i) {
        ans += abs(Ki[i] - mid);
    }

    // 输出结果
    printf("%lld\n", ans);

    return 0;
}
