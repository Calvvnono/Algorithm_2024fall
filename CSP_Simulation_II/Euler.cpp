#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// 对数进行质因数分解，结果存入 factors
void factorize(int x, map<int, int>& factors) {
    for (int i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            factors[i]++;
            x /= i;
        }
    }
    if (x > 1) {
        factors[x]++;
    }
}

int main() {
    int n;
    cin >> n;
    map<int, int> phi_factors;  // 存储 φ(N) 的质因数及指数
    vector<pair<int, int>> input; // 存储输入的素数及其指数
    for (int i = 0; i < n; ++i) {
        int p, e;
        cin >> p >> e;
        input.emplace_back(p, e);
    }
    // 计算 φ(N)
    for (auto pe : input) {
        int p = pe.first;
        int e = pe.second;
        if (e > 1) {
            phi_factors[p] += e - 1; // 更新 φ(N) 中 p 的指数
        }
        // 对 p - 1 进行质因数分解
        map<int, int> temp_factors;
        factorize(p - 1, temp_factors);
        for (auto tf : temp_factors) {
            phi_factors[tf.first] += tf.second;
        }
    }
    // 按素数从小到大输出 φ(N) 的质因数分解
    for (auto pf : phi_factors) {
        cout << pf.first << " " << pf.second << endl;
    }
    return 0;
}
