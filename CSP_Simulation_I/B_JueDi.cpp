#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/**
    递归处理每段决堤点的水位，找到当前段的最小水位min_a，
    然后计算将该段提升至min_a所需的轮数（高度差res），
    接着处理大于min_a的连续子段，递归解决每个子段的放置问题，
    最后返回在当前段内放置沙袋的最小轮数，
    同时比较全段放置和递归处理子段的最优方案，取最小值。 
*/

// 处理 [l,r] 段的问题需要的轮次，h是当前段已经处理的高度（即之前已经放置的沙袋层数）
int solve(vector<int>& a, int l, int r, int h) {
    if (l > r) return 0;
    // 找到当前段的最小水位
    int min_a = *min_element(a.begin() + l, a.begin() + r + 1);

    // 先增加当前段补齐至最小水位所需的轮数
    int res = min_a - h;
    int i = l;
    while (i <= r) {
        // 如果当前位置的水位等于最小水位，跳过
        if (a[i] == min_a) {
            i++;
        } else {
            int j = i;
            // 找到连续的水位高于最小水位的子段
            while (j <= r && a[j] > min_a) {
                j++;
            }
            // 递归处理子段，并累加结果
            res += solve(a, i, j - 1, min_a);
            i = j;
        }
    }
    // 返回当前段放置沙袋的最小轮数（r-l+1是一个一个放的朴素方案）
    return min(res, r - l + 1);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int result = solve(a, 0, n - 1, 0);
    cout << result << endl;
    return 0;
}
