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
    int n;
    cin >> n;
    vector<int> fa(n);
    vector<vector<int>> adj(n);
    for(int i = 0; i < n; i++ ){
        cin >> fa[i];
        fa[i]--;
        if(fa[i] != -1){
            adj[fa[i]].push_back(i);
        }
    }

    int m;
    cin >> m;
    vector<vector<int>> query(n);
    vector<int> k(m);
    for(int i = 0; i < m; i++ ){
        int x;
        cin >> x >> k[i];
        x--;
        query[x].push_back(i);
    }

    vector<int> siz(n, 1), dep(n), stk;
    vector<int> ans(m);
    auto dfs1 = [&](auto self, int x) -> void {
        stk.push_back(x);
        for(auto i : query[x]){
            if(dep[x] >= k[i]){
                ans[i] = stk[dep[x] - k[i]];
            } else {
                ans[i] = -1;
            }
        }

        for(auto &u : adj[x]){
            dep[u] = dep[x] + 1;
            self(self, u);
            siz[x] += siz[u];
            if(siz[u] > siz[adj[x][0]]){
                swap(u, adj[x][0]);
            }
        }
        stk.pop_back();
    };
    for(int i = 0; i < n; i++ ){
        if(fa[i] == -1){
            dfs1(dfs1, i);
        }
    }
    for(int i = 0; i < n; i++ ){
        query[i].clear();
    }
    for(int i = 0; i < m; i++ ){
        if(ans[i] == -1){
            ans[i] = 0;
        } else {
            query[ans[i]].push_back(i);
        }
    }

    vector<int> in(n), out(n), seq(n);
    int ctt = 0;
    auto dfs2 = [&](auto self, int x) -> void {
        in[x] = ctt++;
        seq[in[x]] = x; 
        for(auto u : adj[x]){
            self(self, u);
        }
        out[x] = ctt;
    };
    for(int i = 0; i < n; i++ ){
        if(fa[i] == -1){
            dfs2(dfs2, i);
        }
    }
    vector<int> cnt(n);
    auto update = [&](int x, int w){
        cnt[dep[x]] += w;
    };
    auto dfs3 = [&](auto self, int x, int del) -> void {
        for(auto u : adj[x]){
            if(u == adj[x][0]){
                continue;
            }
            self(self, u, 1);
        }
        if(!adj[x].empty()){
            self(self, adj[x][0], 0);
        }

        for(auto u : adj[x]){
            if(u == adj[x][0]){
                continue;
            }
            for(int i = in[u]; i < out[u]; i++ ){
                update(seq[i], 1);
            }
        }
        
        update(x, 1);
        for(auto i : query[x]){
            ans[i] = cnt[dep[x] + k[i]] - 1;
        }
        if(del){
            for(int i = in[x]; i < out[x]; i++ ){
                update(seq[i], -1);
            }
        }
    };
    for(int i = 0; i < n; i++ ){
        if(fa[i] == -1){
            dfs3(dfs3, i, 1);
        }
    }
    for(int i = 0; i < m; i++ ){
        cout << ans[i] << " \n"[i == m - 1];
    }
    return 0;
}