#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
template<class T>
struct Flow {
    const int n;
    struct Edge {
        int to;
        T cap; // cap为边残余量
        Edge(int to, T cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e; // 存边
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h; // cur为当前弧优化, 前面无残余量的边不再遍历, h为分层图各点的层数
    Flow(int n) : n(n), g(n) {}
    
    bool bfs(int s, int t) { //求分层图
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) { // 没被访问过, 且有残余量
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    //寻找增广路
    T dfs(int u, int t, T f) { // t 为汇点, f为当前点可分配流量
        if (u == t) { // 到达汇点, 返回流量
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) { // 有残余量, 且为下一层
                auto a = dfs(v, t, std::min(r, c)); // 该边最大流量和可分配流量取min
                e[j].cap -= a; // 正边减
                e[j ^ 1].cap += a; // 反边加
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) { //加边, c为边容量
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T maxFlow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) { //存在增广路
            cur.assign(n, 0);
            // std::numeric_limits<T>::max() 源点流量赋为无穷
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
};
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 各种边判断规则
    // 必须边 : 剩余流量为0(被选了) 且 <x, y> 两端点在不同的强连通分量
    // 可行边 : 剩余流量为0(被选了) 或 <x, y> 两端点在同一强连通分量中
    // 不可行边 : 剩余流量为1(没被选) 且 <x, y> 两端点不在同一强连通分量中
    int n, m, t;
    cin >> n >> m >> t;
    vector<int> x(t), y(t);
    Flow<int> f(2 + n + m);
    for(int i = 0; i < t; i++ ){
        cin >> x[i] >> y[i];
        f.addEdge(x[i], y[i] + n, 1);
    }
    for(int i = 0; i < n; i++ ){
        f.addEdge(0, i + 1, 1);
    }
    for(int i = 0; i < m; i++ ){
        f.addEdge(n + i + 1, n + m + 1, 1);
    }
    f.maxFlow(0, 1 + n + m);
    vector<int> dfn(n + m + 2), low(dfn), ins(dfn), c(dfn), stk;
    vector<vector<int>> e(n + m + 2);
    vector<int> vis(f.e.size() + 1);
    for(int i = 0; i <= n + m + 1; i++ ){
        for(auto x : f.g[i]){
            auto [u, c] = f.e[x];
            // 连边技巧 : 在残量网络上对剩余流量为1的边在新图上建边;
            // 匹配边的反边剩余流量为1, 非匹配边剩余流量为1
            if(c > 0){
                e[i].push_back(u);
            } else {
                vis[x] = 1;
            }
        }
    }

    int cnt = 0, ctt = 0;
    auto dfs = [&](auto self, int x) -> void {
        dfn[x] = low[x] = ++cnt;
        ins[x] = 1;
        stk.push_back(x);
        for(auto u : e[x]){
            if(!dfn[u]){
                self(self, u);
                low[x] = min(low[x], low[u]);
            } else if(ins[u]){
                low[x] = min(low[x], dfn[u]);
            }
        }

        if(dfn[x] == low[x]){
            ctt++;
            int z;
            do{
                z = stk.back();
                stk.pop_back();
                ins[z] = 0;
                c[z] = ctt;
            }while(z != x);
        }
    };
    for(int i = 0; i <= n + m + 1; i++ ){
        if(!dfn[i]){
            dfs(dfs, i);
        }
    }

    vector<int> ans;
    // 将原图上的边放最前面方便遍历
    // 剩余流量为1, 且<x, y> 不在同一个强连通分量则为非可行边
    for(int i = 0; i < 2 * t; i += 2 ){
        int x = f.e[i ^ 1].to, y = f.e[i].to;
        if(!vis[i] && c[x] != c[y]){
            ans.push_back(i / 2);
        }
    }
    cout << (int)ans.size() << "\n";
    for(auto x : ans){
        cout << x + 1 << " ";
    }
    cout << "\n";
    return 0;
}