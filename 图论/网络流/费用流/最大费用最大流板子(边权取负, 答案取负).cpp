#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
struct MCMF {
    struct Edge {
        long long to, cap, f; // to : 目标点, cap : 流量限制, f : 单位流量花费
        Edge(long long to, long long cap, long long f) : to(to), cap(cap), f(f) {}
    };
    const int n;
    vector<Edge> e; // 边集
    vector<vector<int>> g;  
    vector<long long> h, dis; //h : 残余网络各点的势能, dis : 源点到各点最短距离(最小花费) 
    vector<int> pre; // 保存增广路路径
    bool dijkstra(int s, int t) {
        dis.assign(n, numeric_limits<long long>::max());
        pre.assign(n, -1);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            auto [d, u] = que.top();
            que.pop();
            if (dis[u] != d) continue;
            for (int i : g[u]) {
                auto [v, c, f] = e[i];
                // 对边<u, v> 新边边权 f' = f + h[u] - h[v]
                if (c > 0 && dis[v] > d + h[u] - h[v] + f) {
                    dis[v] = d + h[u] - h[v] + f;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != numeric_limits<long long>::max();
    }
    MCMF(int n) : n(n), g(n) {}
    void addEdge(int u, int v, long long c, long long f) {
        g[u].push_back(e.size());
        e.emplace_back(v, c, f);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -f);
    }
    auto maxFlow(int s, int t) {
        long long flow = 0;
        long long cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            // 残余网络各点势能 h' = h + dis
            // 对于一对边 <i, j>  d[i] + (w + h[i] - h[j]) = d[j];
            // w + (d[i] + h[i]) - (d[j] + h[j]) = 0 显然这样更新边权不为负数
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            long long aug = numeric_limits<long long>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) aug = min(aug, e[pre[i]].cap);
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                e[pre[i]].cap -= aug;
                e[pre[i] ^ 1].cap += aug;
            }
            flow += aug;
            cost += (long long)aug * h[t]; // 花费 = 增广路流量 * 最小花费
        }
        return make_pair(flow, cost);
    }
};
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    MCMF f(2 + 2 * n);
    vector<vector<int>> a(n, vector<int> (n));
    for(int i = 0; i < n; i++ ){
        f.addEdge(0, i + 1, 1, 0);
        f.addEdge(n + i + 1, 2 * n + 1, 1, 0);
        for(int j = 0; j < n; j++ ){
            cin >> a[i][j];
            f.addEdge(i + 1, n + j + 1, 1, a[i][j]);
        }
    }
    cout << f.maxFlow(0, 2 * n + 1).se << "\n";

    // 费用流取最大值时, 边权取负数, 跑mcmf后, 费用再取负, 势能优化dijistra保证了边权不为负因此可以用dijistra优化的费用流
    MCMF f1(2 + 2 * n);
    for(int i = 0; i < n; i++ ){
        f1.addEdge(0, i + 1, 1, 0);
        f1.addEdge(n + i + 1, 2 * n + 1, 1, 0);
        for(int j = 0; j < n; j++ ){
            f1.addEdge(i + 1, n + j + 1, 1, -a[i][j]);
        }
    }
    cout << -f1.maxFlow(0, 2 * n + 1).se << "\n";
    return 0;
}