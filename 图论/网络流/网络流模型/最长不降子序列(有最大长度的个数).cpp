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
const int inf = 1e9;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++ ){
        cin >> a[i];
    }

    vector<int> dp(n + 1);
    for(int i = 0; i < n; i++ ){
        dp[i + 1] = 1;
        for(int j = 0; j < i; j++ ){
            if(a[j] <= a[i]){
                dp[i + 1] = max(dp[i + 1], dp[j + 1] + 1);
            }
        }
    }
    if(n == 1){
        cout << "1\n1\n1\n";
        return 0;
    }
    int mx = *max_element(dp.begin(), dp.end());
    Flow<int> f(2 + 2 * n);
    // 不降子序列相当于有d层的分层图, 对分层图建边
    for(int i = 0; i < n; i++ ){
        if(dp[i + 1] == 1){
            f.addEdge(0, i + 1, 1);
        }
        if(dp[i + 1] == mx){
            f.addEdge(i + 1 + n, 2 * n + 1, 1);
        }
        f.addEdge(i + 1, i + 1 + n, 1);
        for(int j = 0; j < i; j++ ){
            if(a[j] <= a[i] && dp[j + 1] + 1 == dp[i + 1]){
                f.addEdge(j + 1 + n, i + 1, 1);
            }
        }
    } 
    int ans = f.maxFlow(0, 2 * n + 1);
    cout << mx << "\n";
    cout << ans << "\n";
    // 一个点能被选无数次则该边流量设为无穷
    f.addEdge(0, 1, inf);
    f.addEdge(1, n + 1, inf);
    if(dp[n] == mx){
        f.addEdge(n, n + n, inf);
        f.addEdge(n + n, 2 * n + 1, inf);
    }
    cout << ans + f.maxFlow(0, 2 * n + 1) << "\n";
    return 0;
}