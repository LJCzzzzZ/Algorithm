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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<map<int, int>> col(n);
    vector<vector<int>> pos(n);
    vector<int> ans(n);
    auto dfs = [&](auto self, int x, int fa, int dep) -> void {
        col[x][a[x]] = 1;
        pos[dep].push_back(x);
        for(auto u : adj[x]){
            if(u == fa){
                continue;
            }
            self(self, u, x, dep + 1);
            if(col[u].size() > col[x].size()){
                swap(col[u], col[x]);
            }
            for(auto [c, v] : col[u]){
                col[x][c] += v;
            }
            col[u].clear();
        }
        if(dep + k + 1 < n){
            for(auto u : pos[dep + k + 1]){
                if(--col[x][a[u]] == 0){
                    col[x].erase(a[u]);
                }
            }
            pos[dep + k + 1].clear();
        }
        ans[x] = col[x].size();
    };
    dfs(dfs, 0, -1, 0);

    int m;
    cin >> m;
    for(int i = 0; i < m; i++ ){
        int x;
        cin >> x;
        x--;
        cout << ans[x] << "\n";
    }
    return 0;
}