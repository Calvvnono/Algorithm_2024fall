#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> parent;
vector<int> rankArray;

void init(int n) {
    parent.resize(n + 1); // 修改为 n + 1 以防止越界
    rankArray.resize(n + 1, 0);
    for (int i = 0; i <= n; ++i) { // 修改为 <= 以包括所有元素
        parent[i] = i;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); 
    }
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rankArray[rootX] > rankArray[rootY]) {
            parent[rootY] = rootX;
        } else if (rankArray[rootX] < rankArray[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rankArray[rootX]++;
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    init(N);
    string result;

    for (int i = 0; i < M; ++i) {
        int Zi, Xi, Yi;
        cin >> Zi >> Xi >> Yi;

        // 检查输入是否在范围内
        if (Xi < 0 || Xi > N || Yi < 0 || Yi > N) {
            continue; // 跳过无效输入
        }

        if (Zi == 0) {
            unite(Xi, Yi);
        } else if (Zi == 1) {
            if (find(Xi) == find(Yi)) {
                result += '1';
            } else {
                result += '0';
            }
        }
    }

    // 手动将二进制字符串转换为十进制
    long long binaryResult = 0;
    for (char c : result) {
        binaryResult = (binaryResult * 2 + (c - '0')) % 998244353;
    }

    cout << binaryResult << endl;
    return 0;
}
