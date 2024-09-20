const ll INF = 2e18;
// 复杂度O(|V| * |E| * |E|) 点数 * 边数 * 边数
struct EK{
    int n; // n：点数，m：边数
    struct Edge{
        int from, to;
        ll cap, flow;
        Edge(int u, int v, int c, ll f) : from(u), to(v), cap(c), flow(f) {}
    };
    vector<Edge> edge; // edge：所有边的集合
    vector<vector<int>> g; // g：点 x -> x 的所有边在 edges 中的下标
    vector<int> p; // p：点 x -> BFS 过程中最近接近点 x 的边
    EK(int n) : n(n), g(n), p(n) {}

    void addEdge(int from, int to, int cap){
        edge.emplace_back(Edge(from, to, cap, 0));
        edge.emplace_back(Edge(to, from, 0, 0));
        int m = edge.size();
        g[from].push_back(m - 2);
        g[to].push_back(m - 1);
    }

    ll maxflow(int s, int t){
        ll flow = 0;
        while(true){
            vector<ll> a(n); // a：点 x -> BFS 过程中最近接近点 x 的边给它的最大流
            queue<int> q;
            q.push(s);
            a[s] = INF;
            while(!q.empty()){
                auto x = q.front();
                q.pop();
                for(int i = 0; i < (int)g[x].size(); i++ ){
                    Edge e = edge[g[x][i]];
                    if(!a[e.to] && e.cap > e.flow){ // 没被遍历过 且 不是饱和边
                        p[e.to] = g[x][i]; // g[x][i] 是最接近 点e.to的边
                        a[e.to] = min(1ll * a[x], e.cap - e.flow);  // 取增广路上流量最小值
                        q.push(e.to);
                    }
                }
                if(a[t]){ // 汇点接受到流就退出
                    break;
                }
            }
            if(!a[t]){ // 汇点没有接受到流, 说明源点和汇点不连通
                break;
            }
            for(int u = t; u != s; u = edge[p[u]].from ){ // 遍历s -> t最新的增广路
                edge[p[u]].flow += a[t];  // 增加路径上边的 flow 值
                edge[p[u] ^ 1].flow -= a[t];  // 减小反向路径的 flow 值
            }
            flow += a[t];
        }
        return flow;
    }
};i