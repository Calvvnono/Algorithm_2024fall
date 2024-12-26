/*
整体思路：
这道题要求最少在 x 轴上的整点处部署若干个扫地机器人，收集平面上 n 个散落的拼图块。每个机器人可以覆盖以其部署点为圆心，半径为 r 的圆内的所有拼图块。

解决方案：
1. **转换为区间覆盖问题**：对于每个拼图块，计算其在 x 轴上的可覆盖区间（左端点和右端点）。
2. **排序**：将所有的区间按照右端点从小到大排序。
3. **贪心算法**：依次遍历排序后的区间，选择右端点最小且未被覆盖的区间，在其右端点处部署机器人。
4. **更新**：每次部署机器人后，更新已覆盖的最远位置，重复上述步骤，直到所有的拼图块都被覆盖。

关键点在于将二维平面上的覆盖问题转换为一维的区间覆盖问题，然后利用贪心策略求解最小覆盖数。
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Interval {
    int left, right; // 定义区间的左端点和右端点
};

int n;
long double r;
Interval intervals[200005];

int main() {
    cin >> n >> r; // 输入拼图块数量和机器人性能参数
    for (int i = 0; i < n; ++i) {
        int xi, yi;
        cin >> xi >> yi; // 输入每个拼图块的坐标
        long double D = r * r - (long double)yi * yi; // 计算在给定 y 坐标下，x 方向上的最大偏移量平方
        long double dx = sqrt(D); // 计算 x 方向上的最大偏移量
        int left = ceil(xi - dx - 1e-8);   // 计算能覆盖拼图块的左边界，减小精度误差
        int right = floor(xi + dx + 1e-8); // 计算能覆盖拼图块��右边界，减小精度误差
        intervals[i] = {left, right}; // 存储每个拼图块对应的 x 轴区间
    }
    // 按照区间的右端点从小到大排序，便于后续的贪心选择
    sort(intervals, intervals + n, [](Interval a, Interval b) {
        return a.right < b.right;
    });
    int ans = 0, pos = INT_MIN;
    for (int i = 0; i < n; ++i) {
        // 如果当前拼图块的左端点在上一个选择的位置右侧，说明需要新增一个机器人
        if (intervals[i].left > pos) {
            pos = intervals[i].right; // 更新当前位置为当前区间的右端点
            ans++; // 机器人数量加一
        }
    }
    cout << ans << endl; // 输出最少需要的机器人数量
    return 0;
}
