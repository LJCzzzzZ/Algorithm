#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>
const ll inf = 2e18;
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
int read() {
    static char c;
    static int x;
    if(c == '\n') return c = 0, -1;
    while(!isdigit(c = getchar())); 
    x = c ^ 48;
    while(isdigit(c = getchar()))
        x = x * 10 + (c ^ 48);
    return x;
}
int main() 
{
    // 最大权值闭合子图, 在该子图中, 该结点被点选后, 其所有后继都要被选
    // 建图
    /*源点向所有正权点连结一条容量为权值的边

    保留原图中所有的边，容量为正无穷

    所有负权点向汇点连结一条容量为权值绝对值的边
    */
    int n, m;
    scanf("%d %d", &m, &n);
    Flow<ll> f(n + m + 2);
    ll sum = 0;
    for(int i = 1; i <= m; i++ ){
        ll p;
        scanf("%lld", &p);
        f.addEdge(0, i, p);
        sum += p;
        int x;
        while(~(x = read())){
            f.addEdge(i, m + x, inf);
        }
    }

    for(int i = 1; i <= n; i++ ){
        ll c;
        scanf("%lld", &c);
        f.addEdge(m + i, n + m + 1, c);
    }

    ll ans = f.maxFlow(0, n + m + 1);

    // 最后一次建图时bfs扩展到的点即是没被割掉的点
    for(int i = 1; i <= m; i++ ){
        if(f.h[i] > 0){
            printf("%d ", i);
        }
    }
    printf("\n");
    for(int i = m + 1; i <= n + m; i++ ){
        if(f.h[i] > 0){
            printf("%d ", i - m);
        }
    }
    printf("\n");
    printf("%lld\n", sum - ans);
    return 0;
}