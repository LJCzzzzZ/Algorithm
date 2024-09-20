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
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].emplace_back(y, i);
        adj[y].emplace_back(x, i);
    }

    vector<int> dfn(n), low(n), bridge(m);
    int cnt = 0;
    auto tarjan = [&](auto self, int x, int type) -> void {
        dfn[x] = low[x] = ++cnt;
        for(auto [u, id] : adj[x]){
            if(!dfn[u]){
                self(self, u, id);
                low[x] = min(low[x], low[u]);
                if(dfn[x] < low[u]){
                    bridge[id] = 1;
                }
            } else if(type != id){
                low[x] = min(low[x], dfn[u]);
            }
        }
    };
    for(int i = 0; i < n; i++ ){
        if(!dfn[i]){
            tarjan(tarjan, i, -1);
        }
    }

    vector<tuple<int, int, int>> edge;
    vector<int> col(n), was(m);
    int ctt = 0;
    for(int i = 0; i < n; i++ ){
        if(!col[i]){
            ctt += 1;
            auto dfs = [&](auto self, int x, int fa) -> void {
                col[x] = ctt;
                for(auto [u, id] : adj[x]){
                    if(u == fa || bridge[id] || was[id]){
                        continue;
                    }
                    edge.emplace_back(id, x, u);
                    was[id] = 1;
                    if(col[u]){
                        continue;
                    }
                    self(self, u, x);
                }
            };
            dfs(dfs, i, i);
        }
    }
    vector<vector<tuple<int, int, int, int>>> e(ctt + 1);
    vector<int> t(ctt + 1);
    for(int i = 0; i < n; i++ ){
        t[col[i]] += 1;
        for(auto [u, id] : adj[i]){
            if(col[u] != col[i]){
                e[col[i]].emplace_back(col[u], id, i, u);
            }
        }
    }

    int ans = *max_element(t.begin(), t.end());
    for(int i = 1; i <= ctt; i++ ){
        if(t[i] == ans){
            auto dfs1 = [&](auto self, int x, int fa) -> void {
                for(auto [u, id, t, f] : e[x]){
                    if(u == fa){
                        continue;
                    }
                    edge.emplace_back(id, f, t);
                    self(self, u, x);
                }
            };
            dfs1(dfs1, i, i);
            break;
        }
    }
    sort(edge.begin(), edge.end());
    cout << ans << "\n";
    for(auto [id, x, y] : edge){
        cout << x + 1 << " " << y + 1 << "\n";
    }
    return 0;
}