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
    int n, m;
    cin >> n >> m;
    Flow<int> f(n);
    for(int i = 0; i < m; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        f.addEdge(x, y, w);
    }

    // 最大流 = 最小割
    cout << f.maxFlow(0, n - 1) << " ";

    // 满足最小割时, 割边最少的数量
    // 先求出最小割， 把没有满流的置为无穷, 满流的容量置为1,重新跑一遍最小割
    // 如果没有最小割的前提, 直接将所有边置为1即可
    for(int i = 0; i < (int)f.e.size(); i += 2 ){
        if(f.e[i].cap == 0){ // 满流的边赋为1, 用来中断
            f.e[i].cap = 1;
        } else { // 非满流的赋为无穷
            f.e[i].cap = 1e9;
        }
        // 反边置为0
        f.e[i + 1].cap = 0; 
    }
    cout << f.maxFlow(0, n - 1) << "\n";

    // 模数法, 只要模数大于边数就不会影响答案 c = c * mod + 1
    /*
    Flow<ll> f(n);
    const int mod = 1234;
    for(int i = 0; i < m; i++ ){
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        f.addEdge(x, y, 1ll * w * mod + 1);
    }

    ll ans = f.maxFlow(0, n - 1);
    cout << ans / mod << " " << ans % mod << " ";
    */
    return 0;
}