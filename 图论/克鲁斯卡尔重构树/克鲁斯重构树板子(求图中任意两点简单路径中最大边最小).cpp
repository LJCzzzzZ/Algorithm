#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
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
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edge;
    for(int i = 0; i < m; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        edge.emplace_back(w, x, y);
    } 
    sort(edge.begin(), edge.end());

    vector<vector<int>> adj(2 * n); // 空间开两倍, 会新建 n - 1个新父节点
    DSU dsu(2 * n + 1);
    vector<int> val(2 * n + 1);
    int cur = n - 1, cnt = n;
    for(int i = 0; i < m; i++ ){
        auto [w, x, y] = edge[i];
        if(!dsu.same(x, y)){
            int fav = dsu.find(x), fau = dsu.find(y);
            int fa = ++cur;
            dsu.f[fa] = dsu.f[fav] = dsu.f[fau] = fa; // 两个点指向新的父节点
            val[fa] = w; // 新建结点作为边的权值
            // 建新边
            adj[fa].push_back(fau);
            adj[fa].push_back(fav);
            cnt--;
        }
        if(cnt == 1){
            break;
        }
    }

    // 任意两点的LCA 即为 两点间路径最大边的权值最小的权值
    const int LOG = 23;
    vector<vector<int>> f(2 * n + 1, vector<int> (LOG + 1, -1));
    vector<int> dep(2 * n + 1);
    queue<int> q;
    // 从最顶上的新父节点开始跑
    q.push(cur);
    dep[cur] = 1;
    while(!q.empty()){
        auto x = q.front();
        q.pop();
        for(auto u : adj[x]){
            dep[u] = dep[x] + 1;
            f[u][0] = x;
            for(int i = 1; i < LOG; i++ ){
                if(f[u][i - 1] != -1){
                    f[u][i] = f[f[u][i - 1]][i - 1];
                }
            }
            q.push(u);
        }
    }

    auto LCA = [&](int x, int y){
        if(dep[x] < dep[y]){
            swap(x, y);
        }
        for(int i = LOG - 1; i >= 0; i-- ){
            if(dep[f[x][i]] >= dep[y]){
                x = f[x][i];
            }
        }
        if(x == y) return x;
        for(int i = LOG - 1; i >= 0; i-- ){
            if(f[x][i] != f[y][i]){
                x = f[x][i], y = f[y][i];
            }
        }
        return f[x][0];
    };

    vector<ll> dp(n + 1);
    for(int i = 0; i < n - 1; i++ ){
        dp[i + 1] = dp[i] + val[LCA(i, i + 1)];
    }
    int Q;
    cin >> Q;
    while(Q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << dp[r] - dp[l] << "\n";
    }
    return 0;
}