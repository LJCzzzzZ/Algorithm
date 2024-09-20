#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
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
    // https://atcoder.jp/contests/abc301/tasks/abc301_h
    // 题意: 给定一张图, 问将边A的权值加1后, 图中S -> T所有路径中边权值最大的最小的 最小变化为多少
    // 题解: 分类讨论 + 并查集 + 树剖 + 离线查询
    // 按边权进行加边建最小生成树, 若已经联通当前边为候选边
    //  1: (1). 若最大边权为A - 1时就联通了, 那么该边不影响答案
    //     (2). 若当前边权值为大值时, S和T仍未联通, 说明要联通边权至少为A + 1, 因此该边+1不影响答案
    //  2: (1). 对生成树进行树剖, 对候选边在生成树上的路径进行联通, 说明在路径上可以加上这条边可以形成一个环, 因此路径上所有边+1都不影响
    //          答案
    //     (2). 若该边不是生成树上的边, 那么是否+1不影响答案, 在生成树上的边永远满足任意两点间最大权值最小
    //     (3). 若该边是生成树上的边, 那么该边若被权值小于当前权值的侯选边影响的话答案不变, 该边不在路径上影响也为0

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> U(m), V(m), W(m);
    vector<vector<int>> edge(m + 1);
    for(int i = 0; i < m; i++ ){
        cin >> U[i] >> V[i] >> W[i];
        U[i]--, V[i]--;
        edge[W[i]].push_back(i);
    }
    int q;
    cin >> q;
    vector<vector<int>> qry(m + 1);
    vector<int> A(q), S(q), T(q);
    for(int i = 0; i < q; i++ ){
        cin >> A[i] >> S[i] >> T[i];
        A[i]--, S[i]--, T[i]--;
        qry[W[A[i]]].push_back(i);
        qry[W[A[i]] - 1].push_back(i);
    }

    vector<int> ans(q, 1);
    DSU dsu(n);
    HLD t(n);
    vector<bool> vis(m);
    for(int i = 0; i <= m; i++ ){
        for(auto j : edge[i]){
            if(dsu.merge(U[j], V[j])){
                t.addEdge(U[j], V[j]);
            } else {
                vis[j] = true;
            }
        }
        for(auto j : qry[i]){
            if(W[A[j]] == i + 1 && dsu.same(S[j], T[j])){
                ans[j] = 0;
            }
            if(W[A[j]] == i && !dsu.same(S[j], T[j])){
                ans[j] = 0;
            }
        }
    }

    t.work();

    DSU dsu1(n);
    for(int i = 0; i <= m; i++ ){
        for(auto j : edge[i]){
            if(vis[j]){
                int u = U[j], v = V[j];
                u = dsu1.find(u);
                v = dsu1.find(v);
                while(u != v){
                    if(t.dep[u] < t.dep[v]){
                        swap(u, v);
                    }
                    dsu1.merge(t.parent[u], u);
                    u = dsu1.find(u);
                }
            }
        }
        for(auto j : qry[i]){
            if(W[A[j]] == i){
                if(vis[A[j]]){
                    ans[j] = 0;
                } else {
                    int u = U[A[j]], v = V[A[j]];
                    if(t.dep[u] < t.dep[v]){
                        swap(u, v);
                    }
                    if(t.isAncester(u, S[j]) == t.isAncester(u, T[j])){
                        ans[j] = 0;
                    }
                    if(dsu1.find(u) != u){
                        ans[j] = 0;
                    }
                }
            }
        }
    }
    for(int i = 0; i < q; i++ ){
        cout << ans[i] << "\n";
    }
    return 0;
}