#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = 1e9 + 7;

// 快速幂实现
ll fastPow(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// 分成尽可能多的3（接近e）能获得最大的乘积
ll maxProfit(int n) {
    if (n < 4) return n;
    ll result = 1;
    int countOfThree = n / 3;
    if (n % 3 == 1) {
        countOfThree--;
        result = 4;
    } else if (n % 3 == 2) {
        result = 2;
    }
    result = (result * fastPow(3, countOfThree, mod)) % mod;
    return result;
}

int main() {
    int n;
    cin >> n;
    cout << maxProfit(n) << endl;
    return 0;
}