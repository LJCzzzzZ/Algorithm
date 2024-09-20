#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    // 对于连接u, v的一条边来说
    //如果 deg[u] > deg[v] 则 v -> u
    // 否则 u -> v
    //如果度数相同 编号小的 -> 编号大的
    vector<int> in(n), x(m), y(m);
    for(int i = 0; i < m; i++ ){
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
        in[x[i]]++;
        in[y[i]]++;
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++ ){
        int u = x[i], v = y[i];
        if(in[u] > in[v]){
            swap(u, v);
        } else if(in[u] == in[v] && u > v){
            swap(u, v);
        }
        adj[u].push_back(v);
    }

    ll ans = 0;
    vector<int> vis(n, -1);
    for(int i = 0; i < n; i++ ){
        for(auto u : adj[i]){
            vis[u] = i;
        }
        for(auto u : adj[i]){
            for(auto x : adj[u]){
                if(vis[x] == i){
                    ans++;
                }
            }
        }
    }
    cout << ans << "\n";
    return 0;
}