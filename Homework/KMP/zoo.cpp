#include<bits/stdc++.h>
using namespace std;
const int yyj = 1e9+7;
const int MAXLEN = 1e6+5;
typedef int _int;
#define int long long
 
int T, n, nex[MAXLEN], num[MAXLEN], ans = 0;
char s[MAXLEN];
 
_int main(){
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--){
    memset(nex, 0, sizeof(nex));
    memset(num, 0, sizeof(num)); ans = 1, num[1] = 1;
    cin >> s+1; n = strlen(s+1), nex[2] = 1;
    for(int i=2, j=0;i<=n;i++){
        while(j && s[j+1] != s[i]) j = nex[j];
        j += s[i] == s[j+1], nex[i] = j, num[i] = num[j]+1;
    }
    for(int i=1, j=0;i<=n;i++){
        while(j && s[j+1] != s[i]) j = nex[j];
        j += s[j+1] == s[i];
        while(j*2 > i) j = nex[j];
        ans = (ans*(num[j]+1)) % yyj;
    }
        cout << ans << endl;
    }
    return 0;
}