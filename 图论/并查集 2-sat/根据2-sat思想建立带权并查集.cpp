#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

vector<int> fa, d;
vector<vector<int>> c;
vector<ll> a, b;
int find(int x){
    if(x == fa[x]){
        return x;
    }
    int f = find(fa[x]);
    d[x] ^= d[fa[x]];
    fa[x] = f;
    return f;
}
void solve(){

    // 题意: 给出n个字符串, 可以任意反转整个字符串, 求反转最少的字符串使得两两之间至少有k位相同
    // 题解: 根据2-sat的思想建立带权并查集
    // 有字符串si sj, 若si 和 sj都不反转时不能匹配只说明必须反转其中一个, 则i, j连并查集且带权不同
    // 若其中一个反转后不能匹配说明都不能反转, 则i, j连并查集且带权相同
    // 可行判断: 连并查集的过程中若已经在同一个并查集则不能和已有条件失配
    // 可行解: 取并查集中0, 1权值总和小的部分
    int n, m, k;
    cin >> n >> m >> k;
    fa.resize(n);
    d.assign(n, 0);
    a.resize(n);
    b.resize(n);
    c.assign(n, vector<int> (2, 0));
    iota(fa.begin(), fa.end(), 0);
    for(int i = 0; i < n; i++ ){
        string s;
        cin >> s;
        a[i] = 0;
        for(auto x : s){
            a[i] = 2ll * a[i] + x - '0';
        }
        reverse(s.begin(), s.end());
        b[i] = 0;
        for(auto x : s){
            b[i] = 2ll * b[i] + x - '0';
        }
    }
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < i; j++ ){
            if(m - __builtin_popcountll(a[i] ^ a[j]) < k){
                int x = find(i);
                int y = find(j);
                if(x == y && d[i] == d[j]){
                    cout << "-1\n";
                    return;
                }

                if(x != y){
                    fa[y] = x;
                    d[y] = d[i] ^ d[j] ^ 1;
                }
            }

            if(m - __builtin_popcountll(a[i] ^ b[j]) < k){
                int x = find(i);
                int y = find(j);
                if(x == y && d[i] != d[j]){
                    cout << "-1\n";
                    return;
                }

                if(x != y){
                    fa[y] = x;
                    d[y] = d[i] ^ d[j];
                }
            }
        }
    }

    for(int i = 0; i < n; i++ ){
        find(i);
        c[fa[i]][d[i]] += 1;
    }
    for(int i = 0; i < n; i++ ){
        if(c[i][0] < c[i][1]){
            c[i][0] = -1;
        } else {
            c[i][1] = -1;
        }
    }

    vector<int> ans;
    for(int i = 0; i < n; i++ ){
        if(c[fa[i]][d[i]] == -1){
            ans.push_back(i);
        }
    }
    cout << (int) ans.size() << "\n";
    for(auto x : ans){
        cout << x + 1 << " \n"[x == ans.back()];
    }
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}