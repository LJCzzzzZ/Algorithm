#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    // 题意: 给定一棵树, 每个点有一个权值, 给出q个询问<a, b> 问 Σ(a[x] * a[y]), x -> f[x], y -> f[y]的权值和
    // 题解: 给每一层的点数进行根号分类
    // 对于 每层个数小于sqrt(n) 的 对数至多sqrt(n) * sqrt(n) 对, 这时到根距离为sqrt(n) 总复杂度为O(n*sqrt(n))
    // 但当深度大, 个数少, 多次询问同一对时, 复杂度不可接受, 这时 可以将每一层建立 sqrt(n) * sqrt(n)的记录表进行记忆化
    // 而对于点数大于sqrt(n)的层, 到根距离至多sqrt(n) 显然直接暴力求解复杂度也为 O(n * sqrt(n))
    // 因此总复杂度为 O(n * sqrt(n))
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++ ){
        int x;
        cin >> x;
        x--;
        adj[x].push_back(i);
    }
    vector<int> d(n), fa(n, -1);
    vector<ll> sum(n);
    auto dfs = [&](auto self, int x) -> void {
        sum[x] += 1ll * a[x] * a[x];
        for(auto u : adj[x]){
            fa[u] = x;
            d[u] = d[x] + 1;
            sum[u] = sum[x];
            self(self, u);
        }
    };
    dfs(dfs, 0);
    int B = 350;
    vector<vector<int>> dep(n);
    vector<int> id(n);
    for(int i = 0; i < n; i++ ){
        id[i] = dep[d[i]].size();
        dep[d[i]].push_back(i);
    }
    vector<vector<ll>> dp(n);
    for(int i = 0; i < n; i++ ){
        if(dep[d[i]].size() <= B){
            dp[i].resize(dep[d[i]].size(), -1);
        }
    }

    auto f = [&](auto self, int x, int y){
        if(x == -1){
            return 0ll;
        }
        if(dep[d[x]].size() <= B && dp[x][id[y]] != -1){
            return dp[x][id[y]];
        }
        ll res = self(self, fa[x], fa[y]) + 1ll * a[x] * a[y];
        if(dep[d[x]].size() <= B){
            dp[x][id[y]] = res;
        }
        return res;
    };
    while(q--){
        int x, y;
        cin >> x >> y;
        x--, y--;
        cout << f(f, x, y) << "\n";
        
    }
    return 0;
}