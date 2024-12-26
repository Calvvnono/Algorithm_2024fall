#include <bits/stdc++.h>
using namespace std;

/**
 * 贪心：希望损失最少，所以按照损失高到低排序
 * 遍历任务，尽量安排卡在ddl（给后续ddl更靠前的任务留位置）
 *  - 如果不能安排在ddl，则尝试安排到截止时间之前的空闲时间
 *  - 如果ddl前没有时间可以安排，则累加扣款
 */

int main() {
    int m, n;
    cin >> m >> n;  // 输入初始奖金和游戏数量

    vector<pair<int, int>> games(n);  // 用来存储游戏的扣款与截止时间
    for (int i = 0; i < n; i++) {
        cin >> games[i].second;  // 输入游戏的截止时间
    }
    for (int i = 0; i < n; i++) {
        cin >> games[i].first;  // 输入游戏不能按时完成的扣款
    }

    // 按扣款从高到低排序
    sort(games.begin(), games.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.first > b.first;
    });

    vector<bool> used(n + 1, false);  // 标记每个时间段是否被占用
    bool arranged = false;
    int total_deduction = 0;
    for (auto game : games) {
        int w = game.first;  
        int t = game.second;   
        arranged = false;   
        // 尽量临近截止时间安排任务，如果不能安排在t时间，则尝试安排到t之前的时间
        for (int i = t; i >= 1; i--) {
            if (!used[i]) {  // 如果该时间段未被占用
                used[i] = true;  // 标记该时间段已被占用
                arranged = true;  // 标记安排任务成功
                break;  // 安排任务成功，跳出循环
            }
        }
        if(!arranged)   total_deduction += w;  // 无法在ddl内完成，累加扣款
    }
    // 输出最后能获得的最多奖金：初始奖金减去所有扣款
    cout << m - total_deduction << endl;
    return 0;
}
