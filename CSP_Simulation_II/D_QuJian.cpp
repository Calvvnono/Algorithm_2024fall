// 整体思路：使用双端队列在遍历过程中维护当前窗口的最大值和最小值，以便快速判断区间差是否大于 K，从而高效统计所有满足条件的“好区间”。

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    // 处理每个查询
    while(m--){
        int k;
        cin >> k;
        // 使用双端队列维护窗口内的最大值和最小值
        int left = 0;
        long long count = 0;
        deque<int> maxdq, mindq;
        for(int right = 0; right < n; right++){
            // 更新最大值双端队列：保持队列中的元素递减
            while(!maxdq.empty() && a[right] > a[maxdq.back()]) maxdq.pop_back();
            maxdq.push_back(right);
            // 更新最小值双端队列：保持队列中的元素递增
            while(!mindq.empty() && a[right] < a[mindq.back()]) mindq.pop_back();
            mindq.push_back(right);
            // 检查当前窗口是否满足条件：最大值和最小值之差是否大于 k
            while(left <= right && a[maxdq.front()] - a[mindq.front()] > k){
                left++;
                // 移动左边界时更新双端队列：确保队列中的��引在当前窗口范围内
                if(maxdq.front() < left) maxdq.pop_front();
                if(mindq.front() < left) mindq.pop_front();
            }
            // 统计满足条件的区间数量：当前窗口的左边界位置
            count += left;
        }
        // 输出当前查询的结果
        cout << count << "\n";
    }
}
