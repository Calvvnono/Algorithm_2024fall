#include <iostream>
#include <string>
using namespace std;

// 全局变量，记录当前解析的位置
int pos;

// 解析因子：处理括号或单个字符
int parseFactor(const string& s);

// 解析项：处理连接的因子
int parseTerm(const string& s);

// 解析表达式：处理含有 '|' 的部分
int parseExpression(const string& s) {
    int maxLen = parseTerm(s);
    while (pos < s.length() && s[pos] == '|') {
        pos++; // 跳过 '|'
        int len = parseTerm(s);
        if (len > maxLen) {
            maxLen = len;
        }
    }
    return maxLen;
}

int parseTerm(const string& s) {
    int totalLen = 0;
    while (pos < s.length() && s[pos] != '|' && s[pos] != ')') {
        int len = parseFactor(s);
        totalLen += len;
    }
    return totalLen;
}

int parseFactor(const string& s) {
    if (s[pos] == 'a') {
        pos++;
        return 1;
    } else if (s[pos] == '(') {
        pos++; // 跳过 '('
        int len = parseExpression(s);
        pos++; // 跳过 ')'
        return len;
    }
    return 0;
}

int main() {
    string s;
    cin >> s;
    pos = 0;
    int result = parseExpression(s);
    cout << result << endl;
    return 0;
}
