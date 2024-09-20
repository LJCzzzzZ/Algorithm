#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    // u跳到k级祖先
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;
        
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        return seq[in[u] - dep[u] + d];
    }
        
    // u是否是v的父节点
    bool isAncester(int u, int v) {
        // v入读大, u出度大
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    // 求以u为根 v的父节点
    //  u
    //  |
    //  |
    //  |
    //  v
    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }

        if (!isAncester(u, v)) {
            return parent[u];
        }
        // u 第一个小于v入度的点
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    // 以u 为根, 子树v的大小    
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    
    // a, b, c三点的公共祖先
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
int main() 
{
    // 题意: 给出一颗树, 给出q个询问, [L, R] 求Σmin(dis(i, L), dis(i, R))
    // 题解: LCA
    // 显然以 L为隔断的连通块的贡献都是到L, R同理, 那么对于L ~ R路径之间的点, 则以路径中点为分界进行加贡献
    //
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    HLD h(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        h.addEdge(x, y);
    }
    h.work();

    vector<ll> dp(n);
    function<void(int)> dfs1 = [&](int x){
        for(auto u : h.adj[x]){
            dfs1(u);
            dp[x] += dp[u] + h.siz[u];
        }
    };
    dfs1(0);

    vector<ll> sum(n), up(n);
    function<void(int)> dfs2 = [&](int x){
        up[x] = sum[x] - dp[x];
        for(auto u : h.adj[x]){
            sum[u] = sum[x] - h.siz[u] + n - h.siz[u];
            dfs2(u);
        }
    };
    sum[0] = dp[0];
    dfs2(0);

    int q;
    cin >> q;
    while(q--){
        int x, y;
        cin >> x >> y;
        x--, y--;
        if(h.dep[x] < h.dep[y]){
            swap(x, y);
        }
        if(x == y){
            cout << sum[x] << "\n";
            continue;
        }
        int dis = h.dist(x, y);
        int a = h.jump(x, (dis - 1) / 2);
        ll ans = sum[x] - up[a] - 1ll * (n - h.siz[a]) * ((dis - 1) / 2)
                 + sum[y] - dp[a] - 1ll * h.siz[a] * (dis - (dis - 1) / 2);
        cout << ans << "\n";
    }
    return 0;
}