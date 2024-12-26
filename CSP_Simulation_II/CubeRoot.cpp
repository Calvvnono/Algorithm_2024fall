#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;

// 质因数分解
vector<pair<ll, int>> factorize(ll x) {
    vector<pair<ll, int>> factors;
    for (ll i = 2; i * i <= x; ++i) {
        int cnt = 0;
        while (x % i == 0) {
            x /= i;
            cnt++;
        }
        if (cnt > 0) {
            factors.push_back({i, cnt});
        }
    }
    if (x > 1) {
        factors.push_back({x, 1});
    }
    return factors;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        ll x;
        cin >> x;
        ll a = 1;
        ll b = 1;
        vector<pair<ll, int>> factors = factorize(x);
        for (auto& factor : factors) {
            ll p = factor.first;
            int exp = factor.second;
            int outside = exp / 3;
            int inside = exp % 3;
            a *= pow(p, outside);
            b *= pow(p, inside);
        }
        cout << a << endl;
    }
    return 0;
}
