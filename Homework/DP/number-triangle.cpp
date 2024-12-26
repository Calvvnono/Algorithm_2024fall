#include <bits/stdc++.h>
using namespace std;

/**
 * num[i][j]可以由num[i-1][j]或num[i-1][j-1]得到
 * dp[i][j]表示从num[0][0]到num[i][j]的最大路径和
 * dp[i][j] = num[i][j] + max(dp[i-1][j], dp[i-1][j-1])
 */

int INF = -987654321;
int num[1001][1001];
int dp[1001][1001];
int ans;

int main() {
    int r, i, j;
    cin >> r;
    for (i = 0; i < r; i++) {
        for (j = 0; j <= i; j++) 
            cin >> num[i][j];
        num[i][j] = INF;
    }
    dp[0][0] = num[0][0];
    for (i = 1; i < r; i++) {
        for (j = 0; j <= i; j++) {
            if (j == 0)
                dp[i][j] = num[i][j] + dp[i-1][j];
            else
                dp[i][j] = num[i][j] + max(dp[i-1][j], dp[i-1][j-1]);
        }
    }
    for (int n = 0; n < r; n++)
        ans = max(ans, dp[r-1][n]);
    cout << ans << endl;
    return 0;
}