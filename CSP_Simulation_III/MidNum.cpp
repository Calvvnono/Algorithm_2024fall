#include <bits/stdc++.h>
using namespace std;
/**  Naive Version
int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    long long count = 0;
    // 遍历所有可能的子段
    for(int i = 0; i < n; ++i){
        vector<int> temp;
        for(int j = i; j < n; ++j){
            temp.push_back(a[j]);
            int len = temp.size();
            vector<int> sorted = temp;
            sort(sorted.begin(), sorted.end());
            int median = sorted[len / 2];
            if(median >= m) count++;
        }
    }
    cout << count;
    return 0;
}
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int count = 0;

    // 枚举所有以 i 为起点的子段
    for (int left = 0; left < n; ++left) {
        multiset<int> window;
        
        // 枚举所有以 left 为起点的子段
        for (int right = left; right < n; ++right) {
            window.insert(arr[right]);
            
            // 计算当前窗口的中位数
            int size = window.size();
            int median;
            auto it = window.begin();
            
            if (size % 2 == 1) {  // 如果子段长度是奇数
                // 中位数是中间的那个数
                advance(it, size / 2);
                median = *it;
            } else {  // 如果子段长度是偶数
                // 中位数是中间两个数的较大值
                advance(it, size / 2 - 1);
                median = max(*it, *next(it));
            }
            
            // 如果中位数大于 m，增加计数
            if (median >= m) {
                count++;
            }
        }
    }

    cout << count << endl;

    return 0;
}
