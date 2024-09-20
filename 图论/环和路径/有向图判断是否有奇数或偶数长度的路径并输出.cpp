#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> out(n);
    for(int i = 0; i < n; i++ ){
        int c, x;
        cin >> c;
        out[i] = c;
        for(int j = 0; j < c; j++ ){
            cin >> x;
            x--;
            adj[i].push_back(x);
        }
    }
    
    int s;
    cin >> s;
    s--;
    vector<vector<int>> dp(n, vector<int> (2, -1)), pre(dp);
    pre[s][0] = -2;
    queue<pair<int, int>> q;
    q.emplace(s, 0);
    while(!q.empty()){
        auto [x, t] = q.front();
        q.pop();
        for(auto u : adj[x]){
            if(pre[u][t ^ 1] == -1){
                pre[u][t ^ 1] = x;
                q.emplace(u, t ^ 1);
            }
        }
    }

    auto print = [&](auto self, int x, int t) -> void {
        if(pre[x][t] == -2){
            cout << x + 1 << " ";
            return;
        }
        self(self, pre[x][t], t ^ 1);
        cout << x + 1 << " ";
    };
    for(int i = 0; i < n; i++ ){
        if(out[i] == 0 && pre[i][1] != -1){
            cout << "Win\n";
            print(print, i, 1);
            return 0;
        }
    }

    vector<int> was(n);
    bool cycle = false;
    auto dfs = [&](auto self, int x) -> void {
        was[x] = 1;
        for(auto u : adj[x]){
            if(was[u] == -1) continue;
            if(was[u] == 1){
                cycle = true;
            } else {
                self(self, u);
            }
        }
        was[x] = -1;
    };
    dfs(dfs, s);
    if(cycle){
        cout << "Draw\n";
    } else {
        cout << "Lose\n";
    }
    return 0;
}