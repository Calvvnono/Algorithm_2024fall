#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> blocks(n);
    for (int i = 0; i < n; ++i) {
        cin >> blocks[i].first >> blocks[i].second;
    }

    // 问题 1：计算第一层最多能有多少个方块
    sort(blocks.begin(), blocks.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });
    int countFirstLayer = 0;
    int lastEnd = -1e9;
    for (const auto& block : blocks) {
        if (block.first >= lastEnd) {
            countFirstLayer++;
            lastEnd = block.second;
        }
    }

    // 问题 2：计算最少需要多少层
    vector<pair<int, int>> events;
    for (const auto& block : blocks) {
        events.push_back({block.first, 1});   // 左端点，计数 +1
        events.push_back({block.second, -1}); // 右端点，计数 -1
    }
    sort(events.begin(), events.end());
    int maxOverlap = 0;
    int currentOverlap = 0;
    for (const auto& event : events) {
        currentOverlap += event.second;
        if (currentOverlap > maxOverlap) {
            maxOverlap = currentOverlap;
        }
    }

    cout << countFirstLayer << " " << maxOverlap << endl;

    return 0;
}
