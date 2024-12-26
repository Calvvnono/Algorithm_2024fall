#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

// 计算 f(A)
vector<int> f(const vector<int>& A) {
    vector<int> B;
    for (int x : A) {
        if (x == 1) {
            B.push_back(0);
            B.push_back(1);
        } else {
            B.push_back(1);
            B.push_back(0);
        }
    }
    return B;
}

// 计算 f^n((1))
vector<int> fn(int n) {
    vector<int> A = {1};
    for (int i = 0; i < n; ++i) {
        A = f(A);
    }
    return A;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        vector<int> result = fn(n);
        ll countPair = 0;
        for (size_t i = 0; i < result.size() - 1; ++i) {
            if (result[i] == 0 && result[i + 1] == 0) {
                countPair++;
            }
        }
        cout << countPair % MOD << endl;
    }
    return 0;
}
