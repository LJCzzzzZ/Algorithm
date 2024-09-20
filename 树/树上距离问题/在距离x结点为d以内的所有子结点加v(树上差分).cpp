#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int m;
    cin >> m;
    vector<vector<pair<int, int>>> s(n);
    for(int i = 0; i < m; i++ ){
        int v, d, x;
        cin >> v >> d >> x;
        v--;
        s[v].emplace_back(d, x);
    }

    vector<ll> ans(n);
    vector<ll> c(n);
    function<void(int, int, int, ll)> dfs = [&](int x, int fa, int dep, ll sum){
        sum += c[dep];
        for(auto [d, v] : s[x]){
            sum += v;
            if(dep + d + 1 < n ){
                c[dep + d + 1] -= v;
            }
        }

        ans[x] = sum;
        for(auto u : adj[x]){
            if(u == fa) continue;
            dfs(u, x, dep + 1, sum);
        }

        for(auto [d, v] : s[x]){
            if(dep + d + 1 < n){
                c[dep + d + 1] += v;
            }
        }
    };
    dfs(0, -1, 0, 0);
    
    for(int i = 0; i < n; i++ ){
        cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}