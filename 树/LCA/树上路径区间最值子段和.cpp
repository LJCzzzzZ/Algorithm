#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
struct info {
    int sum;
    int mx, mxl, mxr;
    int mn, mnl, mnr;
    void init(int x){
        sum = x;
        mx = max(x, 0);
        mn = min(x, 0);
        mxl = mxr = mx;
        mnl = mnr = mn;
    }
    info rev() { return {sum, mx, mxr, mxl, mn, mnr, mnl}; }
    info operator + (const info &o) {
        return {
            sum + o.sum,
            max({mx, o.mx, mxr + o.mxl}),
            max(mxl, sum + o.mxl),
            max(o.mxr, mxr + o.sum),
            min({mn, o.mn, mnr + o.mnl}),
            min(mnl, sum + o.mnl),
            min(o.mnr, mnr + o.sum)
        };
    }
};
void solve(){
    // 题意:问树上任意两个点之间的简单路径之间是否存在一个和大于等于k的子段
    // 题解:倍增 + 树上四毛子(区间前后缀最大和, 区间最大和, 区间前后缀最小和, 区间最小和)
    // 路径问题考虑两点之间的LCA, 则 该整个区间为 L + info[u][1] + info[v][0] + R.rev(), 右链如果要链接要反过来
    int n;
    cin >> n;
    int cur = 1;
    int t = 18; 
    vector<vector<int>> f(n + 2, vector<int> (t));
    vector<vector<info>> p(n + 2, vector<info> (t));
    vector<int> dep(n + 2);
    p[1][0].init(1);
    dep[1] = 1;
    for(int i = 0; i < n; i++ ){
        char o;
        cin >> o;
        if(o == '+'){
            int v, x;
            cur += 1;
            cin >> v >> x;
            f[cur][0] = v;
            p[cur][0].init(x);
            dep[cur] = dep[v] + 1;
            for(int j = 1; j < t; j++ ){
                f[cur][j] = f[f[cur][j - 1]][j - 1];
                p[cur][j] = p[cur][j - 1] + p[f[cur][j - 1]][j - 1];
            }
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            info L, R, res;
            L.init(0), R.init(0);
            if(dep[u] < dep[v]){
                swap(u, v);
            }
            for(int j = t - 1; j >= 0; j-- ){
                if(dep[u] - (1 << j) >= dep[v]){
                    L = L + p[u][j];
                    u = f[u][j];
                }
            }
            if(u == v){
                res = L + p[u][0];
            } else {
                for(int j = t - 1; j >= 0; j-- ){
                    if(f[u][j] != f[v][j]){
                        L = L + p[u][j];
                        R = R + p[v][j];
                        u = f[u][j];
                        v = f[v][j];
                    }
                }
                res = L + p[u][1] + p[v][0] + R.rev();
            }
            if(res.mx >= k && res.mn <= k){
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
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