#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
#define mp make_pair
typedef pair<int, int> hashv;
const ll mod1 = 1e9 + 7;
const ll mod2 = 1e9 + 9;

hashv operator + (hashv a, hashv b) {
    int c1 = a.fi + b.fi,c2 = a.se + b.se;
    if (c1 >= mod1) c1 -= mod1;
    if (c2 >= mod2) c2 -= mod2;
    return mp(c1, c2);
}

hashv operator - (hashv a, hashv b) {
    int c1 = a.fi - b.fi,c2 = a.se - b.se;
    if (c1 < 0) c1 += mod1;
    if (c2 < 0) c2 += mod2;
    return mp(c1, c2);
}

hashv operator * (hashv a, hashv b) {
    return mp(1ll * a.fi * b.fi % mod1, 1ll * a.se * b.se % mod2);
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> s(n);
    int m = 0;
    for(int i = 0; i < n; i++ ){
        cin >> s[i];
        m = max(m, (int)s[i].size());
    }    


    hashv base(13331, 23333);
    vector<hashv> pw(m + 1), pre(m + 1);
    pw[0] = mp(1, 1);
    for(int i = 0; i < m; i++ ){ // 预处理每一位
        pw[i + 1] = pw[i] * base;
    }
    vector<int> a(m);
    hashv S = mp(0, 0);
    // 字符串哈希是前缀和, 是一位一位的, 特殊的: 二进制串异或的改变某一位
    // 因此可以求出剔除某一个串后的所有串的哈希值
    auto add = [&](int pos){
        if(a[pos] > 0){
            S = S - pw[pos];
        } else {
            S = S + pw[pos];
        }   
        a[pos] ^= 1;
    };
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < (int)s[i].size(); j++ ){
            if(s[i][j] == '1'){
                add(j);
            }
        }
    }


    int ans = 0;
    for(int i = 0; i < n; i++ ){
        hashv T = mp(0, 0);
        for(int j = s[i].size() - 1; j >= 1; j-- ){
            T = T * base;
            if(s[i][j] == '1'){
                add(j);
                T = T + mp(1, 1);
            }
            if(T == S){
                ans += 1;
            }
        }
        for(int j = s[i].size() - 1; j >= 1; j-- ){
            if(s[i][j] == '1'){
                add(j);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}