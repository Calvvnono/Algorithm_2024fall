#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    while(n--){
        string s;
        cin >> s;
        if(s.size() < 6){
            cout << 0 << endl;
            continue;
        }
        bool has_letter = false, has_digit = false, has_special = false;
        unordered_map<char, int> cnt;
        // 简单的遍历每个字符串，统计字母、数字、特殊字符的个数
        for(auto c : s){
            if(isalpha(c)) has_letter = true;
            else if(isdigit(c)) has_digit = true;
            else if(c == '*' || c == '#') has_special = true;
            cnt[c]++;
        }
        if(has_letter && has_digit && has_special){
            bool high = true;
            for(auto &[c, count] : cnt){
                if(count > 2){
                    high = false;
                    break;
                }
            }
            if(high) cout << 2 << endl;
            else cout << 1 << endl;
        }
        else{
            cout << 0 << endl;
        }
    }
}
