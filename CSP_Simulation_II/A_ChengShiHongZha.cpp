// 这段代码的整体思路：
// 1. 读取每个城市的重要度。
// 2. 将城市按照重要度从大到小排序。
// 3. 遍历排序后的城市列表，对于重要度相同的城市，它们最早可能被轰炸的顺序是相同的。
// 4. 计算并输出每个城市最早可能被轰炸的顺序。

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> cities(n);
    
    // 读取城市的重要度
    for (int i = 0; i < n; ++i) {
        int importance;
        cin >> importance;
        cities[i] = {importance, i};
    }
    
    // 按重要度从大到小排序
    sort(cities.begin(), cities.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first;
    });
    
    // 计算每个城市最早可能被轰炸的顺序
    vector<int> result(n);
    int count = 0;
    for (int i = 0; i < n; ) {
        int j = i;
        // 找出所有重要度相同的城市
        while (j < n && cities[j].first == cities[i].first) {
            j++;
        }
        // 对于重要度相同的城市，最早可能被轰炸的顺序相同
        for (int k = i; k < j; k++) {
            result[cities[k].second] = count + 1;
        }
        count += j - i;
        i = j;
    }
    
    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}