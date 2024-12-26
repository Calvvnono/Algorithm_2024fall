#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll Count=0;

/**
 * 设置一个小根堆
 * 每次合并最小的两堆，并插入合并的新堆
 */

int main(){
    cin >> n;
    // 每个堆的质量都在 2*10^9 以内，堆(存储和)要用 long long
    priority_queue<ll,vector<ll>,greater<ll>> q;
    for (int i = 0; i < n; i ++) {
        int w;
        cin >> w;
        q.push(w);
    }
    //每次将质量最小的两堆合并
    while(q.size() > 1){
        ll s1 = q.top();   q.pop();
        ll s2 = q.top();   q.pop();
        ll s3 = s1 + s2;
        Count += s3;
        //将合并好的堆放回
        q.push(s3);
    }
    cout << Count;
    return 0;
}