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
    // 给定一个矩阵选择两个未覆盖的点覆盖使得矩阵不能被 1 * 2骨牌完全覆盖
    // 矩阵完全覆盖 = 矩阵黑白染色 + 二分图完备匹配数 = n * m / 2
    // 无解情况 : (1)矩阵未覆盖点数为奇数 (2)黑白点数相差大于2 (3) 二分图最大匹配数 != n * m / 2 - 1
    // 有解情况 : (1)相差 = 2 将多的一部点数减2 (2)相差 = 1 : 再删除相对的黑点, 即可完备匹配 
    // 两同色点的无解情况 --> n / 2 * (n - 1) / 2 = n ^ 2 / 4 >= 1e6  n <= 2000
    // 问题范围压缩到2000, 大于2000可填数的答案必定大于1e6
    // 小范围解 : 枚举删除的一个点, 建图跑二分图最大匹配, 满足最大匹配数 = n * m / 2 - 1
    // 再删一个点使得二分图最大匹配数减少即删去必经点
    // 让左部为点数大的一半 : 求必经点数 = 点数n - 非必经点
    // 求非必经点tirck : 先跑二分图匹配, 对残量网络, 从左部非匹配点出发 -> 右部匹配点 -> 找到左部匹配点
    // 显然可构成交错路径, 使得非匹配点成为匹配点 复杂度O(n + m) : 遍历每个点每条边一次
    // 总复杂度O(n * n * sqrt(n)) : 枚举点数 * 二分图dinic 
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    int cnt = 0;
    for(int i = 0; i < n; i++ ){
        cin >> s[i];
        for(auto x : s[i]){
            cnt += (x == '.');
        }
    }
    if(cnt > 2000){
        cout << 1000000 << "\n";
        return 0;
    }
    

    vector<pair<int, int>> moves{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    vector<vector<int>> adj(n * m + 1);
    int ctt = 0;
    vector<vector<int>> a(n, vector<int> (m));
    vector<int> type(n * m + 1);
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < m; j++ ){
            if(s[i][j] != '.'){
                continue;
            }
            a[i][j] = ++ctt;
            type[ctt] = (j + i) & 1;
            if(ctt > 2000){
                cout << 1000000 << "\n";
                return 0;
            }
        }
    }
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < m; j++ ){
            if(s[i][j] != '.'){
                continue;
            }
            for(auto [dx, dy] : moves){
                int x = dx + i, y = dy + j;
                if(x < 0 || y < 0 || x >= n || y >= m || s[x][y] != '.'){
                    continue;
                }
                adj[a[i][j]].push_back(a[x][y]);
            }
        }
    }
    int ans = 0;
    for(int id = 1; id <= ctt; id++ ){
        int B = 0, W = 0;
        for(int i = 1; i <= ctt; i++ ){
            if(i == id) continue;
            if(type[i]) B += 1;
            else W += 1;
        }
        if(abs(B - W) != 1){
            continue;
        }
        Flow<int> f(ctt + 2);
        vector<int> L;
        for(int i = 1; i <= ctt; i++ ){
            if(i == id) continue;
            if(type[i] == (B > W)){
                f.addEdge(0, i, 1);   
                L.push_back(i);
                for(auto x : adj[i]){
                    if(x != id){
                        f.addEdge(i, x, 1);
                    }
                }
            } else {
                f.addEdge(i, ctt + 1, 1);
            }
        }
        int res = f.maxFlow(0, ctt + 1);
        if(res != cnt / 2 - 1){
            continue;
        } else {
            vector<int> vis(ctt + 1);
            vector<int> x(ctt + 1), y(ctt + 1);
            for(auto j : L){
                for(auto u : f.g[j]){
                    auto [v, c] = f.e[u];
                    if(v != 0 && c == 0){
                        x[j] = v;
                        y[v] = j;
                    }
                }
            }

            auto dfs = [&](auto self, int x) -> void {
                if(vis[x]){
                    return;
                }
                vis[x] = 1;
                for(auto u : adj[x]){
                    if(y[u]){
                        self(self, y[u]);
                    }
                }
            };
            for(auto j : L){
                if(!x[j]){
                    dfs(dfs, j);
                }
            }
            for(auto j : L){
                ans += vis[j];
            }
        }
    }

    cout << min((cnt - 1) * cnt / 2 - ans / 2, 1000000) << "\n";
    return 0;
}