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

    /* 建图
    拆点后源点向1~n连接权为1的边，n+1~2n向汇点连权为1的边。

    对于原图中相连的两个点x->y，二分图中体现为x->y+n
    */

    // 最小路径覆盖 = 原图点数 - 新拆点二分图最大匹配数
    // 对于 x -> y + n 被匹配一条那么 路径数减少一条
    int n, m;
    cin >> n >> m;
    Flow<int> f(2 * n + 2);
    for(int i = 1; i <= n; i++ ){
        f.addEdge(0, i, 1);
        f.addEdge(i + n, 2 * n + 1, 1);
    }
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y;
        f.addEdge(x, y + n, 1);
    }

    int ans = n - f.maxFlow(0, 2 * n + 1);
    vector<int> pre(n + 1), last(pre);
    for(int i = 1; i <= n; i++ ){
        for(auto x : f.g[i]){
            auto [u, c] = f.e[x];
            if(c == 0 && u != 0){ // 剩余流量为0(被匹配了), 连向的点不是源点
                // 记录前驱和后继
                pre[u - n] = i;
                last[i] = u - n;
            }
        }
    }

    for(int i = 1; i <= n; i++ ){
        if(!pre[i]){ // 没有前驱就是该路径最后一个被遍历的点
            auto dfs = [&](auto self, int x) -> void {
                cout << x << " ";
                if(!last[x]){
                    return;
                }
                self(self, last[x]); // 递归上一个点
            };
            dfs(dfs, i);
            cout << "\n";
        }
    }

    cout << ans << "\n";
    return 0;
}