#include <iostream>
using namespace std;
typedef long long ll;

/**
 * 问题分析：40%版本
 * - 我们有 m 个魔法石，每个魔法石可以施展一个在 [Li, Ri] 区间内的魔法值。
 * - 我们需要从中选择两个不同的魔法石 i 和 j，选择对应的魔法值 x 和 y，使得 x + y = n。
 * - 方案的不同是指 i、j、x、y 中任意一个不同即视为不同方案。
 *
 * 解题思路：
 * - 使用三重循环，时间复杂度为 O(m^3)：
 *   1. 枚举第一个魔法石 i，从 1 到 m。
 *   2. 枚举第二个魔法石 j，从 1 到 m，且 j ≠ i。
 *   3. 枚举魔法值 x，从 Li 到 Ri。
 *      - 计算 y = n - x。
 *      - 如果 y 在第 j 个魔法石的施展区间 [Lj, Rj] 内，则方案数加 1。
 * - 由于魔法值的范围可能较大，需要注意程序的效率。
 *
 * 注意：
 * - 为了防止输出结果过大，最终答案需要对 998244353 取模。
 * - 由于数据规模较小（根据题目提示，此方法可获得 40% 的分数），所以可以接受 O(m^3) 的时间复杂度。
 */

const int MOD = 998244353;
const int MAX_M = 505; // 根据题目限制调整

int main() {
    int n, m;
    cin >> n >> m;
    int L[MAX_M], R[MAX_M];

    // 读取每个魔法石的施展区间
    for (int i = 0; i < m; ++i) {
        cin >> L[i] >> R[i];
    }

    ll ans = 0;

    // 枚举第一个魔法石 i
    for (int i = 0; i < m; ++i) {
        // 枚举第二个魔法石 j，确保 i ≠ j
        for (int j = 0; j < m; ++j) {
            if (i == j) continue;

            // 枚举第一个魔法石的魔法值 x
            for (int x = L[i]; x <= R[i]; ++x) {
                int y = n - x; // 计算需要的 y
                // 判断 y 是否在第 j 个魔法石的施展区间内
                if (y >= L[j] && y <= R[j]) {
                    ans = (ans + 1) % MOD;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
