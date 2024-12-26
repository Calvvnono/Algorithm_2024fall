#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> Point;

/**
 * 按照“左半区”/“右半区”/“跨两区”的距离分治
 * 1. 基本情况：如果区间内的点数小于等于3，直接暴力计算两两之间的距离平方，返回最小值
 * 2. 分治法：将点集分成两部分，递归求解左右两部分的最近点对
 * 3. 合并操作：在跨越分界线的点对中查找距离平方更小的点对(剪枝：Δx或Δy小于当前最小距离平方)
 * 4. 返回最终的最小距离平方
 */

ll dist2(const Point &a, const Point &b) {
    ll dx = a.first - b.first;
    ll dy = a.second - b.second;
    return dx * dx + dy * dy;
}

ll closest_pair(vector<Point> &points, int l, int r) {
    // 基本情况：如果区间内的点数小于等于3，直接暴力计算两两之间的距离平方，返回最小值
    if (r - l <= 3) {  
        ll min_d2 = LLONG_MAX;
        for (int i = l; i < r; i++) {
            for (int j = i + 1; j < r; j++) {
                min_d2 = min(min_d2, dist2(points[i], points[j]));
            }
        }
        // 对区间内的点按 y 坐标排序，方便后续合并操作
        sort(points.begin() + l, points.begin() + r, [](const Point &a, const Point &b) {
            return a.second < b.second;  // 按 y 坐标排序
        });
        return min_d2;
    }

    // 分治法：将点集分成两部分，递归求解左右两部分的最近点对
    int mid = (l + r) / 2;
    int mid_x = points[mid].first;  // 分割点的 x 坐标

    // 递归计算左右部分的最小距离平方
    ll d2_left = closest_pair(points, l, mid);
    ll d2_right = closest_pair(points, mid, r);
    ll d2 = min(d2_left, d2_right);  // 当前的最小距离平方

    // 构建跨越分界线的点的集合，只保留 x 坐标与分界线距离小于当前最小距离平方的点
    vector<Point> strip;
    for (int i = l; i < r; i++) {
        if (abs(points[i].first - mid_x) * 1LL * abs(points[i].first - mid_x) < d2) {
            strip.push_back(points[i]);
        }
    }
    // 对保留的点按照 y 坐标排序
    sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) {
        return a.second < b.second;  // 按 y 坐标排序
    });
    // 在 y 坐标接近的点对中查找距离平方更小的点对
    for (int i = 0; i < strip.size(); i++) {
        // 只比较 y 坐标差小于当前最小距离平方的点对
        for (int j = i + 1; j < strip.size() && (strip[j].second - strip[i].second) * 1LL * (strip[j].second - strip[i].second) < d2; j++) {
            d2 = min(d2, dist2(strip[i], strip[j]));
        }
    }
    // 返回最终的最小距离平方
    return d2;
}


int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) 
        cin >> points[i].first >> points[i].second;

    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        return a.first < b.first;  // 按x排序
    });

    ll result = closest_pair(points, 0, n);
    cout << result << endl;
    return 0;
}
