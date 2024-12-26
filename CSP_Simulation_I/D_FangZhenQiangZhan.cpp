#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

/**
 * 问题分析：
 * - 我们需要找到最小的可能的 k（每个初始弹匣中的子弹数），满足以下条件：
 *   1. k ≥ max(ai)，即 k 不小于当前弹匣中最大子弹数。
 *   2. 能够将当前的子弹数 ai[] 分成若干组，每组的子弹数之和为 k。
 *
 * 解题思路：
 * - 从 max_ai 开始到 sum_ai，依次尝试可能的 k。
 * - 对于每个可能的 k，使用 DFS 尝试将 ai[] 分成若干组，每组的子弹数之和为 k。
 * - 在 DFS 中，使用各种剪枝策略来减少搜索空间：
 *   - 如果当前的子弹数已经达到 k，则开始下一组的搜索。
 *   - 如果当前的子弹数加上下一个 ai[i] 超过了 k，则跳过。
 *   - 如果连续相同的 ai[i]，为了避免重复计算，可以跳过已经尝试过的相同值。
 *   - 如果当前子弹数为 0（新的一组），且 ai[i] 在之前的搜索中失败过，则可以提前返回失败。
 *
 * 实现步骤：
 * 1. 读取输入，计算 sum_ai 和 max_ai，并对 ai[] 进行排序（从大到小）。
 * 2. 从 max_ai 开始到 sum_ai，依次尝试可能的 k。
 *    - 如果 sum_ai % k != 0，则跳过（剪枝）。
 *    - 计算需要的组数 cnt = sum_ai / k。
 *    - 初始化 vis[] 数组（表示 ai[] 中的元素是否已被使用）。
 *    - 调用 DFS 函数，尝试分组。
 *    - 如果 DFS 成功，输出当前的 k，并结束程序。
 * 3. 如果遍历完所有 k 都未找到，输出 sum_ai（实际不会到这里）。
 */

const int MAX_N = 60;
int n;
int ai[MAX_N];
int sum_ai = 0;
int max_ai = 0;
bool vis[MAX_N];
int cnt; // 需要的组数
int k;   // 当前尝试的每组子弹数（即 k）
bool fail[MAX_N]; // 剪枝：记录在某些情况下失败的位置，避免重复搜索

bool dfs(int group_num, int curr_sum, int start_index) {
    if (group_num > cnt) {
        // 所有组都成功组装完毕
        return true;
    }
    if (curr_sum == k) {
        // 当前组已达到目标，开始下一组
        return dfs(group_num + 1, 0, 0);
    }
    int prev = -1;
    for (int i = start_index; i < n; ++i) {
        if (!vis[i] && curr_sum + ai[i] <= k && prev != ai[i]) {
            vis[i] = true;
            if (dfs(group_num, curr_sum + ai[i], i + 1)) {
                return true;
            }
            vis[i] = false;
            prev = ai[i];
            // 剪枝条件
            if (curr_sum == 0 || curr_sum + ai[i] == k) {
                return false;
            }
        }
    }
    return false;
}

int main() {
    // 输入部分
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> ai[i];
        sum_ai += ai[i];
        if (ai[i] > max_ai) {
            max_ai = ai[i];
        }
    }

    // 对 ai[] 进行排序（从大到小）
    sort(ai, ai + n, greater<int>());

    // 尝试从 max_ai 开始到 sum_ai 的可能的 k
    for (k = max_ai; k <= sum_ai; ++k) {
        if (sum_ai % k != 0) {
            continue; // 总子弹数不能被 k 整除，剪枝
        }
        cnt = sum_ai / k; // 需要的组数
        memset(vis, 0, sizeof(vis));
        if (dfs(1, 0, 0)) {
            cout << k << endl;
            return 0;
        }
    }

    // 如果未找到，输出 sum_ai（实际不会到这里）
    cout << sum_ai << endl;
    return 0;
}
