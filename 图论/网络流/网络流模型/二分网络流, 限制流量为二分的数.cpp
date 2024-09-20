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
    //https://codeforces.com/problemset/problem/847/J
    int n, m;
    cin >> n >> m;
    vector<int> x(m), y(m);
    for(int i = 0; i < m; i++ ){
        cin >> x[i] >> y[i];
    }
    auto check = [&](int lim){
        Flow<int> f(n + m + 2);
        for(int i = 0; i < m; i++ ){
            f.addEdge(0, i + 1, 1);
            f.addEdge(i + 1, m + x[i], 1);
            f.addEdge(i + 1, m + y[i], 1);
        }
        for(int i = 0; i < n; i++ ){
            f.addEdge(m + i + 1, n + m + 1, lim);
        }
        return f.maxFlow(0, n + m + 1) == m;
    };
    int l = 0, r = n;
    while(l < r){
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }

    Flow<int> f(n + m + 2); 
    for(int i = 0; i < m; i++ ){
        f.addEdge(0, i + 1, 1);
        f.addEdge(i + 1, m + x[i], 1);
        f.addEdge(i + 1, m + y[i], 1);
    }
    for(int i = 0; i < n; i++ ){
        f.addEdge(m + i + 1, n + m + 1, l);
    }
    f.maxFlow(0, m + n + 1);
    cout << l << "\n";
    for(int i = 0; i < m; i++ ){
        for(auto _ : f.g[i + 1]){
            auto [u, c] = f.e[_];
            if(c == 0 && u != 0){
                cout << u - m << " " << (x[i] ^ y[i] ^ (u - m)) << "\n";
            }
        }
    }
    return 0;
}