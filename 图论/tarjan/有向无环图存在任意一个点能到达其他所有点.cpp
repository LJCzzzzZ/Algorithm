#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
const int INF = 2e9;
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};
void solve(){
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edge;
    DSU dsu(n);
    for(int i = 0; i < m; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        x--;
        y--;
        edge.emplace_back(w, x, y);
        dsu.merge(x, y);
    }

    if(dsu.size(dsu.find(0)) != n){
        cout << "-1\n";
        return;
    }
    sort(edge.begin(), edge.end());
    int ans = -1;

    auto check = [&](int d){
        vector<vector<int>> adj(n);
        for(int i = 0; i < m; i++ ){
            auto [w, x, y] = edge[i];
            if(w <= d){
                adj[x].push_back(y);
                adj[y].push_back(x);
            } else {
                adj[x].push_back(y);
            }
        }

        vector<int> dfn(n), low(n), ins(n), stk;
        vector<int> c(n);
        int cnt = 0, ctt = 0;
        function<void(int)> dfs = [&](int x){ // 必须要遍历父边, 不能去重
            low[x] = dfn[x] = ++cnt;
            ins[x] = 1;
            stk.push_back(x);
            for(auto u : adj[x]){
                if(!dfn[u]){
                    dfs(u);
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
                    c[z] = ctt;
                    ins[z] = 0;
                }while(x != z);
            }
        };

        for(int i = 0; i < n; i++ ){
            if(!dfn[i]){
                dfs(i);
            }
        }
        vector<int> deg(ctt + 1);
        for(int i = 0; i < n; i++ ){
            for(auto u : adj[i]){
                if(c[u] != c[i]){
                    deg[c[u]]++;
                }
            }
        }

        int ans = count_if(deg.begin() + 1, deg.end(), [&](int z) {return z == 0;});
        // cout << ans << "zzz\n";
        return ans == 1;
    };

    int l = 0, r = INF;
    while(l < r){
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    if(l == INF) cout << "-1\n";
    else cout << l << "\n";
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}       