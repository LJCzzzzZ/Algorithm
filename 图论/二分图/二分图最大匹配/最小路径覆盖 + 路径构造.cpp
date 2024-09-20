#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const int N = 505;
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
    // https://codeforces.com/contest/1765/problem/A 2400
    // 题意: 给出n个人, m个文件夹, 将m个文件夹分配到k个组中, 每个文件夹有一个访问等级
    // 每个对k个组都有一个访问等级, 当对组的访问权限大于文件夹在组中的权限则被访问到, 否则不能
    // 问在满足 第i个人访问文件夹为 Si的前提下的最小分组

    // 题解: 对于需要文件夹i的人集合{x1, x2, x3..} 需要文件夹j的人的集合 j{y1, y2, y3..}
    // 若i ∈ j 那么i和j就能放进一个组
    // 考虑建图 对 i -> j连一条有向边, 最终形成一张有向无环图, 对于一条路径上的点能被放进同一组, 相当于问用最少路径路径覆盖所有点
    // 最小点覆盖 = 点数 - 拆点二分图最大匹配 = 点数 - 最大流
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<bitset<N>> dp(m);
    for(int i = 0; i < n; i++ ){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++ ){
            dp[j][i] = (s[j] == '1');
        }
    }

    Flow<int> f(2 + 2 * m);
    for(int i = 0; i < m; i++ ){
        for(int j = 0; j < m; j++ ){
            if((dp[i] | dp[j]) == dp[i] && (i < j || dp[i] != dp[j])){
                f.addEdge(i + 1, j + m + 1, 1);
            }
        }
    }
    for(int i = 0; i < m; i++ ){
        f.addEdge(0, i + 1, 1);
        f.addEdge(i + m + 1, 2 * m + 1, 1);
    }

    int k = m - f.maxFlow(0, 2 * m + 1);
    cout << k << "\n";
    vector<int> pre(m, -1), last(m, -1);
    for(int i = 0; i < m; i++ ){
        for(auto x : f.g[i + 1]){
            auto [u, c] = f.e[x];
            if(u != 0 && c == 0){
                pre[u - m - 1] = i;
                last[i] = u - m - 1;
            }
        }
    }

    vector<int> belong(m);
    vector<int> level(m);
    vector<vector<int>> group(n, vector<int> (k));
    int cnt = 0;
    for(int i = 0; i < m; i++ ){
        if(pre[i] == -1){
            auto dfs = [&](auto self, int x, int res) -> void {
                belong[x] = cnt;
                level[x] = res;
                for(int j = 0; j < n; j++ ){
                    if(dp[x][j] == 1){
                        group[j][cnt] = res;
                    } 
                }
                if(last[x] == -1){
                    return;
                }
                self(self, last[x], res + 1);
            };
            dfs(dfs, i, 1);
            cnt += 1;
        }
    }

    for(int i = 0; i < m; i++ ){
        cout << belong[i] + 1 << " \n"[i == m - 1];
    }
    for(int i = 0; i < m; i++ ){
        cout << level[i] + 1 << " \n"[i == m - 1];
    }

    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < k; j++ ){
            cout << group[i][j] + 1 << " \n"[j == k - 1];
        }
    }
    return 0;
}