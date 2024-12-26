#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    s = s.substr(1, s.size() - 2);

    int n;
    cin >> n;
    cin.ignore(); 

    unordered_map<char, char> f;
    for(int i = 0; i < n; ++i){
        string rule;
        getline(cin, rule);
        f[rule[1]] = rule[2];
    }

    int m;
    cin >> m;
    vector<long long> queries(m);
    for(auto &k : queries) cin >> k;

    for(auto k : queries){
        string transformed = s;
        for(long long step = 0; step < k; ++step){
            for(auto &c : transformed){
                if(f.find(c) != f.end()){
                    c = f[c];
                }
            }
        }
        cout << "#" << transformed << "#" << "\n";
    }
    return 0;
}
