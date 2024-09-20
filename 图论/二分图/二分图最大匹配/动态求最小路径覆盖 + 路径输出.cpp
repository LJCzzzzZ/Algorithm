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
const int N = 5050;
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Flow<int> f(N);
    int cur = 1, res = 0;
    int s = 0, t = 5000;
    // 网络流支持动态加点加边, 在残余网络上继续跑可以避免重新建边
    // 建拆点二分图可以 x << 1, x << 1 | 1
    // 最小路径覆盖具有单调不减性
    while(true){
        f.addEdge(s, cur * 2, 1);
        f.addEdge(cur * 2 + 1, t, 1);
        for(int i = 1; i * i < cur * 2; i++ ){
            if(i * i - cur < cur && i * i - cur > 0){
                f.addEdge((i * i - cur) * 2, cur * 2 + 1, 1);
            }
        }
        int add = f.maxFlow(s, t);
        res += add;
        if(cur - res > n){
            break;
        }
        cur += 1;
    }
    cur -= 1;
    cout << cur << "\n";
    vector<int> pre(cur + 1), last(cur + 1);
    for(int i = 1; i <= cur; i++ ){
        for(auto x : f.g[i * 2]){
            auto [u, c] = f.e[x];
            if(u != s && c == 0){
                pre[i] = u / 2;
                last[u / 2] = i;
            }
        }
    }

    for(int i = 1; i <= cur; i++ ){
        if(!pre[i]){
            auto dfs = [&](auto self, int x) -> void {
                if(!last[x]){
                    cout << x << " ";
                    return;
                }
                self(self, last[x]);
                cout << x << " ";
            };
            dfs(dfs, i);
            cout << "\n";
        }
    }
    return 0;
}