#include <iostream>
#include <string>
using namespace std;

/**
 * 问题分析：
 * - 我们有一个由 'N' 和 'F' 组成的字符串，表示灯的开关状态。
 * - 我们可以最多翻转 k 次，每次翻转可以改变一个灯的状态。
 * - 定义不优美度为字符串中最长的连续相同字符的长度（无论是 'N' 还是 'F'）。
 * - 目标是在最多翻转 k 次的情况下，最小化不优美度。
 *
 * 解题思路：
 * - 我们可以对可能的最大连续相同字符的长度（不优美度）进行二分搜索，寻找最小的可行值。
 * - 对于每个猜测的最大长度 L，计算需要多少次翻转可以使得所有的连续相同字符的长度不超过 L。
 * - 计算方法是遍历字符串，对于每个连续相同字符的段，如果长度超过 L，则需要翻转一些字符来打断这个段。
 *   - 对于长度为 R 的段，需要的翻转次数为： (R + L - 1) / L - 1
 *   - 为什么？ 分成一个个小段，R / L的向上取整的公式
 * - 如果总的翻转次数不超过 k，则说明这个 L 是可行的，我们尝试更小的 L。
 * - 否则，尝试更大的 L。
 *
 * 实现细节：
 * - 使用二分搜索来找到最小的可行的不优美度 L。
 * - 时间复杂度为 O(n log n)，其中 n 是字符串的长度。
 */

int n, k;
string s;

// 计算对于给定的最大段长度 L，需要的最小翻转次数
int total_flips(int L) {
    int total_flips = 0;
    int i = 0;
    while (i < n) {
        char curr_char = s[i];
        int run_length = 0;
        // 计算当前连续相同字符的段的长度
        while (i < n && s[i] == curr_char) {
            run_length++;
            i++;
        }
        // 如果段的长度超过 L，需要翻转一些字符
        if (run_length > L) {
            int flips_needed = (run_length + L - 1) / L - 1;
            total_flips += flips_needed;
        }
    }
    return total_flips;
}

int main() {
    // 输入部分
    cin >> n >> k;
    cin >> s;

    // 二分搜索不优美度的最小值
    int left = 1, right = n;
    int answer = n; // 初始化答案为最大可能值
    while (left <= right) {
        int mid = (left + right) / 2;
        int flips_needed = total_flips(mid);
        if (flips_needed <= k) {
            // 如果需要的翻转次数不超过 k，尝试更小的 L
            answer = mid;
            right = mid - 1;
        } else {
            // 否则，尝试更大的 L
            left = mid + 1;
        }
    }
    cout << answer << endl;
    return 0;
}
