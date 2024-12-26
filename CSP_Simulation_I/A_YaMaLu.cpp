#include <bits/stdc++.h>
using namespace std;

int n;
int r_bound;
int ans;
pair<int, int> segs[1000005];

/**
 * 按每个seg的右端点升序，处理过程维护一个有边界r_bound、
 * 遍历segs，只要左端点大于等于r_bound，就可以选
 * 更新r_bound为当前seg的右端点
 */

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> segs[i].first >> segs[i].second;
    }

    // 按右端点排序
    sort(segs, segs + n, [](pair<int, int> a, pair<int, int> b) {
        return a.second <= b.second;
    });

    r_bound = -1;  
    for (int i = 0; i < n; i++) {
        // 只选择左端点大于等于当前右边界的区间
        if (segs[i].first >= r_bound) {
            r_bound = segs[i].second;  // 更新右边界
            ans++;  
        }
    }
    cout << ans << endl;  
    return 0;
}
