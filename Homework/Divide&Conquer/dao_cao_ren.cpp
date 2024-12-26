#include<iostream>
#include<algorithm>
using namespace std;

const int N = 200005;

/**
思路分析：
1. 题目要求统计在二维平面上，满足左下角和右上角有稻草人，且矩形内部没有稻草人的矩形数量。
   这是一个二维平面上的组合问题，可以通过分治法来高效地解决。
   
2. 分治法：
   - 首先按 x 坐标对稻草人的位置进行排序。
   - 然后将稻草人分为左右两部分，递归处理每一部分，在合并时寻找符合条件的矩形。
   - 对于右边部分的每一个稻草人点，检查左边部分的点，确保符合条件的矩形。

3. 核心思路：
   - 通过双栈结构维护左右两部分的稻草人点。
   - 栈1用于维护右边区域，栈2用于维护左边区域。
   - 在递归的合并过程中，利用二分查找来找到满足条件的矩形。
   - 最终的时间复杂度接近 O(n log^2 n)，适合较大规模的数据。

4. 步骤：
   - 先对稻草人的坐标进行按 x 排序。
   - 分治处理左右两部分，在合并时，按 y 排序，使用栈和二分法计算符合条件的矩形数量。
   - 最后输出满足条件的矩形总数。
*/


struct Point {
    int x, y;
} points[N];  // 存储稻草人的坐标

int n;
int stack1[N], top1;  // 用于右半部分点的栈
int stack2[N], top2;  // 用于左半部分点的栈
long long ans = 0;    // 记录满足条件的矩形数量

// 按 y 坐标排序
bool compareY(Point a, Point b) {
    return a.y < b.y;
}

// 按 x 坐标排序
bool compareX(Point a, Point b) {
    return a.x < b.x;
}

// 分治法求解
void solve(int left, int right) {
    if (left == right) return;  // 递归终止条件

    int mid = (left + right) / 2;
    top1 = top2 = 0;  // 栈顶初始化

    // 按 y 坐标排序
    sort(points + left, points + right + 1, compareY);
    // 分别对左右两部分按 x 坐标排序
    sort(points + left, points + mid + 1, compareX);
    sort(points + mid + 1, points + right + 1, compareX);

    int j = left;
    for (int i = mid + 1; i <= right; i++) {
        // 处理右边部分的栈
        while (top1 && points[stack1[top1]].y >= points[i].y) top1--;
        stack1[++top1] = i;  // 将当前点加入栈1

        // 处理左边部分
        while (j <= mid && points[j].x < points[i].x) {
            while (top2 && points[stack2[top2]].y <= points[j].y) top2--;
            stack2[++top2] = j;  // 将当前点加入栈2
            j++;
        }

        // 二分查找左边区域中符合条件的点
        int st = points[stack1[top1 - 1]].x;
        int le = 1, ri = top2, ansIndex = -1;
        while (le <= ri) {
            int mid = (le + ri) / 2;
            if (points[stack2[mid]].x > st) {
                ansIndex = mid;
                ri = mid - 1;
            } else {
                le = mid + 1;
            }
        }

        // 如果找到符合条件的点，计算符合条件的矩形数量
        if (ansIndex != -1) {
            ans += top2 - ansIndex + 1;
        }
    }

    // 递归处理左右两部分
    solve(left, mid);
    solve(mid + 1, right);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    solve(1, n);
    cout << ans << endl;
    return 0;
}
