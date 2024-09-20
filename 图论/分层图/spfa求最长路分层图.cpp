#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const ll INF = 2e18;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
    }

    vector<int> dfn(n), low(n), stk, c(n), ins(n);
    int cnt = 0, ctt = 0;
    auto tarjan = [&](auto self, int x) -> void {
        dfn[x] = low[x] = ++cnt;
        stk.push_back(x);
        ins[x] = 1;
        for(auto u : adj[x]){
            if(!dfn[u]){
                self(self, u);
                low[x] = min(low[x], low[u]);
            } else if(ins[u]){
                low[x] = min(low[x], dfn[u]);
            }
        }
        if(low[x] == dfn[x]){
            int z;
            ctt++;
            do{
                z = stk.back();
                stk.pop_back();
                ins[z] = 0;
                c[z] = ctt;
            }while(x != z);
        }
    };
    for(int i = 0; i < n; i++ ){
        if(!dfn[i]){
            tarjan(tarjan, i);
        }
    }

    vector<vector<int>> e(ctt + 1);
    vector<vector<int>> g(ctt + 1);
    vector<int> w(ctt + 1);
    for(int i = 0; i < n; i++ ){
        w[c[i]]++;
        // cout << i << " " << c[i] << "ccc\n";
        for(auto u : adj[i]){
            if(c[i] != c[u]){
                e[c[i]].push_back(c[u]);
                g[c[u]].push_back(c[i]);
            }
        }
    }

    vector<vector<int>> dis(ctt + 1, vector<int> (2));
    vector<vector<int>> vis(ctt + 1, vector<int> (2));
    queue<tuple<int, int, int>> q;
    q.emplace(c[0], 0, 0);
    vis[c[0]][0] = 1;
    // spfa 跑最长路分层图
    while(!q.empty()){
        auto [x, t, d] = q.front();
        q.pop();
        vis[x][t] = 0;
        for(auto u : e[x]){
            if(dis[u][t] < dis[x][t] + w[u]){
                dis[u][t] = dis[x][t] + w[u];
                if(!vis[u][t]){
                    q.emplace(u, t, dis[u][t]);
                }
            }
        } 
        if(t == 0){
            for(auto u : g[x]){
                if(dis[u][t + 1] < dis[x][t] + w[u]){
                    dis[u][t + 1] = dis[x][t] + w[u];
                    if(!vis[u][t + 1]){
                        q.emplace(u, t + 1, dis[u][t + 1]);
                    }
                }
            }
        }
    }
    dis[c[0]][0] = max(dis[c[0]][0], w[c[0]]);
    cout << max(dis[c[0]][0], dis[c[0]][1]) << "\n";
    return 0;
}