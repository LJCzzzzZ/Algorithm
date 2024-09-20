#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define mp make_pair
#define pii pair<int, int>

int main() 
{

    // 最小路径树: 满足原图求出最小路径树后, 在新图中到各点的最短距离等于原图到各点的最短距离, 且满足选出的边权值和最小
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<tuple<int, int, int>>> adj(n);
    vector<int> w(m);
    for(int i = 0; i < m; i++ ){
        int x, y;
        cin >> x >> y >> w[i];
        x--, y--;
        adj[x].emplace_back(y, w[i], i);
        adj[y].emplace_back(x, w[i], i);
    }

    vector<ll> dis(n, 2e18);
    dis[0] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.emplace(0, 0);
    vector<int> st(n), pre(n, -1); // pre数组保存在最小路径树中该点由哪一条边连过去
    while(!q.empty()){
        auto [_, x] = q.top();
        q.pop();
        if(st[x]){
            continue;
        }
        st[x] = 1;
        for(auto [u, v, id] : adj[x]){
            if(dis[u] > dis[x] + v){
                dis[u] = dis[x] + v;
                q.emplace(dis[u], u);
                if(pre[u] == -1){ // 该点第一次被遍历, 随意连一条边
                    pre[u] = id;
                }
            }
            if(dis[u] == dis[x] + v && v < w[pre[u]]){ // 到该点距离最短, 若当前边权值更小, 则改为从 x -> u,就满足边权和最小的性质
                pre[u] = id;
            }
        }
    }

    vector<int> edge;
    auto dfs = [&](auto self, int x, int fa) -> void{ // dfs一遍原图找出树, 树边则是每个点的pre
        for(auto [u, v, id] : adj[x]){
            if(u == fa){
                continue;
            }
            if(pre[u] == id){ // 只递归树边指向的点
                edge.emplace_back(id);
                self(self, u, x);
            }
        }
    };
    dfs(dfs, 0, -1);
    cout << min(k, (int)edge.size()) << "\n";
    for(int i = 0; i < min(k, (int)edge.size()); i++ ){
        cout << edge[i] + 1 << " ";
    }
    cout << "\n";
    return 0;
}