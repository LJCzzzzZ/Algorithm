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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> f(1 << n);
    for(int s = 0; s < 1 << n; s++ ){
        int state = 0;
        for(int i = 0; i < n; i++ ){
            if(s >> i & 1){
                for(auto x : adj[i]){
                    state |= (1 << x);
                }
            }
        }
        f[s] = state;
    }

    vector<pair<int, int>> pre(1 << n, {-1, -1});
    vector<int> dis(1 << n, -1);
    queue<int> q;
    q.emplace((1 << n) - 1);
    dis[(1 << n) - 1] = 0;
    while(!q.empty()){
        auto state = q.front();
        q.pop();
        for(int s = state; ; s = (s - 1) & state){
            if(__builtin_popcount(s ^ state) <= k){
                int ns = f[s];
                if(dis[ns] == -1){
                    dis[ns] = dis[state] + 1;
                    q.emplace(ns);
                    pre[ns] = make_pair(s, state);
                }
            }
            if(s == 0){
                break;
            }
        }
    }
    for(int s = state; s > 0; s = (s - 1) & state )
        banzi
    if(dis[0] == -1){
        cout << "-1\n";
        return 0;
    }
    cout << dis[0] << "\n";

    auto dfs = [&](auto self, int state) -> void {
        if(state == (1 << n) - 1){
            return;
        }
        auto [ns, s] = pre[state];
        self(self, s);
        for(int i = 0; i < n; i++ ){
            if((ns ^ s) >> i & 1){
                cout << char('a' + i);
            }
        }
        cout << "\n";
    };
    dfs(dfs, 0);
    return 0;
}