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
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> seg;
    vector<int> st;
    for(int i = 0; i < n; i ++ ){
        int l, r;
        cin >> l >> r;
        seg.emplace_back(r, l);
        st.push_back(l);
        st.push_back(r);
    }
    sort(seg.begin(), seg.end());
    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());

    int m = st.size();
    MCMF f(m + 3);
    auto find = [&](int x){
        return lower_bound(st.begin(), st.end(), x) - st.begin();
    };
    // 源点入流为k 限制了无论怎么选不重集都不会选超过k次
    // 每条线段向后面不相交的线段连边, 线段左端点向线段右端点连 流量为 1, 花费为线段长度的边
    /*f.addEdge(0, 1, k, 0);
    for(int i = 0; i < n; i++ ){
        auto [r, l] = seg[i];
        int L = find(l), R = find(r);
        f.addEdge(1, L + 2, 1, 0);
        f.addEdge(R + 2, m + 2, 1, 0);
        f.addEdge(L + 2, R + 2, 1, -(r - l));
        for(int j = i + 1; j < n; j++ ){
            auto [dy, dx] = seg[j];
            if(dx >= r){
                int nex = find(dx);
                f.addEdge(R + 2, nex + 2, 1, 0);
            }
        }
    }
    cout << -f.maxFlow(0, m + 2).se << "\n";
    */

    // 线段左端点向线段右端点连 流量为 1, 花费为线段长度的边
    // 每个点向后一个点连边 流量为k 花费为0 没用的流量给后面用
    // 跑出来就是 x <= k 段不重区间集合, 合并起来就是k可重区间集合
    f.addEdge(0, 1, k, 0);
    for(int i = 0; i < m - 1; i++ ){
        f.addEdge(i + 1, i + 2, k, 0);
    }
    for(int i = 0; i < n; i++ ){
        auto [r, l] = seg[i];
        int L = find(l), R = find(r);
        f.addEdge(L + 1, R + 1, 1, -(r - l));
    }
    f.addEdge(m, m + 1, k, 0);
    cout << -f.maxFlow(0, m + 1).se << "\n";
    return 0;
}