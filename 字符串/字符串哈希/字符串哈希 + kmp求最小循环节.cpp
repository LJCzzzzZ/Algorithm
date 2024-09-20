#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定n个字符串, 可以将一个字符串循环任意次, 按顺序问当前字符串最少循环几次能使得前面没有相同字符串出现过
    // 题解1: 字符串哈希 + 当前弧优化
    // 将一个长度为k 的字符串 复制n次 = x * pw[k] ^ n + x * pw[k] ^ (n - 1) + x * pw[k] ^ (n - 2) ....
    //                              = x * (pw[k] ^ n + pw[k] ^ (n - 1) ...)
    // 显然其哈希值可以在枚举复制次数时构建出来, 那么就有做法: 对每个字符串枚举其复制次数, 用哈希表保存哈希值查看是否被用过
    // 当有 k 种字符串时 枚举次数为 D(最大长度) D / s1 +  D / s2 + D / s3.... 为调和级数
    // 当只有一种 字符串时, 容易被全为单个相同字符卡成n * n, 引入当前弧优化, 那么单类型复杂度稳定问 D / s1
    // 总复杂度 O(nlognlogn) -> 调和级数 + 哈希表

    // 题解2: 字符串最小循环节 + 当前弧优化
    // 显然对于任意两种最小循环节不相同的字符串来说, 两者任意时刻不会被影响, 而对于相同的只需要知道最小可用即可
    // 求最小循环节用kmp算法算出f数组, 最小循环节即为 d = m % (n - f[n]) ? m : n - f[n];
    // 求最小可用时, 暴力枚举 + 保存当前最小循环节能用的最小为起点枚举
    // 复杂度 O(nlognlogn)  
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> s(n);
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> s[i];
        int m = s[i].size();
        vector<int> f(m + 1);
        for(int j = 1, k = 0; j < m; j++ ){
            while(k && s[i][k] != s[i][j]){
                k = f[k];
            }
            k += (s[i][k] == s[i][j]);
            f[j + 1] = k;
        }
        int d = (m % (m - f[m]) ? m : m - f[m]);
        a[i] = m / d;
        s[i] = s[i].substr(0, d);
    }

    map<string, map<int, int>> mp;
    map<string, set<int>> st;
    for(int i = 0; i < n; i++ ){
        int &res = mp[s[i]][a[i]];
        if(res == 0){
            res = a[i];
        }
        auto &t = st[s[i]];
        while(t.count(res)){
            res += a[i];
        }
        t.insert(res);
        cout << res / a[i] << " \n"[i == n - 1];
    }
    return 0;
}
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
const int N = 2e5 + 10;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(pair<int, int> x) const { return x.fi ^ x.se ^ RANDOM; }
};
typedef gp_hash_table<pair<int, int>, int, chash> hash_t;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<hashv> pw(N);
    hashv base(13331, 23333);
    pw[0] = mp(1, 1);
    for(int i = 1; i < N; i++ ){
        pw[i] = pw[i - 1] * base;
    }
    int n;
    cin >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++ ){
        cin >> s[i];
    }    
    auto t = s;
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    vector<int> id(n);
    for(int i = 0; i < n; i++ ){
        id[i] = lower_bound(t.begin(), t.end(), s[i]) - t.begin();
    }

    int m = t.size();
    vector<pair<int, int>> hs(m); 
    for(int i = 0; i < m; i++ ){
        for(auto x : t[i]){
            hs[i] = hs[i] * base + mp(x, x);
        }
    }   

    hash_t mp;
    vector<int> cur(m);
    vector<pair<int, int>> p(m, {1, 1});
    for(int i = 0; i < n; i++ ){
        hashv B = pw[(int)s[i].size()];
        hashv pre = p[id[i]];
        for(int j = cur[id[i]]; ; j++ ){
            if(mp.find(hs[id[i]] * pre) == mp.end()){
                mp[hs[id[i]] * pre] = 1;
                cout << j + 1 << " \n"[i == n - 1];
                cur[id[i]] = j;
                p[id[i]] = pre;
                break;
            }
            pre = pre * B;
            pre = pre + hashv(1, 1);
        }
    }
    return 0;
}