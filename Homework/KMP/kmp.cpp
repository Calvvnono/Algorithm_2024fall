#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 计算部分匹配表（前缀函数）
vector<int> computePrefixFunction(const string &pattern) {
    int m = pattern.length();
    vector<int> pi(m, 0);
    int k = 0;
    for (int q = 1; q < m; q++) {
        // 如果字符不匹配，回退到前一个匹配的位置
        while (k > 0 && pattern[k] != pattern[q]) {
            k = pi[k - 1];
        }
        // 如果字符匹配，前缀长度加1
        if (pattern[k] == pattern[q]) {
            k++;
        }
        pi[q] = k; // 记录前缀长度
    }
    return pi;
}

// KMP算法
int KMPMatcher(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> pi = computePrefixFunction(pattern);
    int q = 0; // 当前匹配的字符数
    int count = 0; // 记录匹配次数
    for (int i = 0; i < n; i++) {
        // 如果字符不匹配，回退到前一个匹配的位置
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q - 1];
        }
        // 如果字符匹配，匹配字符数加1
        if (pattern[q] == text[i]) {
            q++;
        }
        // 如果匹配字符数等于模式串长度，说明找到一个匹配
        if (q == m) {
            count++; // 匹配次数加1
            q = pi[q - 1]; // 继续寻找下一个匹配
        }
    }
    return count;
}

int main() {
    string A, B;
    cin >> A >> B;
    cout << KMPMatcher(A, B) << endl; // 输出B在A中的出现次数
    return 0;
}
