#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
struct Edge{
    int to, cap;
    Edge(int to, int cap) : to(to), cap(cap) {}
};
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> m >> n;
    vector<Edge> e;
    vector<vector<int>> g(n + 2);
    vector<int> cur, h;
    for(int i = 1; i <= m; i++ ){
        g[0].push_back(e.size());
        e.emplace_back(i, 1);
        g[i].push_back(e.size());
        e.emplace_back(0, 0);
    }

    for(int i = 1; i <= n - m; i++ ){
        g[m + i].push_back(e.size());
        e.emplace_back(n + 1, 1);
        g[n + 1].push_back(e.size());
        e.emplace_back(m + i, 0);
    }

    int x, y;
    while(true){
        cin >> x >> y;
        if(x == -1 && y == -1){
            break;
        }
        g[x].emplace_back(e.size());
        e.emplace_back(y, 1);
        g[y].emplace_back(e.size());
        e.emplace_back(x, 0);
    }

    auto bfs = [&](int s, int t){
        h.assign(n + 2, -1);
        h[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            auto x = q.front();
            q.pop();
            for(auto u : g[x]){
                auto [v, c] = e[u];
                if(c > 0 && h[v] == -1){
                    h[v] = h[x] + 1;
                    q.push(v);
                    if(v == t){
                        return true;
                    }
                }
            }
        }
        return false;
    };

    auto dfs = [&](auto self, int s, int t, int f){
        if(s == t){
            return f;
        }
        auto r = f;
        for(int &i = cur[s]; i < (int)g[s].size(); i++ ){
            int j = g[s][i];
            auto [u, c] = e[j];
            if(c > 0 && h[u] == h[s] + 1){
                auto a = self(self, u, t, min(f, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if(r == 0){
                    break;
                }
            }
        }
        return f - r;
    };
    int ans = 0;
    while(bfs(0, n + 1)){
        cur.assign(n + 2, 0);
        ans += dfs(dfs, 0, n + 1, numeric_limits<int>::max());
    }
    cout << ans << "\n";

    for(int i = 1; i <= m; i++ ){
        for(auto x : g[i]){
            auto [to, c] = e[x];
            if(c == 0 && to){ // 该边为左部连向右部的边且剩余流量为0(被匹配了) 即为匹配边
                cout << i << " " << to << "\n";
            }
        }
    }
    return 0;
}