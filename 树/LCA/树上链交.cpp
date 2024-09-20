#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    HLD h(n);
    vector<int> a(n - 1), b(n - 1);
    for(int i = 1; i < n; i++ ){
        int x, y;
        cin >> x >> y;
        x--, y--;
        a[i - 1] = x;
        b[i - 1] = y;
        h.addEdge(x, y);
    }

    map<int, vector<int>, greater<int>> mp;
    vector<int> w(n);
    for(int i = 0; i < n; i++ ){
        cin >> w[i];
        mp[w[i]].push_back(i);
    }

    int res = 0;
    int S = -1, T = -1;
    vector<int> ans(n);
    for(auto [u, v] : mp){
        int m = v.size();
        if(m <= 1){
            continue;
        }

        if(m >= 3){
            res = u;
            break;
        }

        int A = v[0], B = v[1];
        if(S == -1){
            S = A, T = B;
            h.work(S);
            ans.assign(n, u);
            for(int i = T; i != S; i = h.parent[i] ){
                ans[i] = 0;
            }
        } else {
            while(S != T && h.rootedLca(A, B, T) != T ){
                ans[T] = u;
                T = h.parent[T];
            }
            while(S != T && h.rootedLca(A, B, S) != S){
                S = h.rootedParent(T, S);
                ans[S] = u;
            }
        }
    }

    if(S == -1){
        h.work(0);
    }

    for(int i = 0; i < n - 1; i++ ){
        if(h.parent[a[i]] == b[i]){
            swap(a[i], b[i]);
        }
        cout << max(res, ans[b[i]]) << "\n";
    }
    return 0;
}