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
        // [in[u], out[u])
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
        a[i]--;
    }

    HLD h(n);
    for(int i = 0; i < n - 1; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        h.addEdge(x, y);
    }

    h.work(0);

    vector<ll> ans(n), cnt(n);
    ll sum = 0, maxn = 0;
    auto update = [&](int x, int w){ // 更新结点信息
        cnt[a[x]] += w;
        if(cnt[a[x]] > maxn){
            maxn = cnt[a[x]];
            sum = a[x] + 1;
        } else if(cnt[a[x]] == maxn){
            sum += a[x] + 1;
        }
    };
    auto dfs = [&](auto self, int x, int del) -> void { 
        for(auto u : h.adj[x]){ // 先遍历轻结点
            if(u == h.adj[x][0]){
                continue;
            }
            self(self, u, 1);
        }
        if(!h.adj[x].empty()){ // 遍历重结点
            self(self, h.adj[x][0], 0);
        }

        for(auto u : h.adj[x]){
            if(u == h.adj[x][0]){
                continue;
            }   
            // 将轻节点所在的整颗子树合并
            // 以x为根的子树中dfn序 为[in[x], out[x]) (左闭右开)
            for(int i = h.in[u]; i < h.out[u]; i++ ){
                update(h.seq[i], 1);
            }
        }
        // 更新自己
        update(x, 1);
        ans[x] = sum;

        // 是否是轻结点, 删除轻结点所有贡献, 只有重结点有贡献
        if(del){
            for(int i = h.in[x]; i < h.out[x]; i++ ){
                update(h.seq[i], -1);
            }
            sum = maxn = 0;
        }
    };
    dfs(dfs, 0, 1);
    for(int i = 0; i < n; i++ ){
        cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}           